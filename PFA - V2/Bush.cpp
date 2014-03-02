#include "Bush.h"
#include "Singleton.h"
#include "ImageManager.h"
#include "Player.h"
#include "Berry.h"

Bush::Bush()
: Tree()
{
	_grown = false;
	_bushClock.restart();
	_oldDt = 0.f;
	_timeToGrow = rand() % 60 + 15;
	_growthTime = 0.f;
}

int Bush::getLife() const
{
	return 0;
}

void Bush::Animate(std::string const &)
{

}

void Bush::draw(sf::RenderTexture *tex, sf::Shader &shader)
{
	float posX = _position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL;
	float posY = _position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL;
	sf::Sprite tmp;
	if (_grown)
		tmp.setTexture((*ImageManager::getInstance().get(BUSH_FRUITS)));
	else
		tmp.setTexture((*ImageManager::getInstance().get(BUSH)));
	tmp.setPosition(_position.x, _position.y + 20);
	ShadersManager::getInstance().get(BLOOM)->setParameter("RenderedTexture", sf::Shader::CurrentTexture);
	tex->draw(tmp, ShadersManager::getInstance().get(BLOOM));
}

void Bush::draw(sf::RenderTexture *tex)
{
	float posX = _position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL;
	float posY = _position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL;

	sf::Sprite tmp;
	if (_grown)
		tmp.setTexture((*ImageManager::getInstance().get(BUSH_FRUITS)));
	else
		tmp.setTexture((*ImageManager::getInstance().get(BUSH)));
	tmp.setPosition(_position.x, _position.y + 20);
	tex->draw(tmp);
}

void Bush::update(Map &)
{
	double dt = 0;
	double time;

	time = _bushClock.getElapsedTime().asSeconds();
	dt = time - _oldDt;

	_oldDt = time;
	_growthTime += dt;
	if (_growthTime > _timeToGrow)
	{
		_grown = true;
	}
}

void Bush::doAction(AEntity *other)
{
	// do nothing
}

void Bush::getAction(AEntity *other)
{
	if (_grown)
	{
		_grown = false;
		_growthTime = 0.f;
		try // si c'est un player
		{
			Player *player = dynamic_cast<Player *>(other);
			player->addEntityInInventory(new Berry);
		}
		catch (std::bad_cast ex)
		{
			std::cout << "Cas non géré. C'est un animal qui attaque l'arbre." << std::endl;
		}
	}
}