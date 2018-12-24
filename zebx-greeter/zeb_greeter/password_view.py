# password_view.py
#
# Copyright (C) 2014-2018 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2


import os

from gi.repository import Gtk
from gi.repository import LightDM

from kano.logging import logger
from kano.gtk3.buttons import KanoButton, OrangeButton
from kano.gtk3.heading import Heading
from kano.gtk3.kano_dialog import KanoDialog

from kano_greeter.last_user import set_last_user
from kano_greeter.user_list import KanoUserList


class PasswordView(Gtk.Grid):

    def __init__(self, user, greeter):
        Gtk.Grid.__init__(self)

        self.get_style_context().add_class('password')
        self.set_row_spacing(10)

        self.greeter = greeter

        self.user = user
        self.title = self._set_title()

        self.attach(self.title.container, 0, 0, 1, 1)
        self.label = Gtk.Label(user)
        self.label.get_style_context().add_class('login')
        self.attach(self.label, 0, 1, 1, 1)
        self.password = Gtk.Entry()
        self.password.set_visibility(False)
        self.password.set_alignment(0.5)
        self.password.connect('activate', self._login_cb)
        self.attach(self.password, 0, 2, 1, 1)

        self.login_btn = KanoButton(_('Login').upper())
        self.login_btn.connect('clicked', self._login_cb)
        self.attach(self.login_btn, 0, 3, 1, 1)

        # Protect against removing the last Kano user
        # so you do not get locked out from logging into the Kit
        system_users = KanoUserList().get_users()
        if len(system_users) > 1:
            delete_account_btn = OrangeButton(_('Remove Account'))
            delete_account_btn.connect('clicked', self.delete_user)
            self.attach(delete_account_btn, 0, 4, 1, 1)

    def _set_title(self, create=True):
        '''
        Creates a Heading text widget, or updates it
        with the currently selected username.
        '''
        text_title = _('{}: Enter your password').format(self.user)
        text_description = _('If you haven\'t changed your\npassword, use "kano"')

        if create:
            title = Heading(text_title, text_description)
            return title
        else:
            self.title.set_text(text_title, text_description)
            return self.title

    def _reset_greeter(self):
        # connect signal handlers to LightDM
        self.cb_one = self.greeter.connect('show-prompt', self._send_password_cb)
        self.cb_two = self.greeter.connect('authentication-complete',
                                           self._authentication_complete_cb)
        self.cb_three = self.greeter.connect('show-message', self._auth_error_cb)

        self.greeter.connect_sync()
        return (self.cb_one, self.cb_two, self.cb_three)

    def _login_cb(self, event=None, button=None):
        logger.debug('Sending username to LightDM')

        self.login_btn.start_spinner()
        Gtk.main_iteration_do(True)

        # The call below will simply initiate the login flow.
        # The greeter library will inform us through callbacks
        # See: http://web.mit.edu/Source/debathena/config/lightdm-config/debian/debathena-lightdm-greeter
        self.greeter.authenticate(self.user)

    def _send_password_cb(self, _greeter, text, prompt_type):
        logger.debug(u'Need to show prompt: {}'.format(text))

        if _greeter.get_in_authentication():
            logger.debug('Sending password to LightDM')
            _greeter.respond(self.password.get_text())

    def _authentication_complete_cb(self, _greeter):
        logger.debug('Authentication process is complete')

        if not _greeter.get_is_authenticated():
            logger.warn('Could not authenticate user {}'.format(self.user))
            self._auth_error_cb(_('Incorrect password (The default is "kano")'))
            return

        logger.info(
            'The user {} is authenticated. Starting LightDM X Session'
            .format(self.user))

        set_last_user(self.user)

        if not _greeter.start_session_sync('lightdm-xsession'):
            logger.error('Failed to start session')
        else:
            logger.info('Login failed')

    def _auth_error_cb(self, text, message_type=None):
        logger.info(u'There was an error logging in: {}'.format(text))

        self.greeter.cancel_authentication()

        self.login_btn.stop_spinner()
        self.password.set_text('')

        win = self.get_toplevel()
        error = KanoDialog(
            title_text=_('Error Logging In'),
            description_text=text,
            parent_window=win
        )
        error.dialog.set_position(Gtk.WindowPosition.CENTER_ALWAYS)
        error.run()
        win.go_to_users()

    def grab_focus(self, user):
        '''
        Update username title, clear previous password,
        and give focus to password entry field.
        '''
        self.user = user
        self._set_title(create=False)

        self.password.set_text('')
        self.password.grab_focus()

    def delete_user(self, *args):
        import pam

        password_input = Gtk.Entry()
        password_input.set_visibility(False)
        password_input.set_alignment(0.5)

        confirm = KanoDialog(
            title_text = _('Are you sure you want to delete this account?'),
            description_text = _('Enter {}\'s password - A reboot will be required'.format(self.user)),
            widget=password_input,
            has_entry=True,
            button_dict = [
                {
                    'label': _('Cancel').upper(),
                    'color': 'red',
                    'return_value': False
                },
                {
                    'label': _('Ok').upper(),
                    'color': 'green',
                    'return_value': True
                }
            ])

        confirm.dialog.set_position(Gtk.WindowPosition.CENTER_ALWAYS)

        # Kano Dialog will return False if cancel button is clicked, or text
        # from the entry field if Ok
        response = confirm.run()
        if not response:
            return
        elif type(response) == str and not len(response):
            error = KanoDialog(
                title_text=_('Please enter the password for user {}'.format(self.user))
            )
            error.dialog.set_position(Gtk.WindowPosition.CENTER_ALWAYS)
            error.run()
            return
        else:
            password = response

        # Authenticate user and schedule removal. Protect against unknown troubles.
        try:
            if pam.authenticate(self.user, password):
                info = KanoDialog(
                    title_text=_('User {} scheduled for removal'.format(self.user)),
                    description_text=_('Press OK to reboot')
                )
                info.dialog.set_position(Gtk.WindowPosition.CENTER_ALWAYS)
                info.run()

                os.system('sudo kano-init schedule delete-user "{}"'.format(self.user))
                LightDM.restart()
            else:
                error = KanoDialog(
                    title_text=_('Incorrect password for user {}'.format(self.user))
                )
                error.dialog.set_position(Gtk.WindowPosition.CENTER_ALWAYS)
                error.run()
        except Exception as e:
            logger.error(u'Error deleting account {} - {}'.format(self.user, str(e)))
            error = KanoDialog(
                title_text=_('Could not delete account {}'.format(self.user))
            )
            error.dialog.set_position(Gtk.WindowPosition.CENTER_ALWAYS)
            error.run()
