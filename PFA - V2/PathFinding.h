#pragma once
#include						<boost/graph/adjacency_list.hpp>
#include						<boost/graph/graph_traits.hpp>
#include						<boost/graph/astar_search.hpp>
#include						<boost/graph/adjacency_iterator.hpp>
#include						<boost/config.hpp>
#include						<boost/graph/random.hpp>
#include						<boost/random.hpp>
#include						<math.h> 
#include						"Map.h"


using namespace boost;

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

class astar_goal_visitor : public boost::default_astar_visitor{
private:
	typedef boost::adjacency_list<  
		boost::listS,              
		boost::vecS,                
		boost::undirectedS,         
		WayPoint,                   
		WayPointConnection          
	> WayPointGraph;
	typedef WayPointGraph::vertex_descriptor WayPointID;
	typedef WayPointGraph::edge_descriptor   WayPointConnectionID;
	WayPointGraph graphe;
	WayPointID m_goal;

public:
	astar_goal_visitor(WayPointID goal) : m_goal(goal) {}

	void examine_vertex(WayPointID u, const WayPointGraph &amp){ 
		if(u == m_goal)
			throw found_goal(); 
	}
private:

};

class PathFinding
{
public:
	void initPathfinding(Map *&map, Camera *cam);
	void updatePath();
	void addVertexPoint(sf::Vector2i &);
	bool findMeAPath(sf::Vector2i&, sf::Vector2i &, IEntity &);
	
protected:
private:
	bool incNewCell(Map &, std::pair<int, int> add, std::pair<float, float> *tmp, std::pair<int, int> *tmp_add);
	typedef boost::adjacency_list<  
		boost::listS,              
		boost::vecS,                
		boost::undirectedS,         
		WayPoint,                   
		WayPointConnection          
	> WayPointGraph;
	std::list<sf::Vertex *> list_line;
	typedef WayPointGraph::vertex_descriptor WayPointID;
	typedef WayPointGraph::edge_descriptor   WayPointConnectionID;
	WayPointGraph graphe;
	std::pair<WayPointID, bool> _vertex_found;
	void find_vertex(const WayPoint& wp, const WayPointGraph& graph);
	bool equal(const std::pair<float, float>& p1, const std::pair<float, float>& p2);
	Camera *_cam;
};

