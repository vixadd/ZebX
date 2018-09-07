// TODO - Documentation

#include "Util.hh"

#include <algorithm>

#include <X11/Xatom.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#if defined(__EMX__)
#  include <process.h>
#endif // __EMX__
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


std::string bt::basename(const std::string& path) {
  std::string::size_type slash = path.rfind('/');
  if (slash == std::string::npos)
    return path;
  return path.substr(slash+1);
}


std::string bt::dirname(const std::string& path) {
  std::string::size_type slash = path.rfind('/');
  if (slash == std::string::npos)
    return path;
  std::string::const_iterator it = path.begin();
  return std::string(it, it + slash);
}


bool bt::mkdirhier(const std::string &path, int mode)
{
  /*
    POSIX says this about mkdir(1) -p:

    <quote>
    Create any missing intermediate pathname components.  For each
    dir operand that does not name an existing directory, effects
    equivalent to those caused by the following command shall occur:

    mkdir -p -m $(umask -S),u+wx $(dirname dir) && mkdir [-m mode] dir

    where the -m mode option represents that option supplied to the
    original invocation of mkdir, if any.

    Each dir operand that names an existing directory shall be
    ignored without error.
    </quote>

    We do this by changing the umask.  It is restored before creating
    the final component of the path or, in the case of an error,
    before returning.
  */
  // save umask
  mode_t save_umask = umask(0);
  mode_t tmp_umask = save_umask & ~(S_IWUSR | S_IXUSR);
  bool umask_restored = false;
  (void) umask(tmp_umask);

  bool success = true;
  const std::string::const_iterator begin = path.begin();
  const std::string::const_iterator end = path.end();
  std::string::const_iterator it = begin;
  for (; it != end;) {
    if ((it + 1) == end) {
      break;
    }
    it = std::find(it + 1, end, '/');
    if (it == end || (it + 1) == end) {
      (void) umask(save_umask);
      umask_restored = true;
      // make sure we use the right mode to mkdir(2)
      it = end;
    }

    std::string p(begin, it);
    if (mkdir(p.c_str(), it == end ? mode : 0777) != 0) {
      const int e = errno;
      struct stat st;
      if (stat(p.c_str(), &st) != 0) {
        errno = e;
        success = false;
        break;
      } else if (!S_ISDIR(st.st_mode)) {
        errno = ENOTDIR;
        success = false;
        break;
      }
    }
  }

  // restore umask
  if (!umask_restored)
    (void) umask(save_umask);

  return success;
}


std::string bt::expandTilde(const std::string& s) {
  if (s[0] != '~')
    return s;
  const char* const home = getenv("HOME");
  if (home == NULL)
    return s;
  return std::string(home + s.substr(s.find('/')));
}


void bt::bexec(const std::string& command, const std::string& displaystring) {
#ifndef    __EMX__
  if (!fork()) {
#ifndef __QNXTO__ // apparently, setsid interferes with signals on QNX
    setsid();
#endif
    int ret = putenv(const_cast<char *>(displaystring.c_str()));
    assert(ret != -1);
    std::string cmd = "exec ";
    cmd += command;
    ret = execl("/bin/sh", "/bin/sh", "-c", cmd.c_str(), NULL);
    exit(ret);
  }
#else //   __EMX__
  spawnlp(P_NOWAIT, "cmd.exe", "cmd.exe", "/c", command.c_str(), NULL);
#endif // !__EMX__
}


std::string bt::itostring(unsigned long i) {
  if (i == 0)
    return std::string("0");

  const char nums[] = "0123456789";

  std::string tmp;
  for (; i > 0; i /= 10)
    tmp.insert(tmp.begin(), nums[i%10]);
  return tmp;
}


std::string bt::itostring(long i) {
  std::string tmp = bt::itostring(static_cast<unsigned long>(abs(i)));
  if (i < 0)
    tmp.insert(tmp.begin(), '-');
  return tmp;
}


std::string bt::tolower(const std::string &string)
{
  std::string returnValue;
  returnValue.reserve(string.size());
  std::string::const_iterator it = string.begin();
  const std::string::const_iterator end = string.end();
  for (; it != end; ++it)
    returnValue.push_back(::tolower(*it));
  return returnValue;
}

/*
 * Takes an XTextProperty and returns
 * it's string value.
 */
std::string bt::textPropertyToString(::Display *display,
                                     ::XTextProperty& text_prop) {
  std::string ret;

  if (text_prop.value && text_prop.nitems > 0) {
    if (text_prop.encoding == XA_STRING) {
      ret = reinterpret_cast<char *>(text_prop.value);
    } else {
      text_prop.nitems = strlen(reinterpret_cast<char *>(text_prop.value));

      char **list;
      int num;
      if (XmbTextPropertyToTextList(display, &text_prop,
                                    &list, &num) == Success &&
          num > 0 && *list) {
        ret = *list;
        XFreeStringList(list);
      }
    }
  }

  return ret;
}
