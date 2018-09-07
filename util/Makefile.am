#---------------------------------------------------#
#              Makefile.am - ZebX                   #
#                                                   #
#                                                   #
#              Author: David Kroell                 #
#             Created: 2018                         #
#---------------------------------------------------#

CPPFLAGS		= @CPPFLAGS@ @DEBUG@ @NLS@ \
			  -I$(top_srcdir)/lib

bin_SCRIPTS		= bsetbg
bin_PROGRAMS		= bsetroot bstyleconvert

bsetroot_SOURCES	= bsetroot.cc
bsetroot_DEPENDENCIES	= $(top_builddir)/lib/libbt.la
bsetroot_LDADD		= $(top_builddir)/lib/libbt.la

bstyleconvert_SOURCES		= bstyleconvert.cc
bstyleconvert_DEPENDENCIES	= $(top_builddir)/lib/libbt.la
bstyleconvert_LDADD		= $(top_builddir)/lib/libbt.la

MAINTAINERCLEANFILES	= Makefile.in

distclean-local:
	rm -f *\~ *.orig *.rej .\#*
