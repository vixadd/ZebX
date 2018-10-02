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


  /*
   * Singelton screen-info class to tell us about the
   * Screen itself.
   */
  class ScreenInfo: public NoCopy {

  private:

	// Private varaibles that controls the main
	// environment for the displays.
    Display& _display;
    Visual *_visual;
    Window _rootwindow;
    Colormap _colormap;
    int _depth;
    unsigned int _screennumber;
    std::string _displaystring;
    Rect _rect;

  public:

    /*
     * Constructor for the ScreenInfo class.
     * This will hold information for the Display at hand.
     */
    ScreenInfo(Display& d, unsigned int num);

    /*
     * Getter for the display variable
     */
    inline Display& display(void) const
    { return _display; }

    /*
     * Getter on the Visual
     */
    inline Visual *visual(void) const
    { return _visual; }

    /*
     * Retrieve the root window of the app
     */
    inline Window rootWindow(void) const
    { return _rootwindow; }

    /*
     * getter for the Colormap.
     * -- Should be deprecated (TODO)
     */
    inline Colormap colormap(void) const
    { return _colormap; }

    /*
     * retrieve the depth of the window.
     */
    inline int depth(void) const
    { return _depth; }

    /*
     * What screen number the window is displayed on.
     */
    inline unsigned int screenNumber(void) const
    { return _screennumber; }

    /*
     * Rectangle dimension of the window.
     * We probably don't need this since we never use it.
     */
    inline const Rect& rect(void) const
    { return _rect; }

    /*
     * Width of the window.
     */
    inline unsigned int width(void) const
    { return _rect.width(); }

    /*
     * Height of the window.
     */
    inline unsigned int height(void) const
    { return _rect.height(); }

    /*
     * Display string or name banner on the window that is
     * displayed.
     */
    inline const std::string& displayString(void) const
    { return _displaystring; }

  };

} // namespace bt

#endif // __Display_hh
