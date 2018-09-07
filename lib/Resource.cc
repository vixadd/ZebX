// TODO - Documentation

#include "Resource.hh"
#include "Util.hh"

#include <X11/Xlib.h>
#include <X11/Xresource.h>
#include <strings.h>

#include <stdio.h>


bt::Resource::Resource(void)
  : db(NULL)
{ }


bt::Resource::Resource(const std::string &filename)
  : db(NULL)
{ load(filename); }


bt::Resource::~Resource(void)
{ XrmDestroyDatabase(db); }


void bt::Resource::load(const std::string &filename)
{
  XrmDestroyDatabase(db);
  if (!filename.empty())
    db = XrmGetFileDatabase(expandTilde(filename).c_str());
  else
    db = NULL;
}


void bt::Resource::save(const std::string &filename)
{
  if (!valid() || filename.empty())
    return;
  XrmPutFileDatabase(db, expandTilde(filename).c_str());
}


void bt::Resource::merge(const std::string &filename)
{
  if (filename.empty())
    return;
  XrmCombineFileDatabase(expandTilde(filename).c_str(), &db, false);
}


std::string bt::Resource::read(const char* name, const char* classname,
                               const char* default_value) const {
  XrmValue value;
  char *value_type;
  if (XrmGetResource(db, name, classname, &value_type, &value))
    return std::string(value.addr, value.size - 1);
  return std::string(default_value);
}


std::string bt::Resource::read(const std::string& name,
                               const std::string& classname,
                               const std::string& default_value) const {
  XrmValue value;
  char *value_type;
  if (XrmGetResource(db, name.c_str(), classname.c_str(),
                     &value_type, &value))
    return std::string(value.addr, value.size - 1);
  return default_value;
}


int bt::Resource::read(const char* name, const char* classname,
                       int default_value) const {
  XrmValue value;
  char *value_type;
  if (XrmGetResource(db, name, classname, &value_type, &value)) {
    int output;
    sscanf(value.addr, "%d", &output);
    return output;
  }
  return default_value;
}


unsigned int bt::Resource::read(const char* name, const char* classname,
                                unsigned int default_value) const {
  XrmValue value;
  char *value_type;
  if (XrmGetResource(db, name, classname, &value_type, &value)) {
    unsigned int output;
    sscanf(value.addr, "%u", &output);
    return output;
  }
  return default_value;
}


long bt::Resource::read(const char* name, const char* classname,
                        long default_value) const {
  XrmValue value;
  char *value_type;
  if (XrmGetResource(db, name, classname, &value_type, &value)) {
    long output;
    sscanf(value.addr, "%ld", &output);
    return output;
  }
  return default_value;
}


unsigned long bt::Resource::read(const char* name, const char* classname,
                                 unsigned long default_value) const {
  XrmValue value;
  char *value_type;
  if (XrmGetResource(db, name, classname, &value_type, &value)) {
    unsigned long output;
    sscanf(value.addr, "%lu", &output);
    return output;
  }
  return default_value;
}


bool bt::Resource::read(const char* name, const char* classname,
                        bool default_value) const {
  XrmValue value;
  char *value_type;
  if (XrmGetResource(db, name, classname, &value_type, &value)) {
    if (strncasecmp(value.addr, "true", value.size) == 0)
      return true;
    return false;
  }
  return default_value;
}


double bt::Resource::read(const char* name, const char* classname,
                          double default_value) const {
  XrmValue value;
  char *value_type;
  if (XrmGetResource(db, name, classname, &value_type, &value)) {
    double output;
    sscanf(value.addr, "%lf", &output);
    return output;
  }
  return default_value;
}


void bt::Resource::write(const char *resource, const std::string &value)
{ write(resource, value.c_str()); }


void bt::Resource::write(const char* resource, const char* value)
{ XrmPutStringResource(&db, resource, value); }


void bt::Resource::write(const char* resource, int value) {
  char tmp[16];
  sprintf(tmp, "%d", value);
  write(resource, tmp);
}


void bt::Resource::write(const char* resource, unsigned int value) {
  char tmp[16];
  sprintf(tmp, "%u", value);
  write(resource, tmp);
}


void bt::Resource::write(const char* resource, long value) {
  char tmp[64];
  sprintf(tmp, "%ld", value);
  write(resource, tmp);
}


void bt::Resource::write(const char* resource, unsigned long value) {
  char tmp[64];
  sprintf(tmp, "%lu", value);
  write(resource, tmp);
}


void bt::Resource::write(const char* resource, bool value)
{ write(resource, boolAsString(value)); }


void bt::Resource::write(const char* resource, double value) {
  char tmp[80];
  sprintf(tmp, "%f", value);
  write(resource, tmp);
}
