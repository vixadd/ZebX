#ifndef   __Iconmenu_hh
#define   __Iconmenu_hh

#include "Menu.hh"

// forward declarations
class BScreen;

class Iconmenu : public bt::Menu {
public:
  Iconmenu(bt::Application &app, unsigned int screen, BScreen *bscreen);

protected:
  virtual void itemClicked(unsigned int id, unsigned int);

private:
  BScreen *_bscreen;
};

#endif // __Iconmenu_hh
