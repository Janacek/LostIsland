#pragma	once

#include					<list>
#include					"Chunk.h"
#include					"Mutex.hh"


class						ChunkFactory
{
public:
	ChunkFactory();
	~ChunkFactory();

	void					addTask(Chunk *);
	void					computeTask();
	Chunk					*getTask();
private:
	std::list<Chunk *>		_tasks;
	Mutex					*_factoryMutex;
};