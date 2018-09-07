// TODO - Documentation.

#ifndef   __Clientmenu_hh
#define   __Clientmenu_hh

#include <Menu.hh>

class BScreen;


class Clientmenu : public bt::Menu {
public:
  Clientmenu(bt::Application &app, BScreen& screen, unsigned int workspace);

protected:
  virtual void itemClicked(unsigned int id, unsigned int button);

private:
  unsigned int _workspace;
  BScreen& _screen;
};


#endif // __Clientmenu_hh

