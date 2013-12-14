#ifndef ITHREAD_HH_
# define ITHREAD_HH_

# include "CrossType.hh"

struct ThreadFunc
{
  virtual ~ThreadFunc() {}
  virtual void run() = 0;
};

template <typename C>
struct ThreadMemberFunc : ThreadFunc
{
  ThreadMemberFunc(void(C::*function)(), C* object)
    : _function(function), _object(object) {}
  virtual void run()
  {
    (_object->*_function)();
  }

  void(C::*_function)();
  C *_object;
};

class IThread
{
public:
  virtual ~IThread() {}
  virtual void wait() = 0;
  virtual void terminate() = 0;
};

#endif
