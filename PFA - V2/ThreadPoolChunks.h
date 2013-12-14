#pragma	once

#include					"ChunkFactory.h"
#include					"Thread.hh"

class						ThreadPoolChunks
{
public:
	ThreadPoolChunks(ChunkFactory &);
	~ThreadPoolChunks();
	void					init(int);

private:
	int						_nbThreads;
	int						_nbAvailableThreads;
	ChunkFactory			&_factory;
	std::list<Thread *>		_threads;
};