#include "WoodenPlank.h"
#include "Campfire.h"
#include "Player.h"

std::string &WoodenPlank::serialize() const
{
	std::string toto;
	return (toto);
}

void WoodenPlank::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

WoodenPlank::WoodenPlank()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void WoodenPlank::doAction(AEntity *other)
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
			player->addEntityInInventory(new WoodenPlank);
		}
	}
}

void WoodenPlank::getAction(AEntity *other)
{
	// ??
}

void WoodenPlank::loadAnimation(std::string const &, float)
{

}

void WoodenPlank::update(Map &)
{

}

void WoodenPlank::draw(sf::RenderTexture *, sf::Shader &)
{

}

void WoodenPlank::draw(sf::RenderTexture *)
{

}

Type WoodenPlank::getType() const
{
	return WOODEN_PLANK;
}

WoodenPlank::~WoodenPlank()
{

}