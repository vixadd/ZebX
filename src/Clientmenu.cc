// TODO - Documentation.

#include "Clientmenu.hh"
#include "Window.hh"
#include "Screen.hh"


Clientmenu::Clientmenu(bt::Application &app, BScreen& screen,
                       unsigned int workspace)
  : bt::Menu(app, screen.screenNumber()),
    _workspace(workspace), _screen(screen)
{
  setAutoDelete(false);
  showTitle();
}


void Clientmenu::itemClicked(unsigned int id, unsigned int button) {
  BlackboxWindow *win = _screen.window(_workspace, id);

  if (button == 2) {
    // move win to current workspace
    if (_workspace != _screen.currentWorkspace())
      win->changeWorkspace(_screen.currentWorkspace());
  } else {
    // change to the win's workspace
    if (_workspace != _screen.currentWorkspace())
      _screen.setCurrentWorkspace(_workspace);
  }

  if (!win->isVisible())
    win->show();
  _screen.raiseWindow(win);
  win->setInputFocus();
}
