#ifndef IMUTEX_HH_
# define IMUTEX_HH_

# include "CrossType.hh"

class IMutex
{
public:
  virtual ~IMutex() {}

  virtual void lock() = 0;
  virtual void unlock() = 0;
  virtual int trylock() = 0;

  virtual void wait() = 0;
  virtual void signal() = 0;
  virtual void broadcast() = 0;
};

#endif
