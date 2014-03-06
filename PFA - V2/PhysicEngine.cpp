#include "PhysicEngine.h"
#include "MapEnvironment.h"

PhysicEngine::PhysicEngine(Map *&map, Camera *cam) : _map(map), _cam(cam)
{
	_isLaunch = false;
	_isRunning = true;
}

PhysicEngine::~PhysicEngine()
{

}

void PhysicEngine::init()
{


	this->_isFirst = true;

	_isLaunch = true;
	_pathFinding.initPathfinding(_map, _cam);
}

void PhysicEngine::setCamPos(sf::Vector2f &cam)
{
}
bool PhysicEngine::findMeAPath(sf::Vector2i&begin, sf::Vector2i &end, AEntity &ent)
{
	return _pathFinding.findMeAPath(begin, end, ent);
}

bool PhysicEngine::getIsLaunch() const
{
	return _isLaunch;
}

sf::Vector2f PhysicEngine::lerp(sf::Vector2f a, sf::Vector2f b, float f)
{
	return a + f * (b - a);
}

float PhysicEngine::diffDist(sf::Vector2f const &d1, sf::Vector2f const &d2)
{
	float dist = 0;
	dist = std::abs(d1.x - d2.x);
	dist += std::abs(d1.y - d2.y);
	return dist;
}

bool PhysicEngine::tryFindAPathEntity(sf::Vector2i&tmp_begin, sf::Vector2i &tmp_end, AEntity &ent)
{
	ent.setPathToGo(1.f);
	
	while (/*ent.getIsPathFound() == false ||*/ ent.getPathToGo() >= 0)
	{
		sf::Vector2f tmp_lerp_begin;
		sf::Vector2f tmp_lerp_end;


		//tmp_begin.x = (tmp_begin.x + _map->getCamPos().x * Chunk::SIZE_OF_CELL) / Chunk::SIZE_OF_CELL; // ISOK
		//tmp_begin.y = (tmp_begin.y + _map->getCamPos().y * Chunk::SIZE_OF_CELL) / Chunk::SIZE_OF_CELL;
		tmp_lerp_begin.x = static_cast<float>(tmp_begin.x);
		tmp_lerp_begin.y = static_cast<float>(tmp_begin.y);

		tmp_end.x = static_cast<int>(ent.getPosition().x); // player en selec
		tmp_end.y = static_cast<int>(ent.getPosition().y);
		tmp_lerp_end.x = static_cast<float>(tmp_end.x);
		tmp_lerp_end.y = static_cast<float>(tmp_end.y);
		ent.addToPathToGo(-0.1f);
		
		tmp_lerp_begin = lerp(tmp_lerp_begin, tmp_lerp_end, ent.getPathToGo());
		tmp_begin.x = static_cast<int>(tmp_lerp_begin.x);
		tmp_begin.y = static_cast<int>(tmp_lerp_begin.y);
		ent.setIsPathFound(false);
		if (_map->getCellMap()[tmp_begin.y][tmp_begin.x]._cellType == Cell::OCEAN
			|| _map->getEntitiesMap()[tmp_begin.y][tmp_begin.x]._component != NULL)
		{
			ent.setIsPathFound(false);
		}
		else
		{
			ent.setPathToGo(1.f);
		
			if (ent.getSelected())
			{
				ent.setIsPathFound(true);
				//tmp_end.x = ent.getPosition().x; // player en selec
				//tmp_end.y = ent.getPosition().y;
				findMeAPath(tmp_end, tmp_begin, ent);
				return true;
			}


		}
	}


	return false;
}
bool PhysicEngine::launchPf(sf::Vector2i&tmp_begin, sf::Vector2i &tmp_end, Player &ent)
{
	ent.setPathToGo(0.f);

	if (ent.getSelected())
	{
		tmp_end.x = static_cast<int>(ent.getPosition().x); // player en selec
		tmp_end.y = static_cast<int>(ent.getPosition().y);

		ent.setIsPathFound(false);

		findMeAPath(tmp_end, tmp_begin, ent);
		ent.changeMapEntity(*_map);
		return true;
	}
	return false;
}

