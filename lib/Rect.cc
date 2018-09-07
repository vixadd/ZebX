// TODO - Documentation

#include "Rect.hh"

#include <algorithm>


void bt::Rect::setX(int x_) {
  _x2 += x_ - _x1;
  _x1 = x_;
}


void bt::Rect::setY(int y_)
{
  _y2 += y_ - _y1;
  _y1 = y_;
}


void bt::Rect::setPos(int x_, int y_) {
  _x2 += x_ - _x1;
  _x1 = x_;
  _y2 += y_ - _y1;
  _y1 = y_;
}


void bt::Rect::setWidth(unsigned int w)
{ _x2 = w + _x1 - 1; }


void bt::Rect::setHeight(unsigned int h)
{ _y2 = h + _y1 - 1; }


void bt::Rect::setSize(unsigned int w, unsigned int h) {
  _x2 = w + _x1 - 1;
  _y2 = h + _y1 - 1;
}


void bt::Rect::setRect(int x_, int y_, unsigned int w, unsigned int h)
{ *this = bt::Rect(x_, y_, w, h); }


void bt::Rect::setCoords(int l, int t, int r, int b) {
  _x1 = l;
  _y1 = t;
  _x2 = r;
  _y2 = b;
}


bt::Rect bt::Rect::operator|(const bt::Rect &a) const {
  bt::Rect b;

  b._x1 = std::min(_x1, a._x1);
  b._y1 = std::min(_y1, a._y1);
  b._x2 = std::max(_x2, a._x2);
  b._y2 = std::max(_y2, a._y2);

  return b;
}


bt::Rect bt::Rect::operator&(const bt::Rect &a) const {
  bt::Rect b;

  b._x1 = std::max(_x1, a._x1);
  b._y1 = std::max(_y1, a._y1);
  b._x2 = std::min(_x2, a._x2);
  b._y2 = std::min(_y2, a._y2);

  return b;
}


bool bt::Rect::intersects(const bt::Rect &a) const {
  return std::max(_x1, a._x1) <= std::min(_x2, a._x2) &&
         std::max(_y1, a._y1) <= std::min(_y2, a._y2);
}


bool bt::Rect::contains(int x_, int y_) const {
  return x_ >= _x1 && x_ <= _x2 &&
         y_ >= _y1 && y_ <= _y2;
}


bt::Rect bt::Rect::inside(const Rect &a) const {
  Rect r = *this;
  if (r._x2 > a._x2)
    r.setX(r._x1 - (r._x2 - a._x2));
  if (r._x1 < a._x1)
    r.setX(a._x1);
  if (r._y2 > a._y2)
    r.setY(r._y1 - (r._y2 - a._y2));
  if (r._y1 < a._y1)
    r.setY(a._y1);
  return r;
}
