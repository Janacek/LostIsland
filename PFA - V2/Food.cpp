#include "Food.h"


Food::Food(void)
: IEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
}

void Food::doAction(IEntity* other)
{
	//De la food sauvage apparait
}

void Food::getAction(IEntity* other)
{

}

void Food::loadAnimation(std::string const & string_anim, float speed)
{

}
void Food::update(Map &map)
{

}

void Food::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Food::draw(sf::RenderTexture *)
{

}

Type Food::getType() const
{
	return FOOD;
}

Food::~Food(void)
{
}
