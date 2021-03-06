// TODO - Documentation


#ifndef   __Screen_hh
#define   __Screen_hh

#include "StackingList.hh"
#include "blackbox.hh"

#include <Display.hh>
#include <EWMH.hh>
#include <EventHandler.hh>

#include <stdio.h>
#include <cstring>

#include <list>
#include <vector>

// forward declarations
class BlackboxWindow;
class Configmenu;
class Iconmenu;
class Rootmenu;
class Slit;
class Slitmenu;
class Toolbar;
class Toolbarmenu;
class Windowmenu;
class Workspace;
class Workspacemenu;

namespace bt {
  class ScreenInfo;
}


class BScreen : public bt::NoCopy, public bt::EventHandler {
private:
  bool managed, geom_visible;
  Pixmap geom_pixmap;
  Window geom_window;
  Window empty_window;
  Window no_focus_window;

  const bt::ScreenInfo& screen_info;
  Blackbox *_blackbox;
  Configmenu *configmenu;
  Iconmenu *_iconmenu;
  Rootmenu *_rootmenu;
  Slitmenu *_slitmenu;
  Toolbarmenu *_toolbarmenu;
  Windowmenu *_windowmenu;
  Workspacemenu *_workspacemenu;

  BlackboxWindowList windowList;
  StackingList _stackingList;
  unsigned int current_workspace;

  Slit *_slit;
  Toolbar *_toolbar;

  unsigned int geom_w, geom_h;

  bt::Rect usableArea;

  typedef std::list<bt::EWMH::Strut*> StrutList;
  StrutList strutList;
  typedef std::vector<Workspace*> WorkspaceList;
  WorkspaceList workspacesList;

  ScreenResource& _resource;

  void updateGeomWindow(void);

  bool parseMenuFile(FILE *file, Rootmenu *menu);

  void InitMenu(void);
  void LoadStyle(void);

  void manageWindow(Window w);
  void unmanageWindow(BlackboxWindow *win);
  bool focusFallback(const BlackboxWindow *win);

  void placeWindow(BlackboxWindow *win);
  bool cascadePlacement(bt::Rect& win, const bt::Rect& avail);
  bool centerPlacement(bt::Rect &win, const bt::Rect &avail);
  bool smartPlacement(unsigned int workspace, bt::Rect& win,
                      const bt::Rect& avail);
  unsigned int cascade_x, cascade_y;

  void updateAvailableArea(void);
  void updateWorkareaHint(void) const;

public:
  enum { Restart = 1, RestartOther, Exit, Shutdown, Execute, Reconfigure,
         SetStyle };

  BScreen(Blackbox *bb, unsigned int scrn);
  ~BScreen(void);

  inline bool isScreenManaged(void) const
  { return managed; }

  inline Window noFocusWindow() const
  { return no_focus_window; }

  // information about the screen
  inline const bt::ScreenInfo &screenInfo(void) const
  { return screen_info; }
  inline unsigned int screenNumber(void) const
  { return screen_info.screenNumber(); }

  inline ScreenResource& resource(void)
  { return _resource; }
  inline void saveResource(void)
  { _blackbox->resource().save(*_blackbox); }

  inline Blackbox *blackbox(void) const
  { return _blackbox; }

  inline Rootmenu *rootmenu(void) const
  { return _rootmenu; }
  inline Workspacemenu *workspacemenu(void) const
  { return _workspacemenu; }
  inline Iconmenu *iconmenu(void) const
  { return _iconmenu; }
  inline Slitmenu *slitmenu(void) const
  { return _slitmenu; }
  inline Toolbarmenu *toolbarmenu(void) const
  { return _toolbarmenu; }

  Windowmenu *windowmenu(BlackboxWindow *win);

  inline Slit *slit(void) const
  { return _slit; }
  void createSlit(void);
  void destroySlit(void);

  inline Toolbar *toolbar(void) const
  { return _toolbar; }
  void createToolbar(void);
  void destroyToolbar(void);

  Workspace *findWorkspace(unsigned int index) const;

  inline unsigned int workspaceCount(void) const
  { return workspacesList.size(); }
  inline unsigned int currentWorkspace(void) const
  { return current_workspace; }
  void setCurrentWorkspace(unsigned int id);
  void nextWorkspace(void);
  void prevWorkspace(void);

  const bt::Rect& availableArea(void);
  void addStrut(bt::EWMH::Strut *strut);
  void removeStrut(bt::EWMH::Strut *strut);
  void updateStrut(void);

  void updateClientListHint(void) const;
  void updateClientListStackingHint(void) const;
  void updateDesktopNamesHint(void) const;
  void readDesktopNames(void);

  void addWorkspace(void);
  void removeLastWorkspace(void);

  void addWindow(Window w);
  void releaseWindow(BlackboxWindow *win);
  BlackboxWindow* window(unsigned int workspace, unsigned int id);

  void raiseWindow(StackEntity *entity);
  void lowerWindow(StackEntity *entity);

  inline StackingList &stackingList()
  { return _stackingList; }
  void restackWindows(void);

  void addIcon(BlackboxWindow *win);
  void removeIcon(BlackboxWindow *win);
  BlackboxWindow *icon(unsigned int id);

  void nextFocus(void);
  void prevFocus(void);
  void raiseFocus(void);

  void propagateWindowName(const BlackboxWindow * const win);

  void reconfigure(void);
  void toggleFocusModel(FocusModel model);
  void rereadMenu(void);
  void shutdown(void);

  enum GeometryType { Position, Size };
  void showGeometry(GeometryType type, const bt::Rect &rect);
  void hideGeometry(void);

  void clientMessageEvent(const XClientMessageEvent * const event);
  void buttonPressEvent(const XButtonEvent * const event);
  void propertyNotifyEvent(const XPropertyEvent * const event);
  void unmapNotifyEvent(const XUnmapEvent * const event);
};

#endif // __Screen_hh
