// TODO - Documentation

#ifndef __Bitmap_hh
#define __Bitmap_hh

#include "Util.hh"

namespace bt {

  // forward declarations
  class Bitmap;
  class Display;
  class Pen;
  class Rect;

  /*
    Draws the specified bitmap with the specified pen on the specified
    drawable in the specified area.  Note: the bitmap will be drawn
    using the color of the pen.
   */
  void drawBitmap(const Bitmap &bitmap, const Pen &pen,
                  ::Drawable drawable, const Rect &rect);

  /*
    The bitmap object.  You can create custom bitmaps from raw data,
    or use one of 5 standard bitmaps.
   */
  class Bitmap : public NoCopy {
  public:

	/*
	 * Standard Bitmaps up for reuse.
	 */
    static const Bitmap &leftArrow(unsigned int screen);
    static const Bitmap &rightArrow(unsigned int screen);
    static const Bitmap &upArrow(unsigned int screen);
    static const Bitmap &downArrow(unsigned int screen);
    static const Bitmap &checkMark(unsigned int screen);

    /*
     * inline Constructor for a new Bitmap.
     *
     * This will set the screen and drawables automatically
     * based on what's referenced in memory.
     */
    inline Bitmap(void)
      : _screen(~0u), _drawable(0ul), _width(0u), _height(0u)
    { }


    /* CONSTRUCTOR */
    Bitmap(unsigned int scr, const unsigned char *data,
           unsigned int w, unsigned int h);

    /* DESTRUCTOR: BITMAP */
    ~Bitmap(void);

    /*
     * Load function will load the Bitmap display to memory
     * This logs the height and width and accompanying data.
     */
    bool load(unsigned int scr, const unsigned char *data,
              unsigned int w, unsigned int h);

    // GETTER: _screen
    inline unsigned int screen(void) const
    { return _screen; }

    // GETTER: _drawable
    inline ::Drawable drawable(void) const
    { return _drawable; }

    // GETTER: _width
    inline unsigned int width(void) const
    { return _width; }

    // GETTER: _height
    inline unsigned int height(void) const
    { return _height; }

  /* Private Variables encapsulated in getters. */
  private:
   	unsigned int _screen;
   	::Drawable _drawable;
   	unsigned int _width, _height;
  };

} // namespace bt

#endif // __Bitmap_hh
