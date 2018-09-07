// TODO - Documentation


#ifndef   __Workspace_hh
#define   __Workspace_hh

#include <Unicode.hh>
#include <Util.hh>

// forward declarations
class BlackboxWindow;
class BScreen;
class Clientmenu;

class Workspace: public bt::NoCopy {
public:
  Workspace(BScreen *scrn, unsigned int i);

  inline BScreen *screen(void) const
  { return _screen; }

  inline Clientmenu *menu(void) const
  { return clientmenu; }

  inline unsigned int id(void) const
  { return _id; }

  const bt::ustring name(void) const;
  void setName(const bt::ustring &new_name);

  void addWindow(BlackboxWindow *win);
  void removeWindow(BlackboxWindow *win);

  inline BlackboxWindow *focusedWindow(void) const
  { return focused_window; }
  inline void setFocusedWindow(BlackboxWindow *win)
  { focused_window = win; }
  inline void clearFocusedWindow(void)
  { focused_window = 0; }

private:
  BScreen *_screen;
  Clientmenu *clientmenu;
  unsigned int _id;
  BlackboxWindow *focused_window;
};

#endif // __Workspace_hh
