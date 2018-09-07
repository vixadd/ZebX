// TODO - Documentation


#include "WindowGroup.hh"
#include "Window.hh"
#include "blackbox.hh"

#include <X11/Xlib.h>

#include <assert.h>


BWindowGroup::BWindowGroup(Blackbox *b, Window _group)
  : blackbox(b), group(_group)
{ blackbox->insertWindowGroup(group, this); }


BWindowGroup::~BWindowGroup(void)
{ blackbox->removeWindowGroup(group); }


void BWindowGroup::addWindow(BlackboxWindow *win)
{ windowList.push_front(win); }


void BWindowGroup::removeWindow(BlackboxWindow *win)
{
  windowList.remove(win);
  if (windowList.empty()) {
    assert(transientList.empty());
    delete this;
  }
}


void BWindowGroup::addTransient(BlackboxWindow *win) {
  assert(win->isGroupTransient());
  /*
    even though 'win' is a group transient, the group leader may be a
    managed top-level window, in which case we want the transient to
    be listed in the top-level's transient list, not here
  */
  const BlackboxWindow * const tmp = win->findTransientFor();
  assert(!tmp);
  transientList.push_front(win);
}


void BWindowGroup::removeTransient(BlackboxWindow *win) {
  assert(win->isGroupTransient());
  const BlackboxWindow * const tmp = win->findTransientFor();
  assert(!tmp);
  transientList.remove(win);
}
