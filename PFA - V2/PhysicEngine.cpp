#include "PhysicEngine.h"

PhysicEngine::PhysicEngine(Map *&map) : _map(map)
{
	_isLaunch = false;
	_isRunning = true;
}

void PhysicEngine::init()
{
	_isLaunch = true;
	_pathFinding.initPathfinding(_map);
}

void PhysicEngine::setCamPos(sf::Vector2f &cam)
{
	_cam = cam;
}


bool PhysicEngine::getIsLaunch() const
{
	return _isLaunch;
}

void PhysicEngine::update()
{
	//_pathFinding.updatePath(_cam);
}