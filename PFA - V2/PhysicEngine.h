#pragma once

#include <stack>
#include "Player.h"
#include "IEngine.h"
#include "PathFinding.h"

class PhysicEngine : public IEngine
{
public:
	PhysicEngine(Map *&, Camera *cam);
	void init();
	void setCamPos(sf::Vector2f &cam);
	void update();
	void updatePos(std::vector<Player *> players, std::vector<IEntity *> entities);
	bool getIsLaunch() const;
	void addVertexPoint(sf::Vector2i &) ;
	bool findMeAPath(sf::Vector2i&, sf::Vector2i & , IEntity &);

protected:
private:
	Camera		*_cam;
	bool _isLaunch;
	bool _isRunning;
	PathFinding _pathFinding;
	Map *&_map;
	bool					_isFirst;
	bool					_isPathNotFound;
	float					_pathToGo;
};