// TODO - Documentation

#include "Timer.hh"

#include <sys/time.h>


bt::timeval::timeval(const ::timeval &t)
  : tv_sec(t.tv_sec), tv_usec(t.tv_usec)
{ }


bool bt::timeval::operator<(const timeval &tv)
{ return tv_sec < tv.tv_sec || (tv_sec == tv.tv_sec && tv_usec < tv.tv_usec); }


bt::timeval bt::timeval::operator+(const timeval &tv)
{ return timeval(tv_sec + tv.tv_sec, tv_usec + tv.tv_usec); }


bt::timeval &bt::timeval::operator+=(const timeval &tv)
{ return *this = normalizeTimeval(operator+(tv)); }


bt::timeval bt::timeval::operator-(const timeval &tv)
{ return timeval(tv_sec - tv.tv_sec, tv_usec - tv.tv_usec); }


bt::timeval &bt::timeval::operator-=(const timeval &tv)
{ return *this = normalizeTimeval(operator-(tv)); }


bt::timeval &bt::timeval::operator=(const ::timeval &t)
{ return (*this = timeval(t)); }


bt::timeval::operator ::timeval() const {
  ::timeval ret = { tv_sec, tv_usec };
  return ret;
}


bt::timeval bt::normalizeTimeval(const timeval &tm) {
  timeval ret = tm;

  while (ret.tv_usec < 0) {
    if (ret.tv_sec > 0) {
      --ret.tv_sec;
      ret.tv_usec += 1000000;
    } else {
      ret.tv_usec = 0;
    }
  }

  if (ret.tv_usec >= 1000000) {
    ret.tv_sec += ret.tv_usec / 1000000;
    ret.tv_usec %= 1000000;
  }

  if (ret.tv_sec < 0) ret.tv_sec = 0;

  return ret;
}


bt::Timer::Timer(TimerQueueManager *m, TimeoutHandler *h) {
  manager = m;
  handler = h;

  recur = timing = false;
}


bt::Timer::~Timer(void) {
  if (timing)
    stop();
}


void printTime(const char *message, const bt::timeval &tv);

void bt::Timer::adjustStartTime(const timeval &offset)
{ _start += offset; }


void bt::Timer::setTimeout(long t) {
  _timeout.tv_sec = t / 1000;
  _timeout.tv_usec = t % 1000;
  _timeout.tv_usec *= 1000;
}


void bt::Timer::setTimeout(const timeval &t)
{ _timeout = t; }


void bt::Timer::start(void) {
  ::timeval s;
  gettimeofday(&s, 0);
  _start = s;

  if (!timing) {
    timing = true;
    manager->addTimer(this);
  }
}


void bt::Timer::stop(void) {
  timing = false;
  manager->removeTimer(this);
}


void bt::Timer::halt(void)
{ timing = false; }


void bt::Timer::fireTimeout(void)
{
  if (handler)
    handler->timeout(this);
}


bt::timeval bt::Timer::timeRemaining(const timeval &tm) const {
  timeval ret = endpoint();

  ret.tv_sec  -= tm.tv_sec;
  ret.tv_usec -= tm.tv_usec;

  return bt::normalizeTimeval(ret);
}


bt::timeval bt::Timer::endpoint(void) const {
  timeval ret;

  ret.tv_sec = _start.tv_sec + _timeout.tv_sec;
  ret.tv_usec = _start.tv_usec + _timeout.tv_usec;

  return bt::normalizeTimeval(ret);
}


bool bt::Timer::shouldFire(const timeval &tm) const {
  timeval end = endpoint();

  return !((tm.tv_sec < end.tv_sec) ||
           (tm.tv_sec == end.tv_sec && tm.tv_usec < end.tv_usec));
}
