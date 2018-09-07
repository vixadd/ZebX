// TODO - Documentation


#ifndef __WindowGroup_hh
#define __WindowGroup_hh

#include <Util.hh>
#include <list>

class Blackbox;
class BScreen;
class BlackboxWindow;
typedef std::list<BlackboxWindow *> BlackboxWindowList;

class BWindowGroup {
private:
  Blackbox *blackbox;
  Window group;
  BlackboxWindowList windowList;
  BlackboxWindowList transientList;

public:
  BWindowGroup(Blackbox *b, Window _group);
  ~BWindowGroup(void);

  inline Window groupWindow(void) const
  { return group; }

  inline bool empty(void) const
  { return windowList.empty(); }

  void addWindow(BlackboxWindow *win);
  void removeWindow(BlackboxWindow *win);

  void addTransient(BlackboxWindow *win);
  void removeTransient(BlackboxWindow *win);

  inline const BlackboxWindowList &windows(void) const
  { return windowList; }
  inline const BlackboxWindowList &transients(void) const
  { return transientList; }
};

#endif // __WindowGroup_hh
