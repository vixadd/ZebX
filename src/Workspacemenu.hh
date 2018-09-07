// TODO - Documentation

#ifndef   __Workspacemenu_hh
#define   __Workspacemenu_hh

#include <Menu.hh>

// forward declarations
class BScreen;
class Iconmenu;
class Workspace;

class Workspacemenu : public bt::Menu {
public:
  Workspacemenu(bt::Application &app, unsigned int screen, BScreen *bscreen);

  void insertIconMenu(Iconmenu *iconmenu);

  void insertWorkspace(Workspace *workspace);
  void removeWorkspace(unsigned int id);

  void setWorkspaceChecked(unsigned int id, bool checked);

protected:
  virtual void itemClicked(unsigned int id, unsigned int);

private:
  BScreen *_bscreen;
};

#endif // __Workspacemenu_hh
