#include "Bucket.h"
#include "Player.h"
#include "WaterBucket.h"

std::string &Bucket::serialize() const
{
	// save
	std::string toto;
	return (toto);
}

void Bucket::deserialize(std::ifstream &) throw (MyException)
{
	// load
}

Bucket::Bucket()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Bucket::doAction(AEntity *other)
{
	// do action
	if (other)
	{
		Player *player = dynamic_cast<Player *>(other);
		Map * map = player->getMap();
		sf::Vector2f pPos = player->getPosition();
		if (map->getCellMap()[(int)pPos.y + 1][(int)pPos.x]._cellType == Cell::OCEAN)
			player->addEntityInInventory(new WaterBucket());
		else if (map->getCellMap()[(int)pPos.y][(int)pPos.x + 1]._cellType == Cell::OCEAN)
			player->addEntityInInventory(new WaterBucket());
		else if (map->getCellMap()[(int)pPos.y + 1][(int)pPos.x - 1]._cellType == Cell::OCEAN)
			player->addEntityInInventory(new WaterBucket());
		else if (map->getCellMap()[(int)pPos.y - 1][(int)pPos.x]._cellType == Cell::OCEAN)
			player->addEntityInInventory(new WaterBucket());
		else
			player->addEntityInInventory(new Bucket);
	}
}

void Bucket::getAction(AEntity *other)
{

}

void Bucket::loadAnimation(std::string const &, float)
{

}

void Bucket::update(Map &)
{

}

void Bucket::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Bucket::draw(sf::RenderTexture *)
{

}

Type Bucket::getType() const
{
	return BUCKET;
}

Bucket::~Bucket(void)
{
}
