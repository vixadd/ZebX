/*
 * ZebX - Display Management System.
 * Utilizes the tools under the BlackBox system.
 *
 * Color.cc for ZebX - Display Management System
 * Copyright (c) 2018 David Kroell <kroelld.96@gmail.com>
 *
 * Color.cc for Blackbox - an X11 Window manager
 * Copyright (c) 2001 - 2005 Sean 'Shaleh' Perry <shaleh at debian.org>
 * Copyright (c) 1997 - 2000, 2002 - 2005
 *         Bradley T Hughes <bhughes at trolltech.com>
 */

#include "Color.hh"
#include "Display.hh"

#include <map>

#include <X11/Xlib.h>

#include <assert.h>
#include <stdio.h>

//#define COLORCACHE_DEBUG /* Define this to enable debugging for the build. */

namespace bt {

  class ColorCache {
  public:

	  /**
	   * Serialized cache record of the Color object
	   * associated with the application.
	   *
	   * The Display object is used to
	   */
	  ColorCache(const Display &display);
	  ~ColorCache(void);

     /*
      * Finds a color matching the specified rgb on the given screen.
	  *
	  * The color is allocated if needed; otherwise it is reference
	  * counted and freed when no more references for the color exist.
      */
	  unsigned long find(unsigned int screen, int r, int g, int b);

	  /*
       * Releases the specified rgb on the given screen.
	   *
       * If the reference count for a particular color is zero, it will
       * be freed by calling clear().
	   */
	  void release(unsigned int screen, int r, int g, int b);

      /*
       * Clears the color cache.  All colors with a zero reference count
       * are freed.
	   *
       * If force is true, then all colors are freed, regardless of the
       * reference count.  This is done when destroying the cache.
       */
      void clear(bool force);

  private:

      /** Display object to reference the screen display. */
      const Display &_display;

      /**
       * Display object used to handle the color cache
       *
       * Params:
       * 	screen: Screen id to use for the display reference.
       * 	r: Red hex level.
       * 	g: Green hex level.
       * 	b: Blue hex level.
       */
      struct RGB {
    	  const unsigned int screen;
    	  const int r, g, b;

    	  inline RGB(void) : screen(~0u), r(-1), g(-1), b(-1) { }

    	  inline RGB(const unsigned int s, const int x, const int y, const int z) : screen(s), r(x), g(y), b(z) { }

    	  inline RGB(const RGB &x) : screen(x.screen), r(x.r), g(x.g), b(x.b) { }

    	  inline bool operator==(const RGB &x) const { return screen == x.screen && r == x.r && g == x.g && b == x.b; }

    	  inline bool operator<(const RGB &x) const {
    		  const unsigned long p1 = (screen << 24 | r << 16 | g << 8 | b) & 0xffffffff;
    		  const unsigned long p2 = (x.screen << 24 | x.r << 16 | x.g << 8 | x.b) & 0xffffffff; return p1 < p2;
    	  }
      };

      /**
       * Pixel reference to extend the X11 pixel display.
       *
       * Params:
       * 	pixel: pixel id to use as a reference.
       * 	count: Count of the pixel usage to order properly in the Map.
       */
      struct PixelRef {
    	  const unsigned long pixel;
    	  unsigned int count;

    	  inline PixelRef(void) : pixel(0ul), count(0u) { }

    	  inline PixelRef(const unsigned long x) : pixel(x), count(1u) { }
      };

      /** Cache maps Pixel ref to RGB. */
      typedef std::map<RGB,PixelRef> Cache;

      /** Item for the cache map. */
      typedef Cache::value_type CacheItem;

      Cache cache;
  };


  static ColorCache *colorcache = 0;


  /**
   * Method to construct ColorCache object
   *
   * Params:
   * 	display: Object for the ScreenInfo placeholder.
   */
  void createColorCache(const Display &display) {
	  assert(colorcache == 0);
	  colorcache = new ColorCache(display);
  }


