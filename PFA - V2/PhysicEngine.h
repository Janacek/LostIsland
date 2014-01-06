#pragma once

#include <stack>
#include "IEngine.h"
#include "PathFinding.h"

class PhysicEngine : public IEngine
{
public:
	PhysicEngine(Map *&);
	void init();
	void setCamPos(sf::Vector2f &cam);
	void update(std::vector<IEntity *> &players, std::list<IEntity *> &entities);
	bool getIsLaunch() const;
	
protected:
private:
	sf::Vector2f _cam;
	bool _isLaunch;
	bool _isRunning;
	PathFinding _pathFinding;
	Map *&_map;
};