// TODO - Documentation


#ifndef __Texture_hh
#define __Texture_hh

#include "Color.hh"
#include "Util.hh"

namespace bt {

  // forward declarations
  class Rect;
  class Resource;
  class Texture;

  void drawTexture(unsigned int screen,
                   const Texture &texture,
                   Drawable drawable,
                   const Rect &trect,
                   const Rect &urect,
                   Pixmap pixmap = 0ul);

  /*
    If 'name.appearance' cannot be found, a flat solid texture in the
    defaultColor is returned; otherwise, the texture is read.  All
    missing colors are set to the defaultColor.
   */
  Texture
  textureResource(const Display &display,
                  unsigned int screen,
                  const Resource &resource,
                  const std::string &name,
                  const std::string &className,
                  const std::string &defaultColor = "black");

  /*
    If 'name.appearance' cannot be found, the defaultTexture is
    returned; otherwise, the above function is called with the passed
    arguments.
   */
  Texture
  textureResource(const Display &display,
                  unsigned int screen,
                  const Resource &resource,
                  const std::string &name,
                  const std::string &className,
                  const Texture &defaultTexture);

  class Texture {
  public:
    enum Type {
      // bevel options
      Flat                = (1l<<0),
      Sunken              = (1l<<1),
      Raised              = (1l<<2),
      // textures
      Solid               = (1l<<3),
      Gradient            = (1l<<4),
      // gradients
      Horizontal          = (1l<<5),
      Vertical            = (1l<<6),
      Diagonal            = (1l<<7),
      CrossDiagonal       = (1l<<8),
      Rectangle           = (1l<<9),
      Pyramid             = (1l<<10),
      PipeCross           = (1l<<11),
      Elliptic            = (1l<<12),
      // parent relative image
      Parent_Relative     = (1l<<13),
      // fake interlaced image
      Interlaced          = (1l<<14),
      // border around image
      Border              = (1l<<15)
    };

    inline Texture(void)
      : t(0ul), bw(0u)
    { }
    inline Texture(const Texture &tt)
    { *this = tt; }

    inline const std::string &description(void) const
    { return descr; }
    void setDescription(const std::string &d);

    void setColor1(const Color &new_color);
    inline void setColor2(const Color &new_color)
    { c2 = new_color; }
    inline void setBorderColor(const Color &new_borderColor)
    { bc = new_borderColor; }

    inline const Color &color1(void) const
    { return c1; }
    inline const Color &color2(void) const
    { return c2; }
    inline const Color &borderColor(void) const
    { return bc; }
    inline const Color &lightColor(void) const
    { return lc; }
    inline const Color &shadowColor(void) const
    { return sc; }

    inline unsigned long texture(void) const
    { return t; }
    inline void setTexture(unsigned long _texture)
    { t  = _texture; }
    inline void addTexture(unsigned long _texture)
    { t |= _texture; }

    inline unsigned int borderWidth(void) const
    { return bw; }
    inline void setBorderWidth(unsigned int new_bw)
    { bw = new_bw; }

    Texture &operator=(const Texture &tt);
    inline bool operator==(const Texture &tt) const {
      return (c1 == tt.c1 && c2 == tt.c2 && bc == tt.bc &&
              lc == tt.lc && sc == tt.sc && t == tt.t && bw == tt.bw);
    }
    inline bool operator!=(const Texture &tt) const
    { return (!operator==(tt)); }

  private:
    std::string descr;
    Color c1, c2, bc, lc, sc;
    unsigned long t;
    unsigned int bw;
  };

} // namespace bt

#endif // __Texture_hh
