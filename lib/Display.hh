// TODO - Documentation

#ifndef   __Display_hh
#define   __Display_hh

#include "Rect.hh"
#include "Util.hh"

#include <X11/Xlib.h>

namespace bt {

  // forward declarations
  class ScreenInfo;

  class Display : public NoCopy {
  private:
    ::Display *xdisplay;
    ScreenInfo** screen_info_list;
    size_t screen_info_count;

  public:
    Display(const char *dpy_name, bool multi_head);
    ~Display(void);

    inline ::Display* XDisplay(void) const
    { return xdisplay; }

    inline unsigned int screenCount(void) const
    { return screen_info_count; }
    const ScreenInfo &screenInfo(unsigned int i) const;
  };

  class ScreenInfo: public NoCopy {
  private:
    Display& _display;
    Visual *_visual;
    Window _rootwindow;
    Colormap _colormap;
    int _depth;
    unsigned int _screennumber;
    std::string _displaystring;
    Rect _rect;

  public:
    ScreenInfo(Display& d, unsigned int num);

    inline Display& display(void) const
    { return _display; }

    inline Visual *visual(void) const
    { return _visual; }
    inline Window rootWindow(void) const
    { return _rootwindow; }
    inline Colormap colormap(void) const
    { return _colormap; }

    inline int depth(void) const
    { return _depth; }

    inline unsigned int screenNumber(void) const
    { return _screennumber; }

    inline const Rect& rect(void) const
    { return _rect; }
    inline unsigned int width(void) const
    { return _rect.width(); }
    inline unsigned int height(void) const
    { return _rect.height(); }

    inline const std::string& displayString(void) const
    { return _displaystring; }
  };

} // namespace bt

#endif // __Display_hh
