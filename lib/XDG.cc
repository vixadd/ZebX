// TODO - Documentation


#include "Util.hh"
#include "XDG.hh"

#include <stdlib.h>


// make sure directory names end with a slash
static std::string terminateDir(const std::string &string)
{
  std::string returnValue = string;
  std::string::const_iterator it = returnValue.end() - 1;
  if (*it != '/')
    returnValue += '/';
  return returnValue;
}

static std::string readEnvDir(const char *name, const char *defaultValue)
{
  const char * const env = getenv(name);
  std::string returnValue = std::string(env ? env : defaultValue);
  returnValue = bt::expandTilde(returnValue);
  return terminateDir(returnValue);
}

static std::list<std::string> readEnvDirList(const char *name,
                                             const char *defaultValue)
{
  const char * const env = getenv(name);

  std::string str = env ? env : defaultValue;
  // if the environment variable ends with a ':', append the
  // defaultValue
  std::string::const_iterator last = str.end() - 1;
  if (*last == ':')
    str += defaultValue;

  std::list<std::string> returnValue;
  const std::string::const_iterator end = str.end();
  std::string::const_iterator begin = str.begin();
  do {
    std::string::const_iterator it = std::find(begin, end, ':');
    std::string dir = std::string(begin, it);
    dir = bt::expandTilde(dir);
    dir = terminateDir(dir);
    returnValue.push_back(dir);
    begin = it;
    if (begin != end)
      ++begin;
  } while (begin != end);

  return returnValue;
}


std::string bt::XDG::BaseDir::dataHome()
{
  static std::string XDG_DATA_HOME =
    readEnvDir("XDG_DATA_HOME", "~/.local/share/");
  return XDG_DATA_HOME;
}

std::string bt::XDG::BaseDir::configHome()
{
  static std::string XDG_CONFIG_HOME =
    readEnvDir("XDG_CONFIG_HOME", "~/.config/");
  return XDG_CONFIG_HOME;
}

std::list<std::string> bt::XDG::BaseDir::dataDirs()
{
  static std::list<std::string> XDG_DATA_DIRS =
    readEnvDirList("XDG_DATA_DIRS", "/usr/local/share/:/usr/share/");
  return XDG_DATA_DIRS;
}

std::list<std::string> bt::XDG::BaseDir::configDirs()
{
  static std::list<std::string> XDG_CONFIG_DIRS =
    readEnvDirList("XDG_CONFIG_DIRS", "/etc/xdg/");
  return XDG_CONFIG_DIRS;
}

std::string bt::XDG::BaseDir::cacheHome()
{
  static std::string XDG_CACHE_HOME =
    readEnvDir("XDG_CACHE_HOME", "~/.cache/");
  return XDG_CACHE_HOME;
}

std::string bt::XDG::BaseDir::writeDataFile(const std::string &filename)
{
  std::string path = dataHome() + filename;
  std::string directoryName = dirname(path);
  if (!mkdirhier(directoryName, 0700))
    return std::string();
  return path;
}

std::string bt::XDG::BaseDir::writeConfigFile(const std::string &filename)
{
  std::string path = configHome() + filename;
  std::string directoryName = dirname(path);
  if (!mkdirhier(directoryName, 0700))
    return std::string();
  return path;
}

std::string bt::XDG::BaseDir::writeCacheFile(const std::string &filename)
{
  std::string path = cacheHome() + filename;
  std::string directoryName = dirname(path);
  if (!mkdirhier(directoryName, 0700))
    return std::string();
  return path;
}
