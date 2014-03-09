#include "WaterBucket.h"
#include "Player.h"
#include "Bucket.h"
#include "Water.h"

std::string &WaterBucket::serialize() const
{
	std::string toto;
	return (toto);
}

void WaterBucket::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

WaterBucket::WaterBucket()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void WaterBucket::doAction(AEntity *other)
{
	if (other)
	{
		Player *player = dynamic_cast<Player *>(other);
		player->drink(new Water());
		player->addEntityInInventory(new Bucket);
	}
}

void WaterBucket::getAction(AEntity *other)
{

}

void WaterBucket::loadAnimation(std::string const &, float)
{

}

void WaterBucket::update(Map &)
{

}

void WaterBucket::draw(sf::RenderTexture *, sf::Shader &)
{

}

void WaterBucket::draw(sf::RenderTexture *)
{

}

Type WaterBucket::getType() const
{
	return WATERBUCKET;
}

WaterBucket::~WaterBucket(void)
{
}
