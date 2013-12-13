#include "Thread.hh"

Thread::~Thread()
{
  this->wait();
  delete _entryPoint;
}

void Thread::launch()
{
  this->wait();

#if defined(_WIN32)
  _impl = new ThreadWin(this);
#else
  _impl = new ThreadUnix(this);
#endif
}

void Thread::wait()
{
  if (_impl)
    {
      _impl->wait();
      delete _impl;
      _impl = NULL;
    }
}

void Thread::terminate()
{
  if (_impl)
    {
      _impl->terminate();
      delete _impl;
      _impl = NULL;
    }
}

void Thread::run()
{
  _entryPoint->run();
}
