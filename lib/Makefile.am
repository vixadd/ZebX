# TODO - Documentation

AM_CPPFLAGS = 		@SHAPE@ @MITSHM@ @XFT@ @DEBUG@ @NLS@ \
			-DLOCALEPATH=\"$(pkgdatadir)/nls\"
lib_LTLIBRARIES = 	libbt.la
libbt_la_SOURCES = 	Application.cc					\
			Bitmap.cc					\
			Color.cc					\
			Display.cc					\
			EWMH.cc						\
			Font.cc						\
			Image.cc					\
			Menu.cc						\
			Pen.cc						\
			PixmapCache.cc					\
			Rect.cc						\
			Resource.cc					\
			Texture.cc					\
			Timer.cc					\
			Unicode.cc					\
			Util.cc						\
			XDG.cc

libbtdir = $(includedir)/bt
libbt_HEADERS = 	Application.hh					\
			Bitmap.hh					\
			Color.hh					\
			Display.hh					\
			EWMH.hh						\
			EventHandler.hh					\
			Font.hh						\
			Image.hh					\
			Menu.hh						\
			Pen.hh						\
			PixmapCache.hh					\
			Rect.hh						\
			Resource.hh					\
			Texture.hh					\
			Timer.hh					\
			Unicode.hh					\
			Util.hh						\
			XDG.hh

libbt_la_LIBADD =	@ICONV@ @LOCALE@

pkgconfigdir = 		$(libdir)/pkgconfig
nodist_pkgconfig_DATA =	libbt.pc

DISTCLEANFILES = 	*\~ *.orig *.rej .\#* *.il *.pchi
MAINTAINERCLEANFILES = 	Makefile.in
