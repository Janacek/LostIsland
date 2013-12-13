#include "Mutex.hh"

Mutex::Mutex()
{
#if defined(_WIN32)
  _mutexImpl = new MutexWin();
#else
  _mutexImpl = new MutexUnix();
#endif
}

Mutex::~Mutex()
{
  _mutexImpl->unlock();
  delete _mutexImpl;
}

void Mutex::lock()
{
  _mutexImpl->lock();
}

void Mutex::unlock()
{
  _mutexImpl->unlock();
}

int Mutex::trylock()
{
  return _mutexImpl->trylock();
}

void Mutex::wait()
{
  _mutexImpl->wait();
}

void Mutex::signal()
{
  _mutexImpl->signal();
}

void Mutex::broadcast()
{
  _mutexImpl->broadcast();
}
