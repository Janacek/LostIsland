#include "Food.h"


Food::Food(void)
{

}

void Food::doAction(IEntity* other)
{
	//De la food sauvage apparait
}

void Food::getAction(IEntity* other)
{

}

void Food::Animate(std::string const & string_anim)
{

}

int Food::getDamage() const
{
	return 0;
}

Type Food::getType() const
{
	return FOOD;
}

Food::~Food(void)
{
}
