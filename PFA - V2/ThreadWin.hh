#ifndef THREADWIN_HH_
# define THREADWIN_HH_

# include "IThread.hh"

typedef HANDLE THREAD;

class Thread;

class ThreadWin : public IThread
{
public:
  ThreadWin(Thread *owner);
  virtual ~ThreadWin();

  void			wait();
  void			terminate();

private:
  static unsigned int __stdcall entryPoint(void *);

  HANDLE			_thread;
  unsigned int	_threadId;
};

#endif
