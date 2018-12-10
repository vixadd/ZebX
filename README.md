# ZebX [![Build Status](https://travis-ci.org/vixadd/ZebX.svg?branch=master)](https://travis-ci.org/vixadd/ZebX)
ZebX is a new mechanism designed for ARM Processing computers to allow for a minimalized form of displaying information on a well organized UI.

## Built with Blackbox
An X11 Window Manager
The current source is built off of Blackbox v. 0.62.x and it integrates with all add-ons.

## Source Tree
The source tree for Blackbox is comprised of five subdirectories:

	data/		- this holds the default data files that Blackbox
                          requires for proper operation

	doc/		- this holds the documentation files that explain
	                  the various aspects of Blackbox

	nls/		- this holds the message files used to generate
			  message catalogs for different languages

	src/		- this holds the actual C++ source code for the window
			  manager.

	util/		- this holds source code for small utility programs
			  that help Blackbox do what it does best.


## Development and Deployment:
Install the following dependencies:
```bash
$ sudo apt-get install xorg xorg-dev
```
If you are running an Arch Linux distribution, the pacman package manager has 
```xorg-server-devel``` as a package under the <b>xorg</b> group. There for if you're 
running arch linux, all you need to run is:
```bash
$ sudo pacman -S xorg
```

The quickest and easiest way to get Blackbox up and running is to run the
following commands:

```bash
$ cd blackbox-version
$ ./configure
$ make
$ sudo make install
```
However, many users have said that on certain platforms they have experienced issues with this method.
For a more indepth installation, the following is valid.

Make sure that you have <b>libx11-dev</b> installed on your machine to integrate properly with the 

This will configure, compile and install Blackbox the quickest.  For those
who like to spend the extra 15 seconds reading ./configure --help, some
compile time options can be turned on and off before the build.

For general information on GNU's ./configure, see the file INSTALL.
Compilation and Installation:
--------------------------------
   The `configure' shell script attempts to guess correct values for
various system-dependent variables used during compilation.  It uses
those values to create a `Makefile' in each directory in the
Blackbox source tree.

Finally, it creates a shell script `config.status' that you can run
in the future to recreate the current configuration, a file
`config.cache' that saves the results of its tests to speed up
reconfiguring, and a file `config.log' containing compiler output
(useful mainly for debugging `configure').

   If you need to do unusual things to compile Blackbox, please try
to figure out how `configure' could check whether to do them, and mail
diffs or instructions to the blackbox mailing list so they can be considered
for the next release.  If at some point `config.cache' contains
results you don't want to keep, you may remove or edit it.

   The file `configure.in' is used to create `configure' by a program
called `autoconf'.  You only need `configure.in' if you want to change
it or regenerate `configure' using a newer version of `autoconf'.

The simplest way to compile this package is:

  1. `cd' to the directory containing the package's source code and type
     `./configure' to configure the package for your system.  If you're
     using `csh' on an old version of System V, you might need to type
     `sh ./configure' instead to prevent `csh' from trying to execute
     `configure' itself.

     Running `configure' takes awhile.  While running, it prints some
     messages telling which features it is checking for.

  2. Type `make' to compile the package.

  3. Type `make install' to install the programs and any data files and
     documentation.

  4. You can remove the program binaries and object files from the
     source code directory by typing `make clean'.  To also remove the
     files that `configure' created (so you can compile the package for
     a different kind of computer), type `make distclean'. 


Compilers and Options:
----------------------
   Some systems require unusual options for compilation or linking that
the `configure' script does not know about.  You can give `configure'
initial values for variables by setting them in the environment.  Using
a Bourne-compatible shell, you can do that on the command line like
this:
     CC=c89 CFLAGS=-O2 LIBS=-lposix ./configure

Or on systems that have the `env' program, you can do it like this:
     env CPPFLAGS=-I/usr/local/include LDFLAGS=-s ./configure

This method can also be used to add debugging support to the program:
    CXXFLAGS="-g -Wall -Winline -W -pedantic" ./configure

Optional Features:
------------------
Blackbox supports the XShape extension of X11R6.  This support is enabled by
default, but may be overridden by specifying `--disable-shape' on the configure
script's command line.

