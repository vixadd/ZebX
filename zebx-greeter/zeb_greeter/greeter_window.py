# greeter-window.py
#
# Copyright (C) 2014-2018 Kano Computing Ltd.
# License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2


from gi.repository import Gtk
from gi.repository import Gdk
from gi.repository import LightDM

from kano.gtk3.apply_styles import apply_common_to_screen
from kano.gtk3.top_bar import TopBar
from kano.gtk3.application_window import ApplicationWindow

from kano_greeter.user_list import UserListView
from kano_greeter.password_view import PasswordView
from kano_greeter.newuser_view import NewUserView
from kano_greeter.login_with_kw_view import LoginWithKanoWorldView


class GreeterWindow(ApplicationWindow):
    WIDTH = 400
    HEIGHT = -1

    greeter = LightDM.Greeter

    def __init__(self):
        apply_common_to_screen()

        self.a = self.b = self.c = 0
        self.switching = 0

        ApplicationWindow.__init__(self, _('Login'), self.WIDTH, self.HEIGHT)
        self.connect("delete-event", Gtk.main_quit)

        # Create a new LightDM.Greeter instance which will be used by the 2 views
        self.greeter = GreeterWindow.greeter.new()

        # Create the two views: one for normal Login, the other to create a new account
        self.password_view = PasswordView(None, self.greeter)
        self.newuser_view = NewUserView(self.greeter)
        self.login_with_kw_view = LoginWithKanoWorldView(self.greeter)

        self.grid = Gtk.Grid()
        self.set_main_widget(self.grid)

        self.grid.set_column_spacing(30)
        self.grid.set_row_spacing(30)

        self.top_bar = TopBar(_('Login'))
        self._remove_top_bar_buttons()
        self.top_bar.set_size_request(self.WIDTH, -1)
        self.grid.attach(self.top_bar, 0, 0, 3, 1)

        self.grid.attach(Gtk.Label(), 0, 3, 3, 1)

        self.top_bar.set_prev_callback(self._back_cb)

        self.user_list = UserListView()

        self.go_to_users()

        cursor = Gdk.Cursor.new(Gdk.CursorType.ARROW)
        self.get_root_window().set_cursor(cursor)

    def _remove_top_bar_buttons(self):
        self.top_bar.box.remove(self.top_bar.close_button)
        self.top_bar.box.remove(self.top_bar.next_button)

    def set_main(self, wdg):
        child = self.grid.get_child_at(1, 1)
        if child:
            self.grid.remove(child)

        self.grid.attach(wdg, 1, 1, 1, 1)
        self.show_all()

    def go_to_users(self):
        self.set_main(self.user_list)
        self.top_bar.disable_prev()

    def go_to_password(self, user):
        self.set_main(self.password_view)
        self.top_bar.enable_prev()

        if not self.switching == 1:
            self.greeter.disconnect(self.a)
            self.greeter.disconnect(self.b)
            self.greeter.disconnect(self.c)

            self.greeter = GreeterWindow.greeter.new()
            self.password_view.greeter = self.greeter
            (self.a, self.b, self.c) = self.password_view._reset_greeter()
            self.switching = 1

        self.password_view.grab_focus(user)

    def go_to_newuser(self):
        self.set_main(self.newuser_view)
        self.top_bar.enable_prev()

        if not self.switching == 2:
            self.greeter.disconnect(self.a)
            self.greeter.disconnect(self.b)
            self.greeter.disconnect(self.c)

            self.greeter = GreeterWindow.greeter.new()
            self.newuser_view.greeter = self.greeter

            # FIXME: We do not reset the greeter in the newuser view
            # It will be done only when the local user account has been forced
            # so as to avoid LightDM freezes
            # (self.a, self.b, self.c) = self.newuser_view._reset_greeter()
            self.switching = 2

    def go_to_login_with_kw(self):
        self.set_main(self.login_with_kw_view)
        self.top_bar.enable_prev()

        if not self.switching == 3:
            self.greeter.disconnect(self.a)
            self.greeter.disconnect(self.b)
            self.greeter.disconnect(self.c)

            self.greeter = GreeterWindow.greeter.new()
            self.login_with_kw_view.greeter = self.greeter

            # FIXME: We do not reset the greeter in the newuser view
            # It will be done only when the local user account has been forced
            # so as to avoid LightDM freezes
            # (self.a, self.b, self.c) = self.login_with_kw_view._reset_greeter()
            self.switching = 3

        self.login_with_kw_view.grab_focus()

    def _back_cb(self, event, button):
        self.go_to_users()
