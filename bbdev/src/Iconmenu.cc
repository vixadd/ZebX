
#include "Iconmenu.hh"
#include "Screen.hh"
#include "Window.hh"

#include <Unicode.hh>


Iconmenu::Iconmenu(bt::Application &app, unsigned int screen,
                   BScreen *bscreen)
  : bt::Menu(app, screen), _bscreen(bscreen)
{
  setAutoDelete(false);
  setTitle(bt::toUnicode("Iconified Windows"));
  showTitle();
}


void Iconmenu::itemClicked(unsigned int id, unsigned int) {
  BlackboxWindow * const win = _bscreen->icon(id);
  win->activate();
}
