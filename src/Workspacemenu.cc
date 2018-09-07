// TODO - Documentation

#include "Workspacemenu.hh"
#include "Clientmenu.hh"
#include "Iconmenu.hh"
#include "Screen.hh"
#include "Workspace.hh"

#include <Unicode.hh>

#include <assert.h>


enum {
  Icons,
  NewWorkspace,
  RemoveLastWorkspace,
  WorkspaceIDDelta
};

Workspacemenu::Workspacemenu(bt::Application &app, unsigned int screen,
                             BScreen *bscreen)
  : bt::Menu(app, screen), _bscreen(bscreen) {
  setAutoDelete(false);
  setTitle(bt::toUnicode("Workspaces"));
  showTitle();

  insertSeparator();
  insertItem(bt::toUnicode("New Workspace"), NewWorkspace);
  insertItem(bt::toUnicode("Remove Last Workspace"), RemoveLastWorkspace);
}


void Workspacemenu::insertWorkspace(Workspace *workspace) {
  insertItem(workspace->name(), workspace->menu(),
             workspace->id() + WorkspaceIDDelta, count() - 3);
}


void Workspacemenu::removeWorkspace(unsigned int id)
{ removeItem(id + WorkspaceIDDelta); }


void Workspacemenu::setWorkspaceChecked(unsigned int id, bool checked)
{ setItemChecked(id + WorkspaceIDDelta, checked); }


void Workspacemenu::insertIconMenu(Iconmenu *iconmenu) {
  insertItem(bt::toUnicode("Iconified Windows"), iconmenu, Icons, 0);
  insertSeparator(1);
}


void Workspacemenu::itemClicked(unsigned int id, unsigned int) {
  switch (id) {
  case NewWorkspace:
    _bscreen->addWorkspace();
    _bscreen->resource().setWorkspaceCount(_bscreen->workspaceCount());
    _bscreen->saveResource();
    break;

  case RemoveLastWorkspace:
    _bscreen->removeLastWorkspace();
    _bscreen->resource().setWorkspaceCount(_bscreen->workspaceCount());
    _bscreen->saveResource();
    break;

  case Icons:
    break;

  default:
    id -= WorkspaceIDDelta;
    assert(id < _bscreen->workspaceCount());
    if (_bscreen->currentWorkspace() != id) {
      _bscreen->setCurrentWorkspace(id);
      hideAll();
    }
    break;
  } // switch
}
