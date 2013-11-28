#pragma once
#include						<boost/graph/adjacency_list.hpp>
#include						<boost/graph/graph_traits.hpp>
#include						<boost/graph/astar_search.hpp>
#include						<boost/graph/adjacency_iterator.hpp>
#include						<boost/config.hpp>
#include						<boost/graph/random.hpp>
#include						<boost/random.hpp>
#include "Map.h"


class PathFinding
{
public:
   void initPathfinding(Map* map);
   void updatePath(void);

protected:
private:

};

