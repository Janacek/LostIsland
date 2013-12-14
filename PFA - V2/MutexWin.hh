#ifndef MUTEXWIN_HH_
# define MUTEXWIN_HH_

# include "IMutex.hh"

class MutexWin : public IMutex
{
public:
  MutexWin();
  virtual ~MutexWin();

  void lock();
  void unlock();
  int trylock();

  void wait();
  void signal();
  void broadcast();

private:
  CRITICAL_SECTION _mutex;
  CONDITION_VARIABLE _cond;
};

#endif
