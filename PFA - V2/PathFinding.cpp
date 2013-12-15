
#include "PhysicEngine.h"
#include "PathFinding.h"
#include "Polygon.h"
#include "Map.h"

void PathFinding::initPathfinding(Map* map)
{
	for (Polygon_ *u : map->_polygons)
	{
		if (u->getPolygonType() == u->GROUND)
		{
			WayPointID wpID = boost::add_vertex(graphe); 
			graphe[wpID].pos = u->getCenter();
			for (std::deque<Edge_ *>::iterator it = u->getEdges().begin() ; it != u->getEdges().end() ; ++it)
			{
				bool isPass = false;
				boost::graph_traits<WayPointGraph>::vertex_iterator it_b, it_end;

				for (boost::tie(it_b, it_end) = boost::vertices(graphe) ; it_b != it_end ; ++it_b)
				{
					if (boost::get(boost::vertex_bundle, graphe)[*it_b].pos == (*it)->_polygonsOwn.second->getCenter())
					{
						isPass = true;

						break;
					}
				}
				std::pair<Polygon_ *, Polygon_ *> t = (*it)->_polygonsOwn;
				if (isPass == false)
				{
					WayPointID wpID2 = boost::add_vertex(graphe);

					graphe[wpID2].pos = t.second->getCenter();
				}
				else
				{
					WayPointID wpID2 = (*it_b);

					if (t.first->getPolygonType() == t.first->GROUND)
					{
						float dx = abs(graphe[wpID].pos.first - graphe[wpID2].pos.first);
						float dy = abs(graphe[wpID].pos.second - graphe[wpID2].pos.second);

						boost::add_edge(wpID, wpID2, WayPointConnection(sqrt(dx * dx + dy * dy)), graphe);				
					}
				}
			}
		}
	}


	typedef boost::graph_traits <WayPointGraph>::adjacency_iterator adjacency_iterator;

}

void PathFinding::updatePath(void)
{
	boost::mt19937 gen(time(0));

	std::vector<WayPointID> p(boost::num_vertices(graphe)); 
	std::vector<float>      d(boost::num_vertices(graphe)); 
	WayPointID start = boost::random_vertex(graphe, gen);
	WayPointID goal = boost::random_vertex(graphe, gen);
	shortest_path.clear();
	try {
		boost::astar_search
			(
			graphe, 
			start,  
			boost::astar_heuristic<WayPointGraph, float>(), 
			boost::predecessor_map(&p[0]).distance_map(&d[0]).visitor(astar_goal_visitor(goal)).weight_map(boost::get(&WayPointConnection::dist, graphe))
			);

	} catch(found_goal fg) { 

		for(WayPointID v = goal;; v = p[v]) {
			shortest_path.push_front(v);
			if(p[v] == v)
				break;
		}
	}
}