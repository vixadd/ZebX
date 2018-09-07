// TODO - Documentation

#ifndef   __Slit_hh
#define   __Slit_hh

#include <Util.hh>

#include "BlackboxResource.hh"
#include "Screen.hh"

class Slit : public StackEntity, public bt::TimeoutHandler,
             public bt::EventHandler, public bt::NoCopy
{
public:
  struct SlitClient {
    Window window;
    Window client_window;
    Window icon_window;
    bt::Rect rect;
  };

private:
  typedef std::list<SlitClient*> SlitClientList;

  bool hidden;
  Display *display;

  Blackbox *blackbox;
  BScreen *screen;
  bt::Timer *timer;
  bt::EWMH::Strut strut;

  SlitClientList clientList;

  struct SlitFrame {
    Pixmap pixmap;
    Window window;

    int x_hidden, y_hidden;
    bt::Rect rect;
  } frame;

  void updateStrut(void);

public:
  Slit(BScreen *scr);
  virtual ~Slit(void);

  bool isHidden(void) const { return hidden; }

  // StackEntity interface
  Window windowID(void) const { return frame.window; }

  unsigned int exposedWidth(void) const;
  unsigned int exposedHeight(void) const;

  void addClient(Window w);
  void removeClient(SlitClient *client, bool remap = True);
  void removeClient(Window w, bool remap = True);
  void reconfigure(void);
  void updateSlit(void);
  void reposition(void);
  void shutdown(void);
  void toggleAutoHide(void);

  // EventHandler interface
  void buttonPressEvent(const XButtonEvent * const event);
  void enterNotifyEvent(const XCrossingEvent * const /*unused*/);
  void leaveNotifyEvent(const XCrossingEvent * const /*unused*/);
  void configureRequestEvent(const XConfigureRequestEvent * const event);
  void unmapNotifyEvent(const XUnmapEvent * const event);
  void reparentNotifyEvent(const XReparentEvent * const event);
  void exposeEvent(const XExposeEvent * const event);

  virtual void timeout(bt::Timer *);

  enum Direction { Vertical = 1, Horizontal };
  enum Placement { TopLeft = 1, CenterLeft, BottomLeft,
                   TopCenter, BottomCenter,
                   TopRight, CenterRight, BottomRight };

  Direction direction(void) const;
  Placement placement(void) const;
};

#endif // __Slit_hh
