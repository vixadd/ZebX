// TODO - Documentation

#ifndef __Font_hh
#define __Font_hh

#include "Unicode.hh"
#include "Util.hh"

namespace bt {

  // forward declarations
  class Display;
  class Font;
  class Pen;
  class Rect;
  class Resource;

  enum Alignment {
    AlignLeft,
    AlignCenter,
    AlignRight
  };

  unsigned int textHeight(unsigned int screen, const Font &font);

  /*
    Returns the text indent (pad).  Note that textRect() and
    drawText() use this function (so you do not have to).
  */
  unsigned int textIndent(unsigned int screen, const Font &font);

  Rect textRect(unsigned int screen, const Font &font,
                const bt::ustring &text);

  void drawText(const Font &font, const Pen &pen,
                Drawable drawable, const Rect &rect,
                Alignment alignment, const ustring &text);

  /*
   * Take a string and make it 'count' chars long by removing the
   * middle and replacing it with the string in 'ellide'.
   */
  ustring ellideText(const ustring &text, size_t count,
                     const ustring &ellide);

  /*
   * Take a string and make no more than 'max_width' pixels wide by
   * removing the middle and replacing it with the string in 'ellide'.
   * The on-screen size of the string font is determined using the
   * specified font on the specified screen.
   */
  ustring ellideText(const ustring &text,
                     unsigned int max_width,
                     const ustring &ellide,
                     unsigned int screen,
                     const bt::Font &font);

  Alignment alignResource(const Resource &resource,
                          const char* name, const char* classname,
                          Alignment default_align = AlignLeft);

  class Font {
  public:
    static void clearCache(void);

    explicit inline Font(const std::string &name = std::string())
      : _fontname(name), _fontset(0), _xftfont(0), _screen(~0u)
    { }
    inline ~Font(void)
    { unload(); }

    inline const std::string& fontName(void) const
    { return _fontname; }
    inline void setFontName(const std::string &new_fontname)
    { unload(); _fontname = new_fontname; }

    XFontSet fontSet(void) const;
    XftFont *xftFont(unsigned int screen) const;

    inline Font& operator=(const Font &f)
    { setFontName(f.fontName()); return *this; }
    inline bool operator==(const Font &f) const
    { return _fontname == f._fontname; }
    inline bool operator!=(const Font &f) const
    { return (!operator==(f)); }

  private:
    void unload(void);

    std::string _fontname;
    mutable XFontSet _fontset;
    mutable XftFont *_xftfont;
    mutable unsigned int _screen; // only used for Xft
  };

} // namespace bt

#endif // __Font_hh
