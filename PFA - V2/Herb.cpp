#include "Herb.h"
#include "ImageManager.h"
#include "ShadersManager.h"
#include "Player.h"

std::string &Herb::serialize() const
{
	std::string toto;
	return (toto);
}

void Herb::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Herb::Herb()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
	_picked = false;
}

void Herb::doAction(AEntity *other)
{
	// do action
	if (other)
	{
		Player *player = dynamic_cast<Player *>(other);
		player->addEntityInInventory(new Herb);
	}
}

void Herb::getAction(AEntity *other)
{
	if (!_picked)
	{
		_picked = true;
		_isDead = true;
		Player *player = dynamic_cast<Player *>(other);
		player->addEntityInInventory(new Herb);
	}
}

void Herb::loadAnimation(std::string const &, float)
{

}

void Herb::update(Map &)
{

}

void Herb::draw(sf::RenderTexture *tex, sf::Shader &)
{
	sf::Sprite tmp;
	tmp.setTexture((*ImageManager::getInstance().get(PICKABLE_GRASS)));
	tmp.setPosition(_position.x, _position.y + 20);
	ShadersManager::getInstance().get(BLOOM)->setParameter("RenderedTexture", sf::Shader::CurrentTexture);

	tex->draw(tmp, ShadersManager::getInstance().get(BLOOM));
}

void Herb::draw(sf::RenderTexture *tex)
{
	sf::Sprite tmp;
	tmp.setTexture((*ImageManager::getInstance().get(PICKABLE_GRASS)));
	tmp.setPosition(_position.x, _position.y + 20);
	tex->draw(tmp);
}

Type Herb::getType() const
{
	return HERB;
}

Herb::~Herb(void)
{
}
