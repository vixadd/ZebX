// TODO - Documentation

#ifndef __EventHandler_hh
#define __EventHandler_hh

#include <X11/Xlib.h>

namespace bt {

  /*
    The abstract event handler.  You must register your event handler
    with the application object.  See
    bt::Application::insertEventHandler() and
    bt::Application::removeEventHandler().
  */
  class EventHandler
  {
  public:
    inline virtual ~EventHandler(void)
    { }

    // Mouse button press.
    inline virtual void buttonPressEvent(const XButtonEvent * const)
    { }
    // Mouse button release.
    inline virtual void buttonReleaseEvent(const XButtonEvent * const)
    { }
    // Mouse movement.
    inline virtual void motionNotifyEvent(const XMotionEvent * const)
    { }
    // Key press.
    inline virtual void keyPressEvent(const XKeyEvent * const)
    { }
    // Key release.
    inline virtual void keyReleaseEvent(const XKeyEvent * const)
    { }

    // Window configure (size, position, stacking, etc.).
    inline virtual void configureNotifyEvent(const XConfigureEvent * const)
    { }
    // Window shown.
    inline virtual void mapNotifyEvent(const XMapEvent * const)
    { }
    // Window hidden.
    inline virtual void unmapNotifyEvent(const XUnmapEvent * const)
    { }
    // Window reparented.
    inline virtual void reparentNotifyEvent(const XReparentEvent * const)
    { }
    // Window destroyed.
    inline virtual void destroyNotifyEvent(const XDestroyWindowEvent * const)
    { }

    // Mouse entered window.
    inline virtual void enterNotifyEvent(const XCrossingEvent * const)
    { }
    // Mouse left window.
    inline virtual void leaveNotifyEvent(const XCrossingEvent * const)
    { }

    // Window needs repainting.
    inline virtual void exposeEvent(const XExposeEvent * const)
    { }

    // Window property changed/added/deleted.
    inline virtual void propertyNotifyEvent(const XPropertyEvent * const)
    { }

    // Message passing.
    inline virtual void clientMessageEvent(const XClientMessageEvent * const)
    { }

    // Window shape changed. (Note: we use XEvent instead of
    // XShapeEvent to avoid the header.)
    inline virtual void shapeEvent(const XEvent * const)
    { }

  protected:
    inline EventHandler(void)
    { }
  };

} // namespace bt

#endif // __EventHandler_hh
