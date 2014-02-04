#include "PhysicEngine.h"

PhysicEngine::PhysicEngine(Map *&map, Camera *cam) : _map(map), _cam(cam)
{
	_isLaunch = false;
	_isRunning = true;
}

void PhysicEngine::init()
{
	_pathToGo = 0.f;
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
		sf::Vector2i tmp_begin = sf::Mouse::getPosition(*Singleton::getInstance()._window);
		sf::Vector2i tmp_end;
		if (_isPathNotFound && _pathToGo <= 1)
		{
			sf::Vector2f tmp_lerp_begin;
			sf::Vector2f tmp_lerp_end;
			tmp_begin.x = (tmp_begin.x + _map->getCamPos().x * Chunk::SIZE_OF_CELL) / Chunk::SIZE_OF_CELL; // ISOK
			tmp_begin.y = (tmp_begin.y + _map->getCamPos().y * Chunk::SIZE_OF_CELL) / Chunk::SIZE_OF_CELL;
			tmp_lerp_begin.x = tmp_begin.x;
			tmp_lerp_begin.y = tmp_begin.y;
			tmp_end.x = players[0]->getPosition().x; // player en selec
			tmp_end.y = players[0]->getPosition().y;
			tmp_lerp_end.x = tmp_end.x;
			tmp_lerp_end.y = tmp_end.y;
			tmp_lerp_begin = lerp(tmp_lerp_begin, tmp_lerp_end, _pathToGo);
			tmp_begin.x = tmp_lerp_begin.x;
			tmp_begin.y = tmp_lerp_begin.y;
			_pathToGo += 0.01;
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
			_pathToGo = 0;
			tmp_end.x = players[0]->getPosition().x; // player en selec
			tmp_end.y = players[0]->getPosition().y;
			findMeAPath(tmp_end, tmp_begin, *players[0]);
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