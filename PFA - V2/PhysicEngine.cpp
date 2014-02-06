#include "PhysicEngine.h"

PhysicEngine::PhysicEngine(Map *&map, Camera *cam) : _map(map), _cam(cam)
{
	_isLaunch = false;
	_isRunning = true;
}

void PhysicEngine::init()
{
	
	_isPathNotFound = false;
	this->_isFirst = true;

	_isLaunch = true;
	_pathFinding.initPathfinding(_map, _cam);
}

void PhysicEngine::setCamPos(sf::Vector2f &cam)
{
	//_cam = cam;
}
bool PhysicEngine::findMeAPath(sf::Vector2i&begin, sf::Vector2i &end, IEntity &ent)
{
	return _pathFinding.findMeAPath(begin, end, ent);
}

bool PhysicEngine::getIsLaunch() const
{
	return _isLaunch;
}

sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float f)
{
	return a + f * (b - a);
}

void PhysicEngine::updatePos(std::vector<Player *> players, std::vector<IEntity *> entities)
{
	if (!Singleton::getInstance().isRightClicking)
	{
		_isFirst = true;
	}
	if ((Singleton::getInstance().isRightClicking && this->_isFirst) || _isPathNotFound)
	{
		this->_isFirst = false;

		for (std::vector<Player *>::iterator it = players.begin(); it != players.end(); ++it)
		{
			if ((*it)->getSelected())
			{

				sf::Vector2i tmp_begin = sf::Mouse::getPosition(*Singleton::getInstance()._window);
				sf::Vector2i tmp_end;

				if (_isPathNotFound && (*it)->getPathToGo() <= 1)
				{
					sf::Vector2f tmp_lerp_begin;
					sf::Vector2f tmp_lerp_end;
					tmp_begin.x = (tmp_begin.x + _map->getCamPos().x * Chunk::SIZE_OF_CELL) / Chunk::SIZE_OF_CELL; // ISOK
					tmp_begin.y = (tmp_begin.y + _map->getCamPos().y * Chunk::SIZE_OF_CELL) / Chunk::SIZE_OF_CELL;
					tmp_lerp_begin.x = tmp_begin.x;
					tmp_lerp_begin.y = tmp_begin.y;

					tmp_end.x = (*it)->getPosition().x; // player en selec
					tmp_end.y = (*it)->getPosition().y;
					tmp_lerp_end.x = tmp_end.x;
					tmp_lerp_end.y = tmp_end.y;
					tmp_lerp_begin = lerp(tmp_lerp_begin, tmp_lerp_end, (*it)->getPathToGo());
					tmp_begin.x = tmp_lerp_begin.x;
					tmp_begin.y = tmp_lerp_begin.y;
					(*it)->addToPathToGo(0.01);
					_isPathNotFound = false;
				}
				else
				{
					tmp_begin.x = (tmp_begin.x + _map->getCamPos().x * Chunk::SIZE_OF_CELL) / Chunk::SIZE_OF_CELL; // ISOK
					tmp_begin.y = (tmp_begin.y + _map->getCamPos().y * Chunk::SIZE_OF_CELL) / Chunk::SIZE_OF_CELL;
				}
				if (_map->getCellMap()[tmp_begin.y][tmp_begin.x]._cellType == Cell::OCEAN
					|| _map->getEntitiesMap()[tmp_begin.y][tmp_begin.x]._component != NULL)
				{
					_isPathNotFound = true;
				}
				else
				{
					(*it)->setPathToGo(0.f);

					if ((*it)->getSelected())
					{

						tmp_end.x = (*it)->getPosition().x; // player en selec
						tmp_end.y = (*it)->getPosition().y;
						findMeAPath(tmp_end, tmp_begin, **it);
					}


				}
			}
		}
	}

}

void PhysicEngine::update()
{
	
	_pathFinding.updatePath();
}

void PhysicEngine::addVertexPoint(sf::Vector2i &pos)
{
	_pathFinding.addVertexPoint(pos);
}