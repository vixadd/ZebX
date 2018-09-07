// TODO - Documentation

#ifndef __Slitmenu_hh
#define __Slitmenu_hh

#include <Menu.hh>

class BScreen;

class Slitmenu : public bt::Menu {
public:
  Slitmenu(bt::Application &app, unsigned int screen, BScreen *bscreen);

  void refresh(void);

protected:
  void itemClicked(unsigned int id, unsigned int button);

private:
   BScreen *_bscreen;
};

#endif // __Slitmenu_hh
