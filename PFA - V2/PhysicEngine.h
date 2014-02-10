#pragma once

#include <list>
#include "Player.h"
#include "IEngine.h"
#include "PathFinding.h"

class PhysicEngine : public IEngine
{
public:
	PhysicEngine(Map *&, Camera *cam);
	~PhysicEngine();
	void init();
	void setCamPos(sf::Vector2f &cam);
	void update();
	void updatePos(std::vector<Player *> players, std::vector<IEntity *> entities);
	bool getIsLaunch() const;
	void addVertexPoint(sf::Vector2i &) ;
	bool findMeAPath(sf::Vector2i&, sf::Vector2i & , IEntity &);
	bool tryFindAPathHuman(sf::Vector2i&, sf::Vector2i &, IEntity &);
	bool tryFindAPathEntity(sf::Vector2i&, sf::Vector2i &, IEntity &);

protected:
private:
	float				diffDist(sf::Vector2f const &, sf::Vector2f const &);
	sf::Vector2f        lerp(sf::Vector2f a, sf::Vector2f b, float f);
	Camera		*_cam;
	bool _isLaunch;
	bool _isRunning;
	PathFinding _pathFinding;
	Map *&_map;
	bool					_isFirst;
	bool					_isPathNotFound;
	
};