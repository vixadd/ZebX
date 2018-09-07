// TODO - Documentation

#ifndef __Toolbarmenu_hh
#define __Toolbarmenu_hh

#include <Menu.hh>

class BScreen;

class Toolbarmenu : public bt::Menu {
public:
  Toolbarmenu(bt::Application &app, unsigned int screen, BScreen *bscreen);

  void refresh(void);

protected:
  void itemClicked(unsigned int id, unsigned int button);

private:
  BScreen *_bscreen;
};

#endif // __Toolbarmenu_hh
