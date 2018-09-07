// TODO - Documentation

#ifndef __StackingList_hh
#define __StackingList_hh

#include <Util.hh>

#include <list>
#include <vector>

class BlackboxWindow;
class StackEntity;

typedef std::list<BlackboxWindow *> BlackboxWindowList;
typedef std::list<StackEntity *> StackEntityList;
typedef std::vector<Window> WindowStack;

class StackingList {
public:
  enum Layer {
    LayerNormal,
    LayerFullScreen,
    LayerAbove,
    LayerBelow,
    LayerDesktop
  };

  typedef StackEntityList::iterator iterator;
  typedef StackEntityList::reverse_iterator reverse_iterator;
  typedef StackEntityList::const_iterator const_iterator;
  typedef StackEntityList::const_reverse_iterator const_reverse_iterator;

  StackingList(void);

  iterator insert(StackEntity *entity);
  iterator append(StackEntity *entity);
  iterator remove(StackEntity *entity);

  iterator& layer(Layer which);
  void changeLayer(StackEntity *entity, Layer new_layer);

  iterator raise(StackEntity *entity);
  iterator lower(StackEntity *entity);

  bool empty(void) const { return (stack.size() == 5); }
  StackEntityList::size_type size(void) const { return stack.size() - 5; }
  StackEntity *front(void) const;
  StackEntity *back(void) const;
  iterator begin(void) { return stack.begin(); }
  iterator end(void) { return stack.end(); }
  reverse_iterator rbegin(void) { return stack.rbegin(); }
  reverse_iterator rend(void) { return stack.rend(); }
  const_iterator begin(void) const { return stack.begin(); }
  const_iterator end(void) const { return stack.end(); }
  const_reverse_iterator rbegin(void) const { return stack.rbegin(); }
  const_reverse_iterator rend(void) const { return stack.rend(); }

  void dump(void) const;

private:
  StackEntityList stack;
  iterator fullscreen, above, normal, below, desktop;
};

class StackEntity {
private:
  StackingList::Layer _layer;
public:
  inline StackEntity() : _layer(StackingList::LayerNormal) { }
  inline void setLayer(StackingList::Layer new_layer)
  { _layer = new_layer; }
  inline StackingList::Layer layer(void) const
  { return _layer; }
  virtual Window windowID(void) const = 0;
};

#endif // __StackingList_hh
