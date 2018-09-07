// TODO - Documentation


#ifndef   __Configmenu_hh
#define   __Configmenu_hh

#include <Menu.hh>

class BScreen;

class Configmenu : public bt::Menu {
public:
    Configmenu(bt::Application &app, unsigned int screen, BScreen *bscreen);

    void refresh(void);

protected:
    void itemClicked(unsigned int id, unsigned int);

private:
    BScreen *_bscreen;
};

#endif // __Configmenu_hh
