// TODO - Documentation

#ifndef __Pen_hh
#define __Pen_hh

#include "Util.hh"

typedef struct _XftDraw XftDraw;

namespace bt {

  // forward declarations
  class Color;
  class Display;
  class PenCacheItem;
  class XftCacheItem;

  class Pen : public NoCopy {
  public:
    static void clearCache(void);

    Pen(unsigned int screen_, const Color &color_);
    ~Pen(void);

    inline unsigned int screen(void) const
    { return _screen; }
    inline const Color &color(void) const
    { return _color; }

    void setGCFunction(int function);
    void setLineWidth(int linewidth);
    void setSubWindowMode(int subwindow);

    ::Display *XDisplay(void) const;
    const Display &display(void) const;
    const GC &gc(void) const;

    XftDraw *xftDraw(Drawable drawable) const;

  private:
    unsigned int _screen;

    const Color &_color;
    int _function;
    int _linewidth;
    int _subwindow;

    mutable PenCacheItem *_item;
    mutable XftCacheItem *_xftitem;
  };

} // namespace bt

#endif // __Pen_hh
