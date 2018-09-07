// TODO - Documentation

#ifndef   __Image_hh
#define   __Image_hh

#include "Util.hh"

namespace bt {

  // forward declarations
  class Color;
  class Display;
  class ScreenInfo;
  class Texture;
  class XColorTable;

  enum DitherMode {
    NoDither,
    OrderedDither,
    FloydSteinbergDither
  };

  struct RGB {
    unsigned int red      : 8;
    unsigned int green    : 8;
    unsigned int blue     : 8;
    unsigned int reserved : 8;
  };

  class Image : public NoCopy {
  public:
    static inline unsigned int maximumColors(void)
    { return global_maximumColors; }
    static inline void setMaximumColors(unsigned int newval)
    { global_maximumColors = newval; }

    static inline DitherMode ditherMode(void)
    { return global_ditherMode; }
    static inline void setDitherMode(DitherMode dithermode)
    { global_ditherMode = dithermode; }

    Image(unsigned int w, unsigned int h);
    ~Image(void);

    Pixmap render(const Display &display, unsigned int screen,
                  const Texture &texture);

  private:
    RGB *data;
    unsigned int width, height;

    void OrderedDither(XColorTable *colortable,
                       unsigned int bit_depth,
                       unsigned int bytes_per_line,
                       unsigned char *pixel_data);
    void FloydSteinbergDither(XColorTable *colortable,
                              unsigned int bit_depth,
                              unsigned int bytes_per_line,
                              unsigned char *pixel_data);

    Pixmap renderPixmap(const Display &display, unsigned int screen);

    void raisedBevel(unsigned int border_width = 0);
    void sunkenBevel(unsigned int border_width = 0);
    void dgradient(const Color &from, const Color &to, bool interlaced);
    void egradient(const Color &from, const Color &to, bool interlaced);
    void hgradient(const Color &from, const Color &to, bool interlaced);
    void pgradient(const Color &from, const Color &to, bool interlaced);
    void rgradient(const Color &from, const Color &to, bool interlaced);
    void vgradient(const Color &from, const Color &to, bool interlaced);
    void cdgradient(const Color &from, const Color &to, bool interlaced);
    void pcgradient(const Color &from, const Color &to, bool interlaced);

    static unsigned int global_maximumColors;
    static DitherMode global_ditherMode;
  };

} // namespace bt

#endif // __Image_hh
