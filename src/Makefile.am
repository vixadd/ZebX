## TODO - Documentation

DEFAULT_MENU		= $(pkgdatadir)/menu
DEFAULT_STYLE		= $(pkgdatadir)/styles/Gray
CPPFLAGS		= @CPPFLAGS@ @SHAPE@ @XFT@ @DEBUG@ @NLS@ \
			  -DLOCALEPATH=\"$(pkgdatadir)/nls\" \
			  -DDEFAULTMENU=\"$(DEFAULT_MENU)\" \
			  -DDEFAULTSTYLE=\"$(DEFAULT_STYLE)\" \
			  -I$(top_srcdir)/lib
bin_PROGRAMS		= blackbox
blackbox_SOURCES	= BlackboxResource.cc                           \
                          Clientmenu.cc					\
			  Configmenu.cc					\
			  Iconmenu.cc					\
			  Rootmenu.cc					\
			  Screen.cc					\
			  ScreenResource.cc				\
			  Slit.cc					\
			  Slitmenu.cc					\
			  StackingList.cc				\
			  Toolbar.cc					\
			  Toolbarmenu.cc				\
			  Window.cc					\
			  WindowGroup.cc				\
			  Windowmenu.cc					\
			  Workspace.cc					\
			  Workspacemenu.cc				\
			  blackbox.cc					\
			  main.cc
blackbox_DEPENDENCIES	= $(top_builddir)/lib/libbt.la
blackbox_LDADD		= $(top_builddir)/lib/libbt.la

MAINTAINERCLEANFILES	= Makefile.in

distclean-local:
	rm -f *\~ *.orig *.rej .\#*
