#include "Wood.h"
#include "Player.h"
#include "Campfire.h"

std::string &Wood::serialize() const
{
	std::string toto;
	return (toto);
}

void Wood::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

//Le Wood apparait lorsque l'on coupe un arbre
Wood::Wood(void)
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
}

void Wood::doAction(AEntity* other)
{
	if (other)
	{
		Player *player = dynamic_cast<Player *>(other);
		Map * map = player->getMap();
		sf::Vector2f pPos = player->getPosition();
		Campfire *campfire;
		if (map->getEntityAt((int)pPos.y + 1, (int)pPos.x) != NULL
			&& map->getEntityAt((int)pPos.y + 1, (int)pPos.x)->getType() == CAMPFIRE)
		{
			campfire = dynamic_cast<Campfire *>(map->getEntityAt((int)pPos.y + 1, (int)pPos.x));
			campfire->putCombustibleInFire(15);
		}
		else if (map->getEntityAt((int)pPos.y, (int)pPos.x + 1) != NULL
			&& map->getEntityAt((int)pPos.y, (int)pPos.x + 1)->getType() == CAMPFIRE)
		{
			campfire = dynamic_cast<Campfire *>(map->getEntityAt((int)pPos.y, (int)pPos.x + 1));
			campfire->putCombustibleInFire(15);
		}
		else if (map->getEntityAt((int)pPos.y, (int)pPos.x - 1) != NULL
			&& map->getEntityAt((int)pPos.y, (int)pPos.x - 1)->getType() == CAMPFIRE)
		{
			campfire = dynamic_cast<Campfire *>(map->getEntityAt((int)pPos.y, (int)pPos.x - 1));
			campfire->putCombustibleInFire(15);
		}
		else if (map->getEntityAt((int)pPos.y - 1, (int)pPos.x) != NULL
			&& map->getEntityAt((int)pPos.y - 1, (int)pPos.x)->getType() == CAMPFIRE)
		{
			campfire = dynamic_cast<Campfire *>(map->getEntityAt((int)pPos.y - 1, (int)pPos.x));
			campfire->putCombustibleInFire(15);
		}
		else
		{
			player->addEntityInInventory(new Wood);
		}
	}
}

void Wood::getAction(AEntity* other)
{
	Player *player = dynamic_cast<Player *>(other);

	player->addEntityInInventory(this);
}

void Wood::loadAnimation(std::string const & string_anim, float speed)
{

}

void Wood::update(Map &map)
{

}

void Wood::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Wood::draw(sf::RenderTexture *)
{

}

Type Wood::getType() const
{
	return WOOD;
}

Wood::~Wood(void)
{
}
