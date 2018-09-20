// TODO - Documentation

#ifndef   __Display_hh
#define   __Display_hh

#include "Rect.hh"
#include "Util.hh"

#include <X11/Xlib.h>

namespace bt {

  // forward declarations
  class ScreenInfo;

  /*
   * Display class <SINGLETON>
   */
  class Display : public NoCopy {
  // PRIVATE VARS
  private:
    ::Display *xdisplay;
    ScreenInfo** screen_info_list;
    size_t screen_info_count;

  public:
    /*
     * Display Constructor
     * ----------params-----------
     * dpy_name   : Display name
     * multi_head : Multiple heads present.
     */
    Display(const char *dpy_name, bool multi_head);

    // DESTRUCTOR
    ~Display(void);

    // Get the current XDisplay object for this head.
    //
    // Return: XDisplay for this Head.
    inline ::Display* XDisplay(void) const
    { return xdisplay; }

    // Return Number of screens.
    inline unsigned int screenCount(void) const
    { return screen_info_count; }

    /*
     * Return screen info object of the specified Screen Id.
     * ----------params------------
     * i : Screen ID as specified in '/etc/X11/xorg.conf'
     */
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
