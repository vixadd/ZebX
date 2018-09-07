// TODO - Documentation

#include "Workspace.hh"
#include "Clientmenu.hh"
#include "Screen.hh"
#include "Window.hh"

#include <Unicode.hh>
#include <Util.hh>

#include <assert.h>


Workspace::Workspace(BScreen *scrn, unsigned int i) {
  _screen = scrn;
  _id = i;

  clientmenu = new Clientmenu(*_screen->blackbox(), *_screen, _id);

  setName(_screen->resource().workspaceName(i));

  focused_window = 0;
}


const bt::ustring Workspace::name(void) const
{ return _screen->resource().workspaceName(_id); }


void Workspace::setName(const bt::ustring &new_name) {
  bt::ustring the_name;

  if (! new_name.empty()) {
    the_name = new_name;
  } else {
    char default_name[80];
    sprintf(default_name, "Workspace %u", _id + 1);
    the_name = bt::toUnicode(default_name);
  }

  _screen->resource().setWorkspaceName(_id, the_name);
  clientmenu->setTitle(the_name);
}


void Workspace::addWindow(BlackboxWindow *win) {
  assert(win != 0);
  assert(win->workspace() == _id || win->workspace() == bt::BSENTINEL);

  win->setWorkspace(_id);

  if (win->isTransient()) {
    BlackboxWindow * const tmp = win->findNonTransientParent();
    if (tmp) {
      win->setWindowNumber(bt::BSENTINEL);
      return;
    }
  }

  const bt::ustring s =
    bt::ellideText(win->title(), 60, bt::toUnicode("..."));
  int wid = clientmenu->insertItem(s);
  win->setWindowNumber(wid);
}


void Workspace::removeWindow(BlackboxWindow *win) {
  assert(win != 0 && win->workspace() == _id);

  if (win->windowNumber() != bt::BSENTINEL)
    clientmenu->removeItem(win->windowNumber());
  win->setWindowNumber(bt::BSENTINEL);
  win->setWorkspace(bt::BSENTINEL);

  if (win == focused_window)
    focused_window = 0;
}
