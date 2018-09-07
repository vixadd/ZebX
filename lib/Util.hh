// TODO - Documentation

#ifndef __Util_hh
#define __Util_hh

#include <limits.h>
#include <string>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

// forward declarations of X11 types
typedef struct _XDisplay Display;
typedef union _XEvent XEvent;
typedef struct _XGC *GC;
typedef struct _XOC *XFontSet;
typedef struct _XftFont XftFont;
typedef unsigned long Time;
typedef unsigned long XID;
typedef XID Atom;
typedef XID Colormap;
typedef XID Cursor;
typedef XID Drawable;
typedef XID Pixmap;
typedef XID Window;

namespace bt {

  // XXX perhaps we could just call this SENTINEL?
  const unsigned int BSENTINEL = UINT_MAX;

  class NoCopy {
  protected:
    inline NoCopy(void)
    { }
  private:
    NoCopy(const NoCopy&);
    NoCopy& operator=(const NoCopy&);
  };

  class PointerAssassin {
  public:
    template<typename T>
    inline void operator()(const T ptr) const
    { delete ptr; }
  };

  inline bool within(int x, int y, int width, int height)
  { return ((x >= 0 && x <= width) && (y >= 0 && y <= height)); }

  void bexec(const std::string& command, const std::string& displaystring);

  std::string basename(const std::string& path);
  std::string dirname(const std::string& path);

  // equivalent to the shell command 'mkdir -m mode -p path'
  bool mkdirhier(const std::string &path, int mode = 0777);

  std::string expandTilde(const std::string& s);

  std::string itostring(unsigned long i);
  std::string itostring(long i);

  inline std::string itostring(unsigned int i)
  { return itostring(static_cast<unsigned long>(i)); }

  inline std::string itostring(int i)
  { return itostring(static_cast<long>(i)); }

  inline std::string itostring(unsigned short i)
  { return itostring(static_cast<unsigned long>(i)); }

  inline std::string itostring(short i)
  { return itostring(static_cast<long>(i)); }

  std::string tolower(const std::string &string);

//#ifdef _XUTIL_H_
  std::string textPropertyToString(::Display *display,
                                   ::XTextProperty& text_prop);
//#endif

} // namespace bt

#endif // __Util_hh