bool PhysicEngine::tryFindAPathHuman(sf::Vector2i&tmp_begin2, sf::Vector2i &tmp_end, Player &ent, AEntity *obj)
{
	//a refaire METTRE UN WHILE
	while (/*ent.getIsPathFound() == false ||*/ ent.getPathToGo() <= 1)
	{
		
		sf::Vector2i tmp_begin = tmp_begin2;
		if (obj || (ent.getIsPathFound() && ent.getPathToGo() <= 1))
		{
			sf::Vector2f tmp_lerp_begin;
			sf::Vector2f tmp_lerp_end;
			tmp_begin.x = (static_cast<int>(tmp_begin.x + _map->getCamPos().x * Chunk::SIZE_OF_CELL)) / Chunk::SIZE_OF_CELL; // ISOK
			tmp_begin.y = (static_cast<int>(tmp_begin.y + _map->getCamPos().y * Chunk::SIZE_OF_CELL)) / Chunk::SIZE_OF_CELL;
			if (_map->getCellMap()[tmp_begin.y][tmp_begin.x]._cellType == Cell::OCEAN) //|| _pathFinding.findMeAdjacent(tmp_begin).empty())
			{
				tmp_lerp_begin.x = static_cast<float>(tmp_begin.x);
				tmp_lerp_begin.y = static_cast<float>(tmp_begin.y);

				tmp_end.x = static_cast<int>(ent.getPosition().x); // player en selec
				tmp_end.y = static_cast<int>(ent.getPosition().y);
				tmp_lerp_end.x = static_cast<float>(tmp_end.x);
				tmp_lerp_end.y = static_cast<float>(tmp_end.y);
				tmp_lerp_begin = lerp(tmp_lerp_begin, tmp_lerp_end, ent.getPathToGo());
				tmp_begin.x = static_cast<int>(tmp_lerp_begin.x);
				tmp_begin.y = static_cast<int>(tmp_lerp_begin.y);
				if (ent.getPathToGo() > 0.8)
					return false;
				ent.addToPathToGo(0.01f);
				ent.setIsPathFound(false);

			}
			else
			{

				sf::Vector2i tmp_target = tmp_begin;
				//if (_map->getEntitiesMap()[tmp_begin.y][tmp_begin.x]._component != NULL)
				{
					/*Si click sur entity qui bouge : 
					-on peut filer au perso son ptr ???
					*/
					for (sf::Vector2f * vect : _pathFinding.findMeAdjacent(tmp_begin))
					{
						tmp_begin.x = static_cast<int>(vect->x);
						tmp_begin.y = static_cast<int>(vect->y);
						if (obj)
						{
							ent._objective = obj;
							return (launchPf(tmp_begin, tmp_end, ent));

						}
						
						if (_map->getEntitiesMap()[tmp_begin.y][tmp_begin.x]._component == NULL)
						{
							//ent.setTarget(_map->getEntitiesMap()[tmp_target.y][tmp_target.x]._component->getType());
							ent._objective = _map->getEntitiesMap()[tmp_target.y][tmp_target.x]._component;
							/*	if (_map->getEntitiesMap()[tmp_target.y][tmp_target.x]._component)
							+						{
							+*/
							//ent.setTarget(_map->getEntitiesMap()[tmp_target.y][tmp_target.x]._component->getType());
							//ent._objective = _map->getEntitiesMap()[tmp_target.y][tmp_target.x]._component;
							/*	}*/
							return (launchPf(tmp_begin, tmp_end, ent));
						}

					}
				}
				return false;
			}
		}
		else
		{
			tmp_begin.x = (static_cast<int>(tmp_begin.x + _map->getCamPos().x * Chunk::SIZE_OF_CELL)) / Chunk::SIZE_OF_CELL; // ISOK
			tmp_begin.y = (static_cast<int>(tmp_begin.y + _map->getCamPos().y * Chunk::SIZE_OF_CELL)) / Chunk::SIZE_OF_CELL;
		}
		/*if (_map->getEntitiesMap()[100][63]._component->getType() == PLAYER)
		{
		std::cout << "YA UN JOUEUR IRRRRRRRRR" << std::endl;
		}*/
		if (_map->getCellMap()[tmp_begin.y][tmp_begin.x]._cellType == Cell::OCEAN
			|| _map->getEntitiesMap()[tmp_begin.y][tmp_begin.x]._component != NULL
			)
		{
			ent.setIsPathFound(true);
		}
		else
		{
			ent.setTarget(Type::BADTYPE);
			ent._objective = NULL;
			return (launchPf(tmp_begin, tmp_end, ent));

		}

	}
}

