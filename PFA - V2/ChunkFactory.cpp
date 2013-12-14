#include					"ChunkFactory.h"

#include <iostream>
ChunkFactory::ChunkFactory()
{
	std::cout << "zepfozfokzpefpzk" << std::endl;
	_tasks.clear();
	_factoryMutex = new Mutex();
	std::cout << "New chunkFactory" << std::endl;
}

void						ChunkFactory::addTask(Chunk *chunk)
{
	_tasks.push_back(chunk);
}

Chunk						*ChunkFactory::getTask()
{
	Chunk					*task = NULL;

	if (!_tasks.empty())
	{
		task = _tasks.front();
		_tasks.pop_front();
	}
	return (task);
}

void						ChunkFactory::computeTask()
{
	Chunk					*task = NULL;

	while (true)
	{
		if (!_tasks.empty())
		{
			std::cout << "Computing task" << std::endl;
			_factoryMutex->lock();
			task = _tasks.front();
			_factoryMutex->unlock();
			_tasks.pop_front();

			task->getTexture();
		}
		sf::sleep(sf::milliseconds(300));
	}
}

ChunkFactory::~ChunkFactory()
{
	delete _factoryMutex;
}