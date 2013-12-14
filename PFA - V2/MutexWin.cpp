#ifdef _WIN32

# include "MutexWin.hh"

MutexWin::MutexWin()
{
  InitializeCriticalSection(&_mutex);
  InitializeConditionVariable(&_cond);
}

MutexWin::~MutexWin()
{
  DeleteCriticalSection(&_mutex);
}

void MutexWin::lock()
{
  EnterCriticalSection(&_mutex);
}

void MutexWin::unlock()
{
  LeaveCriticalSection(&_mutex);
}

int MutexWin::trylock()
{
  return (TryEnterCriticalSection(&_mutex));
}

void MutexWin::wait()
{
  SleepConditionVariableCS(&_cond, &_mutex, INFINITE);
}

void MutexWin::signal()
{
  WakeConditionVariable(&_cond);
}

void MutexWin::broadcast()
{
  WakeAllConditionVariable(&_cond);
}

#endif
