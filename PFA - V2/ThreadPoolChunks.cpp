#include						"ThreadPoolChunks.h"
#include <iostream>

ThreadPoolChunks::ThreadPoolChunks(ChunkFactory &factory)
	: _factory(factory)
{
	_nbThreads = 0;
	_nbAvailableThreads = 0;
	_threads.clear();
	std::cout << "ThreadPool constructed" << std::endl;
}

ThreadPoolChunks::~ThreadPoolChunks()
{
}

void							ThreadPoolChunks::init(int nbThreads)
{
	_nbThreads = nbThreads;
	std::cout << "start init" << std::endl;
	for (int i = 0 ; i < _nbThreads ; ++i)
	{
		std::cout << "Thread creation" << std::endl;
		Thread *thr = new Thread(&ChunkFactory::computeTask, &_factory);
		std::cout << "Thread created" << std::endl;
		_threads.push_back(thr);
		++_nbAvailableThreads;
		std::cout << "Running thread" << std::endl;
		thr->launch();
		std::cout << "thread" << i << " init" << std::endl;
	}
}