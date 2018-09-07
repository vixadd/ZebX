// TODO - Documentation


#ifndef   __bsetroot2_hh
#define   __bsetroot2_hh

#include <Display.hh>
#include <Image.hh>
#include <Util.hh>

#include <string>
#include <cstring>

class bsetroot: public bt::NoCopy {
public:
  bsetroot(int argc, char **argv, char *dpy_name, bool multi_head);
  virtual ~bsetroot(void);

  void setPixmapProperty(int screen, Pixmap pixmap);
  unsigned long duplicateColor(unsigned int screen, const bt::Color &color);

  void gradient(void);
  void modula(int x, int y);
  void solid(void);
  void usage(int exit_code = 0);

private:
  bt::Display display;
  std::string fore, back, grad;
};

#endif // __bsetroot2_hh
