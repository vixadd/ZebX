#!/usr/bin/env python

# login_with_kw_view.py
#
# Copyright (C) 2015 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU General Public License v2
#
# This view allows to authenticate a Kano World
# account and create a synchroznied local user.


from gi.repository import Gtk, GObject

from kano.logging import logger
from kano.gtk3.buttons import KanoButton
from kano.gtk3.heading import Heading
from kano.gtk3.kano_dialog import KanoDialog

from kano_greeter.last_user import set_last_user

from kano_world.functions import login as kano_world_authenticate
from kano.utils import run_cmd

import threading


class LoginWithKanoWorldView(Gtk.Grid):

    def __init__(self, greeter):
        Gtk.Grid.__init__(self)

        self.get_style_context().add_class('password')
        self.set_row_spacing(12)

        self.greeter = greeter

        title = Heading(_('Login with Kano World'),
                        _('Enter your Kano World details.'))
        self.attach(title.container, 0, 0, 1, 1)

        self.username = Gtk.Entry()
        self.username.set_placeholder_text(_('username'))
        self.attach(self.username, 0, 1, 1, 1)

        self.password = Gtk.Entry()
        self.password.set_visibility(False)
        self.password.set_placeholder_text(_('password'))
        self.attach(self.password, 0, 2, 1, 1)

        self.login_btn = KanoButton(_('LOGIN'))
        self.login_btn.connect('clicked', self._btn_login_pressed)
        self.attach(self.login_btn, 0, 3, 1, 1)

    def _btn_login_pressed(self, event=None, button=None):
        '''
        Authenticates against Kano World. If successful synchronizes to a local
        Unix account, and tells lightdm to go forward with local a login.
        '''
        logger.debug('Synchronizing Kano World account')
        self.login_btn.start_spinner()
        self.login_btn.set_sensitive(False)

        t = threading.Thread(target=self._thr_login)
        t.start()

    def _thr_login(self):
        loggedin = False
        reason = ''

        # TODO: Disable the "login" button unless these entry fields are non-empty
        # Collect credentials from the view
        self.unix_password = self.password.get_text()
        self.world_username = self.username.get_text()
        self.unix_username = self.username.get_text()
        atsign = self.unix_username.find('@')
        if atsign != -1:
            # For if we are in "staging" mode (see /etc/kano-world.conf)
            self.unix_username = self.unix_username[:atsign]

        # Now try to login to Kano World
        try:
            logger.debug('Authenticating user: {} to Kano World'.format(self.username.get_text()))
            (loggedin, reason) = kano_world_authenticate(self.username.get_text(), self.password.get_text())
            logger.debug('Kano World auth response: {} - {}'.format(loggedin, reason))
        except Exception as e:
            reason = str(e)
            logger.debug('Kano World auth Exception: {}'.format(reason))
            pass

        if not loggedin:
            # Kano world auth unauthorized
            # FIXME: Localizing the below string fails with an exception
            GObject.idle_add(self._error_message_box, _('Failed to authenticate to Kano World'), reason)
            return
        else:
            # We are authenticated to Kano World: proceed with forcing local user
            rc = -1
            try:
                # Create the local unix user, bypass kano-init-flow, login & sync to Kano World
                createuser_cmd = 'sudo /usr/bin/kano-greeter-account {} {} {}'.format(
                    self.unix_username, self.unix_password, self.world_username)
                procout, procerr, rc = run_cmd(createuser_cmd)
                if rc == 0:
                    logger.debug('Local user created correctly: {}'.format(self.unix_username))
                elif rc == 1:
                    logger.debug('Local user already exists, proceeding with login: {}'.format(self.unix_username))

                created = True
            except:
                created = False

            if not created:
                logger.debug('Error creating new local user: {}'.format(self.unix_username))
                GObject.idle_add(self._error_message_box, _('Could not create local user'), rc)
                return

            # Tell Lidghtdm to proceed with login session using the new user
            # We bind LightDM at this point only, this minimizes the number of attempts
            # to bind the Greeter class to a view, which he does not like quite well.
            logger.debug('Scheduling lightdm authentication in math thread')
            GObject.idle_add(self._auth_call)

    def _auth_call(self):
        logger.debug('Starting lightdm authentication')
        self._reset_greeter()
        self.greeter.authenticate(self.unix_username)
        if self.greeter.get_is_authenticated():
            logger.debug('User is already authenticated, starting session')

    def _reset_greeter(self):
        # connect signal handlers to LightDM
        self.cb_one = self.greeter.connect('show-prompt', self._send_password_cb)
        self.cb_two = self.greeter.connect('authentication-complete',
                                           self._authentication_complete_cb)
        self.cb_three = self.greeter.connect('show-message', self._auth_error_cb)
        self.greeter.connect_sync()
        return (self.cb_one, self.cb_two, self.cb_three)

    def _send_password_cb(self, _greeter, text, prompt_type):
        logger.debug('Need to show prompt: {}'.format(text))
        if _greeter.get_in_authentication():
            logger.debug('Sending password to LightDM')
            _greeter.respond(self.unix_password)

    def _authentication_complete_cb(self, _greeter):
        logger.debug('Authentication process is complete')

        if not _greeter.get_is_authenticated():
            logger.warn('Could not authenticate user {}'.format(self.unix_username))
            self._auth_error_cb(_('Incorrect password (The default is "kano")'))
            return

        logger.info(
            'The user {} is authenticated. Starting LightDM X Session'
            .format(self.unix_username))

        set_last_user(self.unix_username)

        if not _greeter.start_session_sync('lightdm-xsession'):
            logger.error('Failed to start session')
        else:
            logger.info('Login failed')

    def _auth_error_cb(self, text, message_type=None):
        logger.info('There was an error logging in: {}'.format(text))

        win = self.get_toplevel()
        win.go_to_users()

        self.login_btn.stop_spinner()
        self.login_btn.set_sensitive(True)
        self.newuser_btn.set_sensitive(True)

        error = KanoDialog(title_text=_('Error Synchronizing account'),
                           description_text=text,
                           parent_window=self.get_toplevel())
        error.dialog.set_position(Gtk.WindowPosition.CENTER_ALWAYS)
        error.run()

    def _error_message_box(self, title, description):
        '''
        Show a standard error message box
        '''
        self.login_btn.stop_spinner()
        self.login_btn.set_sensitive(True)

        errormsg = KanoDialog(title_text=title,
                              description_text=description,
                              button_dict=[
                                  {
                                      'label': _('OK').upper(),
                                      'color': 'red',
                                      'return_value': True
                                  }])

        errormsg.dialog.set_position(Gtk.WindowPosition.CENTER_ALWAYS)
        errormsg.run()

        # Clean up password field
        self.password.set_text('')
        return

    def grab_focus(self):
        '''
        Clear username and password previous text, and gain focus.
        '''
        self.username.set_text('')
        self.password.set_text('')
