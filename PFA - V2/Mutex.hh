#ifndef MUTEX_HH_
# define MUTEX_HH_

# include "IMutex.hh"
# if defined(_WIN32)
#  include "MutexWin.hh"
# else
#  include "MutexUnix.hh"
# endif

class Mutex : public IMutex
{
public:
  Mutex();
  ~Mutex();

  void lock();
  void unlock();
  int trylock();

  void wait();
  void signal();
  void broadcast();

private:
  IMutex *_mutexImpl;
};

#endif