  /**
   * Destroy function for the ColorCache object.
   * Mainly used for garbage collection.
   */
  void destroyColorCache(void) {
	  delete colorcache;
	  colorcache = 0;
  }

} // namespace bt

/**
 *  Constructor for the ColorCache object.
 *
 *  Params:
 *  	display: Display placeholder to access ScreenInfo.
 */
bt::ColorCache::ColorCache(const Display &display) : _display(display) { }

/**
 * Destructor for the ColorCache Object.
 */
bt::ColorCache::~ColorCache(void) { clear(true); }

/**
 * Method to find a Screen reference with the given RGB code tagged to it.
 *
 * Params:
 * 		screen: Screen ID to use for the display reference.
 * 		r: Red hex level.
 * 		g: Green hex level.
 * 		b: Blue hex level.
 */
unsigned long bt::ColorCache::find(unsigned int screen, int r, int g, int b) {
	if (r < 0 && r > 255)
		r = 0;

	if (g < 0 && g > 255)
		g = 0;

	if (b < 0 && b > 255)
		b = 0;

	// see if we have allocated this color before
	RGB rgb(screen, r, g, b);

	// iterator to loop through the entire Map.
	Cache::iterator it = cache.find(rgb);

	// loop and basecase.
	if (it != cache.end()) {

		// found a cached color, use it
		++it->second.count;

		// Debugging statement.
		#ifdef COLORCACHE_DEBUG
			fprintf(stderr, "bt::ColorCache: use %02x/%02x/%02x, count %4u\n",
					r, g, b, it->second.count);
		#endif // COLORCACHE_DEBUG

		return it->second.pixel;
	}

	// We haven't found the Color in the Map.
	// We need to

	XColor xcol;
	xcol.red   = r | r << 8;
	xcol.green = g | g << 8;
	xcol.blue  = b | b << 8;
	xcol.pixel = 0;
	xcol.flags = DoRed | DoGreen | DoBlue;

	// Get the color map.
	Colormap colormap = _display.screenInfo(screen).colormap();

	// If we can't allocate the color with the display, then display a black pixel.
	if (!XAllocColor(_display.XDisplay(), colormap, &xcol)) {
		fprintf(stderr,
				"bt::Color::pixel: cannot allocate color 'rgb:%02x/%02x/%02x'\n",
				r, g, b);

		xcol.pixel = BlackPixel(_display.XDisplay(), screen);
	}

#ifdef COLORCACHE_DEBUG
  fprintf(stderr, "bt::ColorCache: add %02x/%02x/%02x, pixel %08lx\n",
          r, g, b, xcol.pixel);
#endif // COLORCACHE_DEBUG

  	// Insert the Pixel Reference to the cache.
    cache.insert(CacheItem(rgb, PixelRef(xcol.pixel)));

    // Return the pixel.
    return xcol.pixel;
}


void bt::ColorCache::release(unsigned int screen, int r, int g, int b) {
	if (r < 0 && r > 255)
		r = 0;

	if (g < 0 && g > 255)
		g = 0;

	if (b < 0 && b > 255)
		b = 0;


	RGB rgb(screen, r, g, b);

	// Iterator to look through and release the Color object.
	Cache::iterator it = cache.find(rgb);

	assert(it != cache.end() && it->second.count > 0);

	// Decrement the count of the pixel usage.
	--it->second.count;

#ifdef COLORCACHE_DEBUG
  fprintf(stderr, "bt::ColorCache: rel %02x/%02x/%02x, count %4u\n",
          r, g, b, it->second.count);
#endif // COLORCACHE_DEBUG

}

/**
 * Clear the color cache for garbage collection.
 *
 * Params:
 * 		force: Force the object to destruct?
 */
