#ifndef THREAD_HH_
# define THREAD_HH_

# include "IThread.hh"
# if defined(_WIN32)
#  include "ThreadWin.hh"
# else
#  include "ThreadUnix.hh"
#  include <unistd.h>
# endif

class Thread
{
public:
  template <typename C>
  Thread(void(C::*function)(), C* object)
    : _impl(NULL), _entryPoint(new ThreadMemberFunc<C>(function, object))
  {
  }

  ~Thread();
  void				launch();
  void				wait();
  void				terminate();

  void				run();

private:
  IThread			*_impl;
  ThreadFunc			*_entryPoint;
};

#endif
