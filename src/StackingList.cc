// TODO - Documentation

#include "StackingList.hh"
#include "Window.hh"

#include <Unicode.hh>

#include <cassert>
#include <cstdio>


static StackEntity * const zero = 0;


StackingList::StackingList(void) {
  desktop = stack.insert(stack.begin(), zero);
  below = stack.insert(desktop, zero);
  normal = stack.insert(below, zero);
  above = stack.insert(normal, zero);
  fullscreen = stack.insert(above, zero);
}


StackingList::iterator StackingList::insert(StackEntity *entity) {
  assert(entity);

  iterator& it = layer(entity->layer());
  it = stack.insert(it, entity);
  return it;
}


StackingList::iterator StackingList::append(StackEntity *entity) {
  assert(entity);

  iterator& it = layer(entity->layer());
  if (!*it) { // empty layer
    it = stack.insert(it, entity);
    return it;
  }

  // find the end of the layer (the zero pointer)
  iterator tmp = std::find(it, stack.end(), zero);
  assert(tmp != stack.end());
  tmp = stack.insert(tmp, entity);
  return tmp;
}


StackingList::iterator StackingList::remove(StackEntity *entity) {
  assert(entity);

  iterator& pos = layer(entity->layer());
  iterator it = std::find(pos, stack.end(), entity);
  assert(it != stack.end());
  if (it == pos) ++pos;
  it = stack.erase(it);
  assert(stack.size() >= 5);
  return it;
}


StackingList::iterator& StackingList::layer(Layer which) {
  switch (which) { // teehee
  case LayerNormal:
    return normal;
  case LayerFullScreen:
    return fullscreen;
  case LayerAbove:
    return above;
  case LayerBelow:
    return below;
  case LayerDesktop:
    return desktop;
  }

  assert(0);
  return normal;
}


void StackingList::changeLayer(StackEntity *entity, Layer new_layer) {
  assert(entity);

  (void) remove(entity);
  entity->setLayer(new_layer);
  (void) insert(entity);
}


StackingList::iterator StackingList::raise(StackEntity *entity) {
  assert(entity);

  // find the top of the layer and 'entity'
  iterator& pos = layer(entity->layer());
  const iterator send = stack.end();
  iterator it = std::find(pos, send, entity);
  assert(it != send);

  if (it == pos) {
    // entity is already at the top
    return pos;
  }

  // raise the entity
  (void) stack.erase(it);
  return pos = stack.insert(pos, entity);
}


StackingList::iterator StackingList::lower(StackEntity *entity) {
  assert(entity);

  // find the top of the layer and 'entity'
  iterator& pos = layer(entity->layer());
  const iterator send = stack.end();
  iterator it = std::find(pos, send, entity);
  assert(it != send);

  iterator next = it;
  ++next;
  assert(next != send);
  if (!(*next)) {
    // entity is already at the bottom
    return it;
  }

  if (it == pos) {
    // entity is at the top of the layer, adjust the layer iterator to
    // the next entity
    ++pos;
  }
  assert((*pos));

  // lower the entity
  (void) stack.erase(it);
  it = std::find(pos, send, zero);
  assert(it != send);
  return stack.insert(it, entity);
}


StackEntity *StackingList::front(void) const {
  assert(stack.size() > 5);

  if (*fullscreen) return *fullscreen;
  if (*above) return *above;
  if (*normal) return *normal;
  if (*below) return *below;
  // we do not return desktop entities
  assert(0);

  // this point is never reached, but the compiler doesn't know that.
  return zero;
}


StackEntity *StackingList::back(void) const {
  assert(stack.size() > 5);

  const_iterator it = desktop, _end = stack.begin();
  for (--it; it != _end; --it) {
    if (*it) return *it;
  }

  assert(0);
  return zero;
}


static void print_entity(StackEntity *entity)
{
  BlackboxWindow *win = dynamic_cast<BlackboxWindow *>(entity);
  if (win) {
    fprintf(stderr, "  0x%lx: window 0x%lx %p '%s'\n",
            win->windowID(), win->clientWindow(), win,
            bt::toLocale(win->title()).c_str());
  } else if (entity) {
    fprintf(stderr, "  0x%lx: %p unknown entity\n",
            entity->windowID(), entity);
  } else {
    fprintf(stderr, "  zero\n");
  }
}


void StackingList::dump(void) const {
  const_iterator it = stack.begin(), _end = stack.end();
  fprintf(stderr, "Stack:\n");
  for (; it != _end; ++it)
    print_entity(*it);

  fprintf(stderr, "Layers:\n");
  print_entity(*fullscreen);
  print_entity(*above);
  print_entity(*normal);
  print_entity(*below);
  print_entity(*desktop);
}
