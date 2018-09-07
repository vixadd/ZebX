// TODO - Documentation

#include "Toolbarmenu.hh"
#include "Toolbar.hh"

#include <Unicode.hh>


class ToolbarPlacementmenu : public bt::Menu {
public:
  ToolbarPlacementmenu(bt::Application &app, unsigned int screen,
                       BScreen *bscreen);

  void refresh(void);

protected:
  void itemClicked(unsigned int id, unsigned int button);

private:
  BScreen *_bscreen;
};


enum {
  EnableToolbar,
  Placement,
  AlwaysOnTop,
  AutoHide
};


Toolbarmenu::Toolbarmenu(bt::Application &app, unsigned int screen,
                         BScreen *bscreen)
  : bt::Menu(app, screen), _bscreen(bscreen)
{
  setTitle(bt::toUnicode("Toolbar Options"));
  showTitle();

  ToolbarPlacementmenu *menu = new ToolbarPlacementmenu(app, screen, bscreen);
  insertItem(bt::toUnicode("Enable Toolbar"), EnableToolbar);
  insertSeparator();
  insertItem(bt::toUnicode("Placement"), menu, Placement);
  insertItem(bt::toUnicode("Always on top"), AlwaysOnTop);
  insertItem(bt::toUnicode("Auto Hide"), AutoHide);
}


void Toolbarmenu::refresh(void) {
  const ToolbarOptions &options = _bscreen->resource().toolbarOptions();
  setItemChecked(EnableToolbar, options.enabled);
  setItemChecked(AlwaysOnTop, options.always_on_top);
  setItemChecked(AutoHide, options.auto_hide);
}


void Toolbarmenu::itemClicked(unsigned int id, unsigned int button) {
  if (button != 1)
    return;

  Toolbar *toolbar = _bscreen->toolbar();
  ToolbarOptions &options =
    const_cast<ToolbarOptions &>(_bscreen->resource().toolbarOptions());

  switch (id) {
  case EnableToolbar:
    options.enabled = (toolbar == 0);
    _bscreen->saveResource();
    if (toolbar != 0)
      _bscreen->destroyToolbar();
    else
      _bscreen->createToolbar();
    break;

  case AlwaysOnTop:
    options.always_on_top = !options.always_on_top;
    _bscreen->saveResource();
    if (toolbar) {
      StackingList::Layer new_layer = (options.always_on_top
                                       ? StackingList::LayerAbove
                                       : StackingList::LayerNormal);
      _bscreen->stackingList().changeLayer(toolbar, new_layer);
      _bscreen->restackWindows();
    }
    break;

  case AutoHide:
    options.auto_hide = !options.auto_hide;
    _bscreen->saveResource();
    if (toolbar)
      toolbar->toggleAutoHide();
    break;

  default:
    break;
  } // switch
}


ToolbarPlacementmenu::ToolbarPlacementmenu(bt::Application &app,
                                           unsigned int screen,
                                           BScreen *bscreen)
  : bt::Menu(app, screen), _bscreen(bscreen)
{
  setTitle(bt::toUnicode("Toolbar Placement"));
  showTitle();

  insertItem(bt::toUnicode("Top Left"),      Toolbar::TopLeft);
  insertItem(bt::toUnicode("Top Center"),    Toolbar::TopCenter);
  insertItem(bt::toUnicode("Top Right"),     Toolbar::TopRight);
  insertSeparator();
  insertItem(bt::toUnicode("Bottom Left"),   Toolbar::BottomLeft);
  insertItem(bt::toUnicode("Bottom Center"), Toolbar::BottomCenter);
  insertItem(bt::toUnicode("Bottom Right"),  Toolbar::BottomRight);
}


void ToolbarPlacementmenu::refresh(void) {
  const ToolbarOptions &options = _bscreen->resource().toolbarOptions();
  setItemChecked(Toolbar::TopLeft,
                 options.placement == Toolbar::TopLeft);
  setItemChecked(Toolbar::TopCenter,
                 options.placement == Toolbar::TopCenter);
  setItemChecked(Toolbar::TopRight,
                 options.placement == Toolbar::TopRight);
  setItemChecked(Toolbar::BottomLeft,
                 options.placement == Toolbar::BottomLeft);
  setItemChecked(Toolbar::BottomCenter,
                 options.placement == Toolbar::BottomCenter);
  setItemChecked(Toolbar::BottomRight,
                 options.placement == Toolbar::BottomRight);
}


void ToolbarPlacementmenu::itemClicked(unsigned int id, unsigned int button) {
  if (button != 1)
    return;

  Toolbar *toolbar = _bscreen->toolbar();
  ToolbarOptions &options =
    const_cast<ToolbarOptions &>(_bscreen->resource().toolbarOptions());

  options.placement = id;
  if (toolbar)
    toolbar->setPlacement((Toolbar::Placement) id);
  _bscreen->saveResource();
}