void PhysicEngine::updatePos(std::vector<Player *> players, std::vector<AEntity *> entities)
{
	bool hasObjectif = false;
	std::vector<AEntity *>::iterator obj_it ;
	sf::Vector2i mousePos = sf::Mouse::getPosition(*Singleton::getInstance()._window);
	sf::Vector2i _posSelectedArea = Singleton::getInstance().posRightClickPressed;

	_posSelectedArea.x -= static_cast<int>(Singleton::getInstance().updatePosLeftClickPressed.x * Chunk::SIZE_OF_CELL);
	_posSelectedArea.y -= static_cast<int>(Singleton::getInstance().updatePosLeftClickPressed.y * Chunk::SIZE_OF_CELL);

	sf::RectangleShape selectionZone(sf::Vector2f(static_cast<float>(mousePos.x - _posSelectedArea.x),
		static_cast<float>(mousePos.y - _posSelectedArea.y)));
	selectionZone.setPosition(static_cast<float>(_posSelectedArea.x),
		static_cast<float>(_posSelectedArea.y));

	if (selectionZone.getSize().x == 0 && selectionZone.getSize().y == 0) {
		selectionZone.setSize(sf::Vector2f(1, 1));
	}
	if (!Singleton::getInstance().isRightClicking)
	{
		_isFirst = true;
	}
	for (std::vector<Player *>::iterator it = players.begin(); it != players.end(); ++it)
	{
		for (auto it2 = entities.begin(); it2 != entities.end(); ++it2) // a voir si ca fait pas ramer 
		{

			

			if (Singleton::getInstance().isRightClicking)
			{
				sf::RectangleShape tmp(sf::Vector2f(32, 32));

				sf::Vector2f posDisp;
				posDisp.x = (((*it2)->getPosition().x - _map->_camera->_position.x) * Chunk::SIZE_OF_CELL);
				posDisp.y = (((*it2)->getPosition().y - _map->_camera->_position.y) * Chunk::SIZE_OF_CELL);

				tmp.setPosition(posDisp);
				if (selectionZone.getGlobalBounds().intersects(tmp.getGlobalBounds()))
				{
					hasObjectif = true;
					obj_it = it2;
				}
			}

			if ((*it2)->getType() == BUNNY && (*it2)->getIsStopped() == false)
			{
				if (diffDist((*it)->getPosition(), (*it2)->getPosition()) < 6 && (*it2)->getIsMoving() == false) // ca a lair de marcher
				{

					sf::Vector2i tmp_begin;
					sf::Vector2i tmp_end(static_cast<int>((*it2)->getPosition().x), static_cast<int>((*it2)->getPosition().y));
					sf::Vector2f tmp_lerp_begin;
					sf::Vector2f tmp_lerp_end;
					if ((*it2)->getPosition().x > (*it)->getPosition().x && (*it2)->getPosition().y < (*it)->getPosition().y)
					{

						tmp_begin.x = _map->getSize().x * Chunk::NB_CELLS;
						tmp_begin.y = 3;
					}
					else if ((*it2)->getPosition().x < (*it)->getPosition().x && (*it2)->getPosition().y < (*it)->getPosition().y)
					{

						tmp_begin.x = 0;
						tmp_begin.y = 0;
					}
					else if ((*it2)->getPosition().x < (*it)->getPosition().x && (*it2)->getPosition().y >(*it)->getPosition().y)
					{

						tmp_begin.x = 0;
						tmp_begin.y = _map->getSize().y * Chunk::NB_CELLS;
					}
					else if ((*it2)->getPosition().x > (*it)->getPosition().x && (*it2)->getPosition().y > (*it)->getPosition().y)
					{

						tmp_begin.x = _map->getSize().x * Chunk::NB_CELLS;
						tmp_begin.y = _map->getSize().y * Chunk::NB_CELLS;
					}
						tryFindAPathEntity(tmp_begin, tmp_end, **it2);
				


				}
			}
		}
	}

	if ((Singleton::getInstance().isRightClicking && this->_isFirst))
	{
		this->_isFirst = false;

		for (std::vector<Player *>::iterator it = players.begin(); it != players.end(); ++it)
		{

			if ((*it)->getSelected())
			{
				sf::Vector2i tmp_begin = sf::Mouse::getPosition(*Singleton::getInstance()._window);
				sf::Vector2i tmp_end;
				if (hasObjectif )
				{
					tryFindAPathHuman(tmp_begin, tmp_end, **it, *obj_it);
				}
				else
					tryFindAPathHuman(tmp_begin, tmp_end, **it, NULL);
				//
			}
		}
	}

}

void PhysicEngine::update()
{

	_pathFinding.updatePath();
}

void PhysicEngine::addVertexPoint(sf::Vector2i &pos)
{
	_pathFinding.addVertexPoint(pos);
}