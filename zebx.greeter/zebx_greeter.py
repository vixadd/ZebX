#==============================================================#
#                                                              #
#           Greeter controller that will utilitze the          #
#       core linux utilities to provide login and session      #
#       access to the core user file. This file will also      #
#       serve as the login portion of the ZebX mainframe.      #
#                                                              #
#                        Author: David Kroell                  #
#                       Version: 0.0.1                         #
#                                                              #
#==============================================================#

#!/bin/python

from gi.repository import GObject
from gi.repository import GLib
from gi.repository import Gtk
from gi.repository import LightDM
import sys

greeter = None
login_window = None
login_box = None
prompt_box = None
prompt_label = None
prompt_entry = None
message_label = None

# This Gtk signal is called when the user hits enter after entering a
# username/password or clicks the login button.  Since we re-purposed
# the text entry box, we have 3 possible cases to handle here.
# 1) the user is already authenticated, if for example, they don't have
#  a password set.
# 2) The username has been passed into LightDM and now we need to pass
#  the password
# 3) The username has been entered, but not passed in.  We pass it in
#  and start the authentication process.
def login_cb(widget):
    print >> sys.stderr, "login_cb"
    if greeter.get_is_authenticated():
        print >> sys.stderr, "user is already authenticated, starting session"
        start_session()
    elif greeter.get_in_authentication():
        print >> sys.stderr, "username was passed in already, send password to LightDM"
        greeter.respond(prompt_entry.get_text())
    else:
        print >> sys.stderr, "Initial entry of username, send it to LightDM"
        greeter.authenticate(prompt_entry.get_text())

# Gtk Signal Handlers
handlers = {
    "login_cb": login_cb
}

# The show_prompt callback is oddly named, but when you get this
# callback you are supposed to send the password to LightDM next.  In
# our example, we re-purpose the prompt and ask the user for the
# password which is then sent the next time the user hits the Login
# button or presses enter.
def show_prompt_cb(greeter, text, promptType):
    prompt_label.set_text(text)

    # clear the text entry box so the user can enter the password
    prompt_entry.set_text("")

    print >> sys.stderr, "prompt type: " + str(promptType)
    # if this is a password orompt, we want to hide the characters
    if promptType == LightDM.PromptType.SECRET:
        prompt_entry.set_visibility(False)
    else:
        prompt_entry.set_visibility(True)

# If LightDM sends a message back to the greeter, for example, "Login
# failed" or "invalid password" we display it in our message box.
def show_message_cb(text, message_type):
    message_label.set_visibility(True)
    message_label.set_text(text)

# Callback for after we send LightDM the password, this method
# has to handle a successful login, in which case we start the session
# or a failed login, in which case we tell the user
def authentication_complete_cb(greeter):
    if greeter.get_is_authenticated():
        # For our simple example we always start Unity-2d.  The LightDM
        # API has ways to query available sessions, please see the docs.
        if not greeter.start_session_sync("ubuntu"):
            print >> sys.stderr, "Failed to start session"
    else:
        print >> sys.stderr, "Login failed"

if __name__ == '__main__':
    main_loop = GObject.MainLoop ()
    builder = Gtk.Builder()
    greeter = LightDM.Greeter()

    # connect signal handlers to LightDM
    greeter.connect ("authentication-complete", authentication_complete_cb)
    greeter.connect ("show-message", show_message_cb)
    greeter.connect ("show-prompt", show_prompt_cb)

    # connect builder and widgets
    # you probably really want to put your .UI file somewhere else
    builder.add_from_file("/usr/bin/example-greeter.ui")

    login_window = builder.get_object("login_window")
    login_box = builder.get_object("login_box")
    prompt_box = builder.get_object("prompt_box")
    prompt_label = builder.get_object("prompt_label")
    prompt_entry = builder.get_object("prompt_entry")
    message_label = builder.get_object("message_label")

    # connect signals to Gtk UI
    builder.connect_signals(handlers)

    # connect to greeter
    greeter.connect_sync()

    # setup the GUI
    login_window.show()
    login_box.show()

    prompt_label.set_text("Username:")
    prompt_entry.set_sensitive(True)
    prompt_entry.set_text("")
    prompt_entry.set_visibility(True)
    prompt_box.show()

    prompt_entry.grab_focus()

    main_loop.run ()