Blackbox supports a rendering effect called "faked interlacing" which darkens
every other line in rendered images.  This support works only for gradient
images.  It is compiled in by default, but may be overridden by specifying
`--disable-interlace' on the configure script's command line. 

Blackbox provides an alternative rendering algorithm for dithering on
pseudocolor (8 bit) displays. A noticeable pattern is visible when using
this; it's a matter of taste whether this looks better than the default
algorithm. It is disabled by default, but may be overridden by specifying
'--enable-ordered-pseudo' on the configure script's command line.

Blackbox uses a timer which allows it to periodically flush its pixmap
cache. It is enabled by default, but may be overridden by specifying
'--disable-timed-cache' on the configure script's command line.

Also, `configure' can usually find the X include and library files
automatically, but if it doesn't, you can use the `configure'
options `--x-includes=DIR' and `--x-libraries=DIR' to specify
their locations.


## Configuring Blackbox:
The next thing most users want to do after installing Blackbox is to configure
the colors, fonts, menus, etc. to their liking.  This is covered by the files
data/README, data/README.menu and data/README.style.  These files give
detailed information on how to customize your new window manager.


## Included utilities:
Currently, the only included utilities are a program named bsetroot and a
script called bsetbg. bsetroot is a replacement for xsetroot, minus a few
options.  The difference between xsetroot and bsetroot is that bsetroot has
been coded for multiple screens (e.g. multi-headed displays), where as the
stock xsetroot is not. The bsetbg script acts as a wrapper for most of the
popular programs used to set background pixmaps, making it possible
for styles to provide a machine-independent rootCommand.


## Third-party utilities:
With the start of the 0.60.x series Blackbox no longer handles any
keyboard shortcuts; instead it supports a communication protocol which
allows other programs to handle these and related tasks. If you'd like
to be able to use keyboard shortcuts with Blackbox, bbkeys (available at
http://http://bbkeys.sourceforge.net) can provide you with all the previous
functionality and more.
If you're looking for a GUI with which to configure your blackbox menu and/or
styles, check out http://bbconf.sourceforge.net. bbconf is a QT program that
does just that, as well as providing a GUI for editing your keybindings for the
above mentioned bbkeys.

## Supported Platforms:
ix86-Linux 2.0.x (libc5 and glibc2)
ix86-Linux 2.1.x (libc5 and glibc2)
ix86-Linux 2.2.x (libc5 and glibc2)
ix86-Linux 2.3.x (glibc2.1)
ix86-FreeBSD 4.0-current
ix86-FreeBSD 3.3-{stable,release}
ix86-FreeBSD 3.2-{stable,release}
ix86-FreeBSD 3.1-{stable,release}
ix86-FreeBSD 2.2.x-stable
ix86-NetBSD 1.3.3
ix86-NetBSD 1.4.1
ix86-OpenBSD 2.6
ix86-BSDi 4.0
PPC-mkLinux (version?)
ix86-Solaris 2.6
Sparc-Solaris 2.6 (2.5 anyone?)
Sparc-Solaris 2.7
ix86-Solaris 7 (== 2.7?)
Alpha-Digital UNIX 4.0D
Alpha-Linux 2.2.x
rs6k-AIX 4.1.3
rs6k-AIX 4.3.2
MIPS-IRIX 6.5 (requires gcc, MIPSpro didn't like some of the template-fu)
ix86-OS/2 (version? recent successes?)
hp9000/715-HP/UX 10.20 (with egcs 1.1.1)

Please email shaleh@debian.org for other success reports.

Seeking Help:

## Contact Us
[![Gitter](https://img.shields.io/gitter/room/ZebX-Blackbox/Lobby.svg)](https://gitter.im/ZebX-Blackbox)
### MAILING LISTS (Blackbox)
The mailing list archive can be found at:
http://asgardsrealm.net/lurker/splash/index.html

The mailing list addresses are:

    List posts (restricted to subscribers)
    blackbox@asgardsrealm.net

    Subscribe
    blackbox-subscribe@asgardsrealm.net
    blackbox-subscribe-john=host.domain@asgardsrealm.net

    Unsubscribe
    blackbox-unsubscribe@asgardsrealm.net
    blackbox-unsubscribe-john=host.domain@asgardsrealm.net

    List Help
    blackbox-help@asgardsrealm.net

### WEB SITES (Blackbox)
    General info:
    http://blackboxwm.sourceforge.net/
 
    Development website:
    http://sourceforge.net/projects/blackboxwm/

