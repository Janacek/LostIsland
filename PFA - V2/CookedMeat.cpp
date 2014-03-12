#include "CookedMeat.h"
#include "Player.h"

std::string &CookedMeat::serialize() const
{
	std::string toto;
	return (toto);
}

void CookedMeat::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

CookedMeat::CookedMeat()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
	_value = 40;
}

void CookedMeat::doAction(AEntity* other)
{
	if (other)
	{
		Player *player = dynamic_cast<Player *>(other);
		player->eat(_value);
	}
}


void CookedMeat::getAction(AEntity* other)
{

}

void CookedMeat::update(Map &map)
{

}

void CookedMeat::loadAnimation(std::string const & string_anim, float speed)
{
}

Type CookedMeat::getType() const
{
	return COOKED_MEAT;
}

void CookedMeat::draw(sf::RenderTexture *tex, sf::Shader &shader)
{

}

void CookedMeat::draw(sf::RenderTexture *tex)
{

}


/*sf::Rect & Rock::getCollisionBox(void)
{
}*/
