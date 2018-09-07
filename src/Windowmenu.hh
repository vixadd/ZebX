// TODO - Documentation

#ifndef   __Windowmenu_hh
#define   __Windowmenu_hh

#include <Menu.hh>

// forward declarations
class SendToWorkspacemenu;
class BlackboxWindow;

class Windowmenu : public bt::Menu {
public:
  Windowmenu(bt::Application &app, unsigned int screen);

  inline BlackboxWindow *window() const
  { return _window; }
  void setWindow(BlackboxWindow *win);

  void hide(void);
  void refresh(void);

protected:
  virtual void itemClicked(unsigned int id, unsigned int);

private:
  BlackboxWindow *_window;
  SendToWorkspacemenu *_sendto;
};

#endif // __Windowmenu_hh
