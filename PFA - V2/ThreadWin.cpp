#ifdef _WIN32

# include <cassert>
# include <process.h>
# include "ThreadWin.hh"
# include "Thread.hh"

//#warning "AJOUTER LES EXCEPTIONS PLZ KTHXBAI"

ThreadWin::ThreadWin(Thread *owner)
{
  _thread = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, &ThreadWin::entryPoint, owner, 0, &_threadId));

  if (!_thread)
    {
      //    err() << "Failed to create thread" << std::endl;
    }
}

ThreadWin::~ThreadWin()
{
  if (_thread)
    CloseHandle(_thread);
}

void ThreadWin::wait()
{
  if (_thread)
    {
      assert(_threadId != GetCurrentThreadId());
      WaitForSingleObject(_thread, INFINITE);
    }
}

void ThreadWin::terminate()
{
  if (_thread)
    TerminateThread(_thread, 0);
}

unsigned int __stdcall ThreadWin::entryPoint(void* userData)
{
  Thread *owner = static_cast<Thread*>(userData);

  owner->run();

  _endthreadex(0);

  return 0;
}

#endif
