
#include "PhysicEngine.h"
#include "PathFinding.h"
#include "Map.h"

void PathFinding::initPathfinding(Map* &map)
{
	bool isPass = false;
	int i;

	int j = 0;
	i = 0;
	int t = 0;

	std::cout << "LOL " << Chunk::NB_CELLS << std::endl;
	int u = 0;
	int a = 0;
	int b = 0;
	for (j = 0; j < map->getSize().x * Chunk::NB_CELLS; ++j)
	{

		for (i = 0; i < map->getSize().y * Chunk::NB_CELLS; ++i)
		{


			// on doit passer par tous les points adjacent aux points courants
			// le truc cest que Il ne peut pas y avoir 2 meme points dans la liste

			if (map->getCellMap()[i][j]._cellType != Cell::OCEAN)
			{
				WayPointID wpID = boost::add_vertex(graphe);
				graphe[wpID].pos.first = j;
				graphe[wpID].pos.second = i;
				for (int u = 0; u < 8; ++u)
				{
					//std::cout << "caca" << std::endl;
					bool isPass = false;
					bool isOk = false;
					boost::graph_traits<WayPointGraph>::vertex_iterator it_b, it_end;

					std::pair<float, float> tmp((j), (i));
					std::pair<int, int> tmp_add((j), (i));

					if (u == 0)
					{
						tmp.first += 1;
						tmp_add.first += 1;
					}
					else if (u == 1)
					{
						tmp.second += 1;
						tmp_add.second += 1;
					}
					else if (u == 2)
					{
						tmp.first -= 1;
						tmp_add.first -= 1;
						if (map->getCellMap()[tmp_add.second][tmp_add.first - 1]._cellType != Cell::OCEAN)
						{
							isOk = false;
						}
					}
					else if (u == 3)
					{
						tmp.second -= 1;
						tmp_add.second -= 1;
						if (map->getCellMap()[tmp_add.second - 1][tmp_add.first]._cellType != Cell::OCEAN)
						{
							isOk = false;
						}
					}
					else if (u == 4)
					{
						tmp_add.first += 1;
						tmp_add.second += 1;
						if (map->getCellMap()[tmp_add.second - 1][tmp_add.first]._cellType != Cell::OCEAN &&
							map->getCellMap()[tmp_add.second][tmp_add.first - 1]._cellType != Cell::OCEAN)
						{
							tmp.first += 1;
							tmp.second += 1;

						}
						else
							isOk = true;
					}
					else if (u == 5)
					{
						tmp_add.first -= 1;

						tmp_add.second += 1;

						if (map->getCellMap()[tmp_add.second][tmp_add.first + 1]._cellType != Cell::OCEAN &&
							map->getCellMap()[tmp_add.second - 1][tmp_add.first]._cellType != Cell::OCEAN)
						{
							tmp.first -= 1;
							tmp.second += 1;

						}
						else
							isOk = true;
					}
					else if (u == 6)
					{
						tmp_add.first -= 1;

						tmp_add.second -= 1;

						if (map->getCellMap()[tmp_add.second + 1][tmp_add.first]._cellType != Cell::OCEAN &&
							map->getCellMap()[tmp_add.second][tmp_add.first + 1]._cellType != Cell::OCEAN)
						{
							tmp.first -= 1;
							tmp.second -= 1;

						}
						else
							isOk = true;
					}
					else if (u == 7)
					{
						tmp_add.first += 1;

						tmp_add.second -= 1;

						if (map->getCellMap()[tmp_add.second][tmp_add.first - 1]._cellType != Cell::OCEAN &&
							map->getCellMap()[tmp_add.second + 1][tmp_add.first]._cellType != Cell::OCEAN)
						{
							tmp.first += 1;
							tmp.second -= 1;

						}
						else
							isOk = true;
					}
					//std::cout << " x " << boost::get(boost::vertex_bundle, graphe)[*it].pos.first  << " y " << boost::get(boost::vertex_bundle, graphe)[*it].pos.second << std::endl;		
					if (tmp.first >= 0 && tmp.second >= 0 && tmp.first <= map->getSize().x  * Chunk::NB_CELLS && tmp.second <= map->getSize().y  * Chunk::NB_CELLS && isOk == false)
					{
						for (boost::tie(it_b, it_end) = boost::vertices(graphe); it_b != it_end; ++it_b)
						{
							//std::cout << " x " << boost::get(boost::vertex_bundle, graphe)[*it].pos.first  << " y " << boost::get(boost::vertex_bundle, graphe)[*it].pos.second << std::endl;		
							if (boost::get(boost::vertex_bundle, graphe)[*it_b].pos == tmp)
							{
								isPass = true;
								break;
							}
						}

						if (isPass == false)
						{
							WayPointID wpID2 = boost::add_vertex(graphe);

							graphe[wpID2].pos = tmp;
							if (map->getCellMap()[tmp_add.second][tmp_add.first]._cellType != Cell::OCEAN)
							{
								float dx = abs(graphe[wpID].pos.first - graphe[wpID2].pos.first) * Chunk::SIZE_OF_CELL;
								float dy = abs(graphe[wpID].pos.second - graphe[wpID2].pos.second) * Chunk::SIZE_OF_CELL;
								//std::cout << "Point 1 x " << graphe[wpID].pos.first << " y " << graphe[wpID].pos.second
								//<< "Point 2 x " << graphe[wpID2].pos.first << " y " << graphe[wpID2].pos.second << std::endl;

								a++;
								boost::add_edge(wpID, wpID2, WayPointConnection(sqrt(dx * dx + dy * dy)), graphe);
							}
						}
						else
						{
							
							WayPointID wpID2 = (*it_b);
							if (map->getCellMap()[tmp_add.second][tmp_add.first]._cellType != Cell::OCEAN)
							{
								float dx = abs(graphe[wpID].pos.second - graphe[wpID2].pos.second) * Chunk::SIZE_OF_CELL;
								float dy = abs(graphe[wpID].pos.first - graphe[wpID2].pos.first) * Chunk::SIZE_OF_CELL;
								//std::cout << "Point 1 x " << graphe[wpID].pos.first << " y " << graphe[wpID].pos.second
								//<< "Point 2 x " << graphe[wpID2].pos.first << " y " << graphe[wpID2].pos.second << std::endl;
								boost::add_edge(wpID, wpID2, WayPointConnection(sqrt(dx * dx + dy * dy)), graphe);
								b++;
							}
						}


					}
				}


			}


		}

	}


	int n = 0;
	std::cout << "TOTAL " << u << "map x " << map->getSize().x << " y " << map->getSize().y << " size cell" << "Nb type A " << a << " type B " << b << Chunk::NB_CELLS << std::endl;



}



