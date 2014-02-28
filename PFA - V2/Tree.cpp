#include "Tree.h"
#include "Singleton.h"
#include "ImageSingleton.h"

Tree::Tree()
: IEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
	_duration = 100;
	_isCut = false;
	_isHarvested = false;
}

void Tree::doAction(IEntity* other)
{
	//L'arbre ne fait rien
}


void Tree::getAction(IEntity* other)
{

}

void Tree::update(Map &map)
{
}

void Tree::loadAnimation(std::string const & string_anim, float speed)
{
}

Type Tree::getType() const
{
	return TREE;
}

void Tree::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Tree::draw(sf::RenderTexture *)
{

}
