// TODO - Documentation

#include "Rootmenu.hh"
#include "Screen.hh"

#include <Unicode.hh>


Rootmenu::Rootmenu(bt::Application &app, unsigned int screen, BScreen *bscreen)
  : bt::Menu(app, screen), _bscreen(bscreen) { }


void Rootmenu::insertFunction(const bt::ustring &label,
                              unsigned int function,
                              const std::string &exec,
                              unsigned int id,
                              unsigned int index) {
  unsigned int x = insertItem(label, id, index);
  _funcmap.insert(FunctionMap::value_type(x, _function(function, exec)));
}


void Rootmenu::clear(void) {
  bt::Menu::clear();
  _funcmap.clear();
}


void Rootmenu::itemClicked(unsigned int id, unsigned int) {
  FunctionMap::const_iterator it = _funcmap.find(id);
  if (it == _funcmap.end()) return;

  switch (it->second.func) {
  case BScreen::Execute:
    if (! it->second.string.empty())
      bt::bexec(it->second.string, _bscreen->screenInfo().displayString());
    break;

  case BScreen::Restart:
    _bscreen->blackbox()->restart();
    break;

  case BScreen::RestartOther:
    if (! it->second.string.empty())
      _bscreen->blackbox()->restart(it->second.string);
    break;

  case BScreen::Exit:
    _bscreen->blackbox()->quit();
    break;

  case BScreen::SetStyle:
    if (! it->second.string.empty())
      _bscreen->blackbox()->resource().saveStyleFilename(it->second.string);

  case BScreen::Reconfigure:
    _bscreen->blackbox()->reconfigure();
    return;
  } // switch
}