void PathFinding::updatePath(sf::Vector2f &cam)
{


	typedef boost::graph_traits <WayPointGraph>::edge_iterator edge_iterator_t;

	std::pair<edge_iterator_t, edge_iterator_t> ep;

	edge_iterator_t ei, ei_end;


	//for (boost::tie(ei, ei_end) = boost::edges(graphe); ei != ei_end; ++ei)
	//{

	//	sf::vector2f pt1;
	//	pt1.x = (get(boost::vertex_bundle, graphe)[boost::source(*ei, graphe)].pos.first - cam.x) * chunk::size_of_cell;
	//	pt1.y = (get(boost::vertex_bundle, graphe)[boost::source(*ei, graphe)].pos.second - cam.y) * chunk::size_of_cell;

	//	sf::vector2f pt2;
	//	pt2.x = (get(boost::vertex_bundle, graphe)[boost::target(*ei, graphe)].pos.first - cam.x) * chunk::size_of_cell;
	//	pt2.y = (get(boost::vertex_bundle, graphe)[boost::target(*ei, graphe)].pos.second - cam.y) * chunk::size_of_cell;

	//	sf::vertex line[2] =
	//	{
	//		sf::vertex(pt1),
	//		sf::vertex(pt2)
	//	};
	//	singleton::getinstance()._window->draw(line, 2, sf::lines);

	//	std::cout << "point 1 x " <<  pt1.x << " y " << pt1.y << " pt 2 x "<< pt2.x << " y " << pt2.y << std::endl;  
	//}


	//sf::Texture texture = rt.getTexture();
	//map 
	//sf::Sprite sprite(texture);
	//std::cout << " camx " << cam.x << " camy " << cam.y << std::endl; 
	//sprite.setPosition(0, 0);

	//Singleton::getInstance()._window->draw(sprite);
	if (this->shortest_path.empty() == false)
	{
		for (std::list<WayPointID>::iterator it = this->shortest_path.begin(); it != shortest_path.end(); ++it)
		{
			sf::CircleShape circle;

			circle.setPosition((sf::Vector2f((boost::get(boost::vertex_bundle, graphe)[*it].pos.first - cam.x) * Chunk::SIZE_OF_CELL - 5, (boost::get(boost::vertex_bundle, graphe)[*it].pos.second - cam.y) * Chunk::SIZE_OF_CELL - 5)));
			circle.setRadius(10.f);
			circle.setFillColor(sf::Color(0, 0, 250));

			Singleton::getInstance()._window->draw(circle);
		}
	}
	/*if (Singleton::getInstance().isValidating)
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
	*/

}

void PathFinding::find_vertex(const WayPoint& wp, const WayPointGraph& graph)
{
	std::cout << "coucou" << std::endl;
	_vertex_found = std::make_pair(0, false);
	for (WayPointID id = 0; id < boost::num_vertices(graph); ++id)
	{
		if (equal(graph[id].pos, wp.pos))
		{
			std::cout << "YOYOYOYO x " << graphe[id].pos.first << " y " << graphe[id].pos.first << std::endl;
			_vertex_found = std::make_pair(id, true);
		}
		//

	}

}

bool PathFinding::equal(const std::pair<float, float>& p1, const std::pair<float, float>& p2)
{
	const float EPS = 1e-6;
	return (std::fabs(p1.first - p2.first) < EPS &&
		std::fabs(p1.second - p2.second) < EPS);
}

void PathFinding::findMeAPath(sf::Vector2i&begin, sf::Vector2i &end)
{
	std::vector<WayPointID> p(boost::num_vertices(graphe));
	std::vector<float>      d(boost::num_vertices(graphe));
	bool vertex_start_found;
	WayPointID start;
	WayPoint startPoint;
	startPoint.pos.first = begin.x;
	startPoint.pos.second = begin.y;

	find_vertex(startPoint, graphe);
	std::tie(start, vertex_start_found) = _vertex_found;
	if (vertex_start_found)
	{

	//	std::cout << "start point found !!" << std::endl;
	}
	else
		return;

	bool vertex_goal_found;
	WayPointID goal;
	WayPoint goalPoint;
	goalPoint.pos.first = end.x;
	goalPoint.pos.second = end.y;

	find_vertex(goalPoint, graphe);
	std::tie(goal, vertex_goal_found) = _vertex_found;
	if (vertex_goal_found)
		std::cout << "Goal point found" << std::endl;
	else
		return;
	//std::cout << "debut x " << graphe[start].pos.first << " y " << graphe[start].pos.first << "FIN x" << graphe[goal].pos.first << " y " << graphe[goal].pos.second << std::endl;
	//system("pause");
	float weight = 1.f;
	shortest_path.clear();
	try {
		boost::astar_search
			(
			graphe,
			start,
			boost::astar_heuristic<WayPointGraph, float>(),
			boost::predecessor_map(&p[0]).distance_map(&d[0]).visitor(astar_goal_visitor(goal)).weight_map(boost::get(&WayPointConnection::dist, graphe))
			);

	}
	catch (found_goal fg) {

		for (WayPointID v = goal;; v = p[v]) {
			//std::cout << "WAY ! x" << graphe[v].pos.first << " y " << graphe[v].pos.second << std::endl;
			shortest_path.push_front(v);
			if (p[v] == v)
				break;
		}
	}
}


void PathFinding::addVertexPoint(sf::Vector2i &pos)
{
	WayPointID wpID = boost::add_vertex(graphe);
	graphe[wpID].pos.first = pos.x / Chunk::SIZE_OF_CELL;
	graphe[wpID].pos.second = pos.y / Chunk::SIZE_OF_CELL; // Is NOT OK

}