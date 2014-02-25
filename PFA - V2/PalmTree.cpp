#include "PalmTree.h"
#include					"Singleton.h"
#include					"ImageSingleton.h"
#include	"Map.h"
#include	"MapEnvironment.h"
#include	"Player.h"
#include "Wood.h"

void PalmTree::Animate(std::string const &)
{

}

void PalmTree::draw(sf::RenderTexture *tex, sf::Shader &shader)
{
	int posX = static_cast<int>(_position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL);
	int posY = static_cast<int>(_position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL - 20);

	sf::Sprite tmp;
	if (!_isCut)
		tmp.setTexture((*ImageSingleton::getInstance().get(PALMTREE)));
	else
		tmp.setTexture((*ImageSingleton::getInstance().get(CUT_PALMTREE)));
	tmp.setPosition(_position.x, _position.y);
	ShadersManager::getInstance().get(BLOOM)->setParameter("RenderedTexture", sf::Shader::CurrentTexture);
	tex->draw(tmp, ShadersManager::getInstance().get(BLOOM));
}

void PalmTree::draw(sf::RenderTexture *tex)
{
	int posX = static_cast<int>(_position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL);
	int posY = static_cast<int>(_position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL - 20);

	sf::Sprite tmp;
	if (!_isCut)
		tmp.setTexture((*ImageSingleton::getInstance().get(PALMTREE)));
	else
		tmp.setTexture((*ImageSingleton::getInstance().get(CUT_PALMTREE)));
	tmp.setPosition(_position.x, _position.y);
	tex->draw(tmp);
}

void PalmTree::update(Map &map)
{
	if (_duration <= 0 && !_isCut)
	{
		_isCut = true;
		// ICI ON DROP DU BOIS
	}
}

void PalmTree::doAction(IEntity *)
{
	// Do nothing
}

void PalmTree::getAction(IEntity *other)
{
	try // si c'est un player
	{
		Player *player = dynamic_cast<Player *>(other);
		player->addEntityInInventory(new Wood);
	}
	catch (std::bad_cast ex)
	{
		std::cout << "Cas non géré. C'est un animal qui attaque l'arbre." << std::endl;
	}
	_duration -= other->getDamage();
}