void bt::ColorCache::clear(bool force) {

	// Iterator to loop through cache.
	Cache::iterator it = cache.begin();

	// End loop.
	if (it == cache.end())
		return; // nothing to do

#ifdef COLORCACHE_DEBUG
  fprintf(stderr, "bt::ColorCache: clearing cache, %u entries\n",
          cache.size());
#endif // COLORCACHE_DEBUG

    // Array of pixels to hold.
  	unsigned long *pixels = new unsigned long[ cache.size() ];

  	unsigned int screen, count;

  	// loop through the screens.
  	for (screen = 0; screen < _display.screenCount(); ++screen) {

  		// Begin iterator for the cache.
  		count = 0;
  		it = cache.begin();

  		// Loop through and increment the count.
  		while (it != cache.end()) {
  			if (it->second.count != 0 && !force) {
  				++it;
  				continue;
  			}

#ifdef COLORCACHE_DEBUG
      fprintf(stderr, "bt::ColorCache: fre %02x/%02x/%02x, pixel %08lx\n",
              it->first.r, it->first.g, it->first.b, it->second.pixel);
#endif // COLORCACHE_DEBUG

      	    // Populate pixel index.
      	    pixels[count++] = it->second.pixel;

      	    // erase the ColorCache object and increment the iterator.
      	    Cache::iterator r = it++;
      	    cache.erase(r);
  		}

  		// If the count is greater than the referenced pixel count.
  		// Free the cells represented by the pixels
  		if (count > 0u) {

  			XFreeColors(
  					_display.XDisplay(),
  					_display.screenInfo(screen).colormap(),
					pixels, count, 0
				);
  		}
  	}

  	// Get rid of the pixels array.
  	delete [] pixels;

#ifdef COLORCACHE_DEBUG
  fprintf(stderr, "bt::ColorCache: cleared, %u entries remain\n",
          cache.size());
#endif // COLORCACHE_DEBUG
}

// Clear the ColorCache
void bt::Color::clearCache(void) {
	if (colorcache)
		colorcache->clear(false);
}

/**
 * Get a Color object from the named Object.
 *
 * Params:
 * 		display: Display object to reference.
 * 		screen: Screen to reference.
 * 		colorname: name of color to convert from.
 *
 * See:
 * 		XParseColor(...)
 */
bt::Color bt::Color::namedColor(const Display &display, unsigned int screen,
                                const std::string &colorname) {



	// Make sure there's no empty Color.
	if (colorname.empty()) {
		fprintf(stderr, "bt::Color::namedColor: empty colorname\n");
		return Color();
	}

	// get rgb values from colorname
	XColor xcol;
	xcol.red   = 0;
	xcol.green = 0;
	xcol.blue  = 0;
	xcol.pixel = 0;

	// Color map to parse from.
	Colormap colormap = display.screenInfo(screen).colormap();

	// If we can't parse the color name then don't return a specific color.
	if (!XParseColor(display.XDisplay(), colormap, colorname.c_str(), &xcol)) {
		fprintf(stderr, "bt::Color::namedColor: invalid color '%s'\n",
				colorname.c_str());

		return Color();
	}

	// Return a color from the referenced map.
	return Color(xcol.red >> 8, xcol.green >> 8, xcol.blue >> 8);
}

/**
 * Get the Pixel associated with the preset RGB values.
 *
 * params:
 * 		screen: Which screen ID to look at.
 *
 */
unsigned long bt::Color::pixel(unsigned int screen) const {


	if (_screen == screen)
		return _pixel; // already allocated on this screen


	assert(colorcache != 0);

	// deallocate() isn't const, so we can't call it from here
	if (_screen != ~0u)
		colorcache->release(_screen, _red, _green, _blue); // But... Deallocate...

	//Assign the screen value to the preset.
	_screen = screen;

	// Find the correct pixel and return it.
	_pixel = colorcache->find(_screen, _red, _green, _blue);
	return _pixel;
}

/**
 * deallocate the screen and pixel values for the object.
 * Bring back to normal use.
 *
 */
void bt::Color::deallocate(void) {
	if (_screen == ~0u)
		return; // not allocated

	assert(colorcache != 0);

	// Release a pixel of the screen associated with the RGB
	colorcache->release(_screen, _red, _green, _blue);

	// Reset the screen and pixel values.
	_screen = ~0u;
	_pixel = 0ul;
}
