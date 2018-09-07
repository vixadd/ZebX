// TODO - Documentation

#ifndef __XDG_hh
#define __XDG_hh

#include <list>
#include <string>
#include <algorithm>

namespace bt {

  namespace XDG {

    class BaseDir
    {
    public:
      /*
        This is an interface for basedir-spec 0.6 found at
        http://www.freedesktop.org/wiki/Standards_2fbasedir_2dspec
      */
      static std::string dataHome();
      static std::string configHome();
      static std::list<std::string> dataDirs();
      static std::list<std::string> configDirs();
      static std::string cacheHome();

      /*
        These functions return an absolute path to where a particular
        type of file can be written, creating directories as needed.
        All return an empty string if nothing can be written
        (i.e. destination directory does not exist and could not be
        created).
      */
      static std::string writeDataFile(const std::string &filename);
      static std::string writeConfigFile(const std::string &filename);
      static std::string writeCacheFile(const std::string &filename);
    };

  } // namespace XDG

} // namespace bt

#endif // __XDG_hh
