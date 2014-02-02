#include "PhysicEngine.h"

PhysicEngine::PhysicEngine(Map *&map, Camera *cam) : _map(map), _cam(cam)
{
	_isLaunch = false;
	_isRunning = true;
}

void PhysicEngine::init()
{
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

void PhysicEngine::update()
{
	_pathFinding.updatePath();
}

void PhysicEngine::addVertexPoint(sf::Vector2i &pos)
{
	_pathFinding.addVertexPoint(pos);
}