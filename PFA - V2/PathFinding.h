#pragma once
#include						<boost/graph/adjacency_list.hpp>
#include						<boost/graph/graph_traits.hpp>
#include						<boost/graph/astar_search.hpp>
#include						<boost/graph/adjacency_iterator.hpp>
#include						<boost/config.hpp>
#include						<boost/graph/random.hpp>
#include						<boost/random.hpp>
#include						"Map.h"

struct found_goal {}; 

struct WayPoint{
	std::pair<float, float> pos;
	std::deque<std::pair<float, float>> adjacents;
	// et éventuellement d'autres informations (crouch, hide, camp, ...)
};

// Une liaison entre deux waypoints
struct WayPointConnection{
	float dist;
	WayPointConnection() : dist(0) {}
	WayPointConnection(float _dist) : dist(_dist) {}

	// idem
};

class PathFinding
{
public:
   void initPathfinding(Map* map);
   void updatePath(void);

protected:
private:

};

