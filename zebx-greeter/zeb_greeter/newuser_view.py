#!/usr/bin/env python

# newuser_view.py
#
# Copyright (C) 2015 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU General Public License v2
#
# An option to create a new account via
# kano-init on the next system boot.


from gi.repository import Gtk
from gi.repository import LightDM

import os

from kano.gtk3.buttons import KanoButton
from kano.gtk3.heading import Heading
from kano.gtk3.kano_dialog import KanoDialog


class NewUserView(Gtk.Grid):

    def __init__(self, greeter):
        Gtk.Grid.__init__(self)

        self.get_style_context().add_class('password')
        self.set_row_spacing(12)

        self.greeter = greeter

        title = Heading(_('Add new account'),
                        _('Login with Kano World\n'
                          'or create a new account.'))
        self.attach(title.container, 0, 0, 1, 1)

        # the 2 push buttons
        self.login_btn = KanoButton(_('Kano World'))
        self.login_btn.connect('clicked', self._login_button_pressed)
        self.attach(self.login_btn, 0, 1, 1, 1)

        self.newuser_btn = KanoButton(_('New Account'))
        self.newuser_btn.connect('clicked', self._new_user_reboot)
        self.attach(self.newuser_btn, 0, 2, 1, 1)

    def _login_button_pressed(self, event=None, button=None):
        win = self.get_toplevel()
        win.go_to_login_with_kw()

    def _new_user_reboot(self, event=None, button=None):
        '''
        Schedules kano-init to create a new user from scratch on next reboot,
        then performs the actual reboot
        '''
        confirm = KanoDialog(
            title_text=_('Are you sure you want to create a new account?'),
            description_text=_('A reboot will be required'),
            button_dict=[
                {
                    'label': _('Cancel').upper(),
                    'color': 'red',
                    'return_value': False
                },
                {
                    'label': _('Create').upper(),
                    'color': 'green',
                    'return_value': True
                }
            ])
        confirm.dialog.set_position(Gtk.WindowPosition.CENTER_ALWAYS)

        if confirm.run():
            os.system("sudo kano-init schedule add-user")
            LightDM.restart()
