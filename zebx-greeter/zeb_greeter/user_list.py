#!/usr/bin/env python

# user_list.py
#
# Copyright (C) 2014 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU General Public License v2
#


from gi.repository import Gtk
from gi.repository import LightDM

import pwd

from kano.logging import logger
from kano.gtk3.scrolled_window import ScrolledWindow
from kano.gtk3.heading import Heading
from kano.gtk3.buttons import OrangeButton, KanoButton
from kano.gtk3.kano_dialog import KanoDialog

from kano_greeter.last_user import get_last_user


class KanoUserList:
    def __init__(self):
        # Alternative to LightDM.UsersList due to signals
        # causing a segmentation fault in the application
        pass

    def get_users(self, minimum_id=1000):
        '''
        Returns a list of interactive users on the system
        as reported by Unix /etc/password database
        '''
        interactive_users = []
        system_users = pwd.getpwall()

        # special usernames to exlude from the list
        exclude = ['nobody']

        for user in system_users:
            if user.pw_uid >= minimum_id and user.pw_name not in exclude:
                # This is an interactive user created by Kano
                interactive_users.append(user.pw_name)

        return sorted(interactive_users, reverse=False)


class UserListView(Gtk.Grid):
    HEIGHT = 250
    WIDTH = 1  # not important

    def __init__(self):
        Gtk.Grid.__init__(self)

        self.get_style_context().add_class('password')
        self.set_row_spacing(10)

        title = Heading(_('Select Account'),
                        _('Log in to which account?'))
        self.attach(title.container, 0, 0, 2, 1)

        self.scrolled_window = ScrolledWindow()
        self.scrolled_window.set_size_request(self.WIDTH, self.HEIGHT)
        self.box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL)
        self.box.set_spacing(10)
        self.box.set_margin_left(10)
        self.box.set_margin_right(10)
        self.scrolled_window.add(self.box)
        self.attach(self.scrolled_window, 0, 1, 2, 1)

        self.last_username = get_last_user()
        self._populate()

        self.add_account_btn = OrangeButton(_('Add Account'))
        self.add_account_btn.connect('clicked', self._btn_add_account_pressed)
        self.attach(self.add_account_btn, 0, 2, 1, 1)

        self.shutdown_btn = OrangeButton(_('Shutdown'))
        self.shutdown_btn.connect('clicked', self._btn_shutdown_pressed)
        self.attach(self.shutdown_btn, 1, 2, 1, 1)

    def _populate(self):
        # Populate list
        user_list = KanoUserList()
        for user_name in user_list.get_users():
            logger.debug('adding user {}'.format(user_name))
            self.add_item(user_name)

    def add_item(self, username):
        user = User(username)
        self.box.pack_start(user, False, False, 0)
        if username == self.last_username:
            user.grab_focus()

    def _btn_add_account_pressed(self, event=None, button=None):
        logger.debug('opening new user dialog')
        win = self.get_toplevel()
        win.go_to_newuser()

    def _btn_shutdown_pressed(self, event=None, button=None):
        shutdown_dialog = KanoDialog(title_text=_('Shutting down..'),
                                     description_text=_('Are you sure you want to shutdown your Kano now?'),
                                     button_dict=[
                                         {
                                             'label': _('Cancel').upper(),
                                             'color': 'green',
                                             'return_value': False
                                         },
                                         {
                                             'label': _('SHUTDOWN').upper(),
                                             'color': 'orange',
                                             'return_value': True
                                         }
                                     ])
        shutdown_dialog.dialog.set_position(Gtk.WindowPosition.CENTER_ALWAYS)
        poweroff = shutdown_dialog.run()

        if poweroff:
            LightDM.shutdown()


class User(KanoButton):
    HEIGHT = 50

    def __init__(self, username):
        KanoButton.__init__(self, text=username.title(), color='orange')
        self.set_size_request(-1, self.HEIGHT)

        self.username = username
        self.connect('clicked', self._user_select_cb)

    def _user_select_cb(self, button):
        logger.debug('user {} selected'.format(self.username))
        win = self.get_toplevel()
        win.go_to_password(self.username)
