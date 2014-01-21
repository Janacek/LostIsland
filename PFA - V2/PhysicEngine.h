#pragma once

#include <stack>
#include "IEngine.h"
#include "PathFinding.h"

class PhysicEngine : public IEngine
{
public:
	PhysicEngine(Map *&, Camera *cam);
	void init();
	void setCamPos(sf::Vector2f &cam);
	void update();
	bool getIsLaunch() const;
	void addVertexPoint(sf::Vector2i &) ;
	void findMeAPath(sf::Vector2i&, sf::Vector2i & , IEntity &);

protected:
private:
	Camera		*_cam;
	bool _isLaunch;
	bool _isRunning;
	PathFinding _pathFinding;
	Map *&_map;
};