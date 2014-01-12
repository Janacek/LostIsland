
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

	for (i = 0; i < map->getSize().y * Chunk::NB_CELLS; ++i)
	{
		for (j = 0; j < map->getSize().x * Chunk::NB_CELLS; ++j)
		{


			// on doit passer par tous les points adjacent aux points courants
			// le truc cest que Il ne peut pas y avoir 2 meme points dans la liste

			if (map->getCellMap()[i][j]._cellType != Cell::OCEAN)
			{
				WayPointID wpID = boost::add_vertex(graphe); 
				graphe[wpID].pos.first = j;
				graphe[wpID].pos.second = i;
				for (int u = 0; u < 4 ; ++u)
				{
					//std::cout << "caca" << std::endl;
					bool isPass = false;
					bool isOk = false;
					boost::graph_traits<WayPointGraph>::vertex_iterator it_b, it_end;

					std::pair<float, float> tmp((j) , (i));
					std::pair<int, int> tmp_add((j) , (i));

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
						tmp_add.first += 1;

						tmp_add.second += 1;

						if (map->getCellMap()[tmp_add.second-1][tmp_add.first]._cellType != Cell::OCEAN && 
							map->getCellMap()[tmp_add.second ][tmp_add.first - 1]._cellType != Cell::OCEAN)	
						{
							tmp.first += 1;
							tmp.second += 1;

						}
						else
							isOk = true;
					}
					else if (u == 3)
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
					//std::cout << " x " << boost::get(boost::vertex_bundle, graphe)[*it].pos.first  << " y " << boost::get(boost::vertex_bundle, graphe)[*it].pos.second << std::endl;		
					if (tmp.first >= 0 && tmp.second >= 0 && tmp.first <= map->getSize().x  * Chunk::NB_CELLS && tmp.second <= map->getSize().y  * Chunk::NB_CELLS && isOk == false)
					{
						for (boost::tie(it_b, it_end) = boost::vertices(graphe) ; it_b != it_end ; ++it_b)
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
								float dx = abs(graphe[wpID].pos.first - graphe[wpID2].pos.first);
								float dy = abs(graphe[wpID].pos.second - graphe[wpID2].pos.second);
								//std::cout << "Point 1 x " << graphe[wpID].pos.first << " y " << graphe[wpID].pos.second
								//<< "Point 2 x " << graphe[wpID2].pos.first << " y " << graphe[wpID2].pos.second << std::endl;
								boost::add_edge(wpID, wpID2, WayPointConnection(sqrt(dx * dx + dy * dy)), graphe);
							}
						}
						else
						{
							WayPointID wpID2 = (*it_b);
							if (map->getCellMap()[tmp_add.second][tmp_add.first]._cellType != Cell::OCEAN)		
							{
								float dx = abs(graphe[wpID].pos.first - graphe[wpID2].pos.first);
								float dy = abs(graphe[wpID].pos.second - graphe[wpID2].pos.second);
								//std::cout << "Point 1 x " << graphe[wpID].pos.first << " y " << graphe[wpID].pos.second
								//<< "Point 2 x " << graphe[wpID2].pos.first << " y " << graphe[wpID2].pos.second << std::endl;
								boost::add_edge(wpID, wpID2, WayPointConnection(sqrt(dx * dx + dy * dy)), graphe);
							}
						}


					}
				}


			}


		}

	}


	int n = 0;
	std::cout << "TOTAL " << u << "map x " << map->getSize().x << " y " << map->getSize().y << " size cell" << Chunk::NB_CELLS <<  std::endl;


	//for (Polygon_ *u : map->_polygons)
	//{
	//	if (u->getPolygonType() == u->GROUND)
	//	{
	//		WayPointID wpID = boost::add_vertex(graphe); 
	//		graphe[wpID].pos = u->getCenter();
	//		for (std::deque<Edge_ *>::iterator it = u->getEdges().begin() ; it != u->getEdges().end() ; ++it)
	//		{
	//			bool isPass = false;
	//			boost::graph_traits<WayPointGraph>::vertex_iterator it_b, it_end;

	//			for (boost::tie(it_b, it_end) = boost::vertices(graphe) ; it_b != it_end ; ++it_b)
	//			{
	//				if (boost::get(boost::vertex_bundle, graphe)[*it_b].pos == (*it)->_polygonsOwn.second->getCenter())
	//				{
	//					isPass = true;

	//					break;
	//				}
	//			}
	//			std::pair<Polygon_ *, Polygon_ *> t = (*it)->_polygonsOwn;
	//			if (isPass == false)
	//			{
	//				WayPointID wpID2 = boost::add_vertex(graphe);

	//				graphe[wpID2].pos = t.second->getCenter();
	//			}
	//			else
	//			{
	//				WayPointID wpID2 = (*it_b);

	//				if (t.first->getPolygonType() == t.first->GROUND)
	//				{
	//					float dx = abs(graphe[wpID].pos.first - graphe[wpID2].pos.first);
	//					float dy = abs(graphe[wpID].pos.second - graphe[wpID2].pos.second);

	//					boost::add_edge(wpID, wpID2, WayPointConnection(sqrt(dx * dx + dy * dy)), graphe);				
	//				}
	//			}
	//		}
	//	}
	//}


	//typedef boost::graph_traits <WayPointGraph>::adjacency_iterator adjacency_iterator;

}



void PathFinding::updatePath(sf::Vector2f &cam)
{

	sf::RenderTexture rt;
	rt.clear(sf::Color::Transparent);
	if (!rt.create((16* Chunk::NB_CELLS) * 8,	(16 * Chunk::NB_CELLS) * 8))
	{
		// erreur...
	}
	typedef boost::graph_traits <WayPointGraph>::edge_iterator edge_iterator_t;

	std::pair<edge_iterator_t, edge_iterator_t> ep;

	edge_iterator_t ei, ei_end;


	/*for (boost::tie(ei, ei_end) = boost::edges(graphe); ei != ei_end; ++ei)
	{

		sf::Vector2f pt1 ;
		pt1.x =  get(boost::vertex_bundle, graphe)[boost::source(*ei, graphe)].pos.first * 8;
		pt1.y =  get(boost::vertex_bundle, graphe)[boost::source(*ei, graphe)].pos.second * 8;

		sf::Vector2f pt2 ;
		pt2.x =  get(boost::vertex_bundle, graphe)[boost::target(*ei, graphe)].pos.first * 8;
		pt2.y =  get(boost::vertex_bundle, graphe)[boost::target(*ei, graphe)].pos.second * 8;

		sf::Vertex line[2] = 
		{
			sf::Vertex(pt1),
			sf::Vertex(pt2)
		};
		rt.draw(line, 2, sf::Lines);

		//std::cout << "Point 1 x " <<  pt1.x << " y " << pt1.y << " pt 2 x "<< pt2.x << " y " << pt2.y << std::endl;  
	}

	rt.display();
	*/
//sf::Texture texture = rt.getTexture();
	//map 
	//sf::Sprite sprite(texture);
	//std::cout << " camx " << cam.x << " camy " << cam.y << std::endl; 
	//sprite.setPosition(0, 0);

	//Singleton::getInstance()._window->draw(sprite);
	if (this->shortest_path.empty() == false)
		{
			for (std::list<WayPointID>::iterator it = this->shortest_path.begin() ; it != shortest_path.end() ; ++it)
			{
				sf::CircleShape circle;
				circle.setPosition(sf::Vector2f(boost::get(boost::vertex_bundle, graphe)[*it].pos.first, boost::get(boost::vertex_bundle, graphe)[*it].pos.second));
				circle.setRadius(1.f);
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