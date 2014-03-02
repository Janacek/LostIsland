#include "PalmTree.h"
#include					"Singleton.h"
#include					"ImageManager.h"
#include	"Map.h"
#include	"MapEnvironment.h"
#include	"Player.h"
#include "Wood.h"

PalmTree::PalmTree()
: Tree()
{
	loadAnimation("./Media/images/palmtree_animation.png", 0.5f);
}

void PalmTree::Animate(std::string const &)
{

}

void PalmTree::loadAnimation(std::string const &string_anim, float speed)
{
	sf::Texture *imgAnim = new sf::Texture;
	if (!imgAnim->loadFromFile(string_anim))
		std::cerr << "image non charge" << std::endl;
	sf::Image img_tmp = imgAnim->copyToImage();
	imgAnim->loadFromImage(img_tmp);

	_waveAnim = new Animation();
	_waveAnim->setSpriteSheet(*imgAnim);
	_waveAnim->addFrame(sf::IntRect(0, 0, 32, 49));
	_waveAnim->addFrame(sf::IntRect(32, 0, 32, 49));
	_waveAnim->addFrame(sf::IntRect(64, 0, 32, 49));
	_waveAnim->addFrame(sf::IntRect(96, 0, 32, 49));

	_animatedSprite = new AnimatedSprite(sf::seconds(speed), true, false);
	_curAnim = _waveAnim;


	_animatedSprite->play(*_curAnim);
}

void PalmTree::draw(sf::RenderTexture *tex, sf::Shader &shader)
{
	int posX = static_cast<int>(_position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL);
	int posY = static_cast<int>(_position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL - 20);
	sf::Sprite tmp;
	if (!_isCut)
	{
		_animatedSprite->setPosition(_position);
		tex->draw(*_animatedSprite);
		ShadersManager::getInstance().get(BLOOM)->setParameter("RenderedTexture", sf::Shader::CurrentTexture);
		tex->draw(*_animatedSprite, ShadersManager::getInstance().get(BLOOM));
	}
	else
	{
		tmp.setTexture((*ImageManager::getInstance().get(CUT_PALMTREE)));
		tmp.setPosition(_position.x, _position.y);
		ShadersManager::getInstance().get(BLOOM)->setParameter("RenderedTexture", sf::Shader::CurrentTexture);
		tex->draw(tmp, ShadersManager::getInstance().get(BLOOM));
	}
}

void PalmTree::draw(sf::RenderTexture *tex)
{
	int posX = static_cast<int>(_position.x - Singleton::getInstance()._window->getSize().x  * Chunk::SIZE_OF_CELL);
	int posY = static_cast<int>(_position.y - Singleton::getInstance()._window->getSize().y  * Chunk::SIZE_OF_CELL - 20);
	
	
	
	sf::Sprite tmp;
	if (!_isCut)
	{
		_animatedSprite->setPosition(_position);
		tex->draw(*_animatedSprite);
		//tmp.setTexture((*ImageManager::getInstance().get(PALMTREE)));
	}
	else
	{
		tmp.setTexture((*ImageManager::getInstance().get(CUT_PALMTREE)));
		tmp.setPosition(_position.x, _position.y);
		tex->draw(tmp);
	}
}

void PalmTree::update(Map &map)
{
	if (_duration <= 0 && !_isCut)
	{
		_isCut = true;
		// ICI ON DROP DU BOIS
	}

	double dt = 0;
	double time;

	time = _mvtClock.getElapsedTime().asSeconds();
	dt = time - _oldDtMvt;
	_oldDtMvt = time;

	_animatedSprite->play(*_curAnim);

	sf::Time t = sf::seconds(dt);
	_animatedSprite->update(t);
}

void PalmTree::doAction(AEntity *)
{
	// Do nothing
}

void PalmTree::getAction(AEntity *other)
{
	if (!_isHarvested)
	{
		try // si c'est un player
		{
			Player *player = dynamic_cast<Player *>(other);
			player->addEntityInInventory(new Wood);
			_isHarvested = true;
		}
		catch (std::bad_cast ex)
		{
			std::cout << "Cas non géré. C'est un animal qui attaque l'arbre." << std::endl;
		}
	}
	_duration -= other->getDamage();
}