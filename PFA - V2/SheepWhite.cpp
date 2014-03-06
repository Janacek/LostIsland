#include "SheepWhite.h"

SheepWhite::SheepWhite(sf::Vector2f &position, int life, Camera *cam)
: Sheep(position, life, cam)
{
	loadAnimation("Media/images/sheep.png", 0.1f);
}

SheepWhite::~SheepWhite()
{

}

void SheepWhite::loadAnimation(std::string const &string_anim, float time)
{
	sf::Texture *imgAnim = new sf::Texture;
	if (!imgAnim->loadFromFile(string_anim))
		std::cerr << "image non charge" << std::endl;
	sf::Image img_tmp = imgAnim->copyToImage();
	imgAnim->loadFromImage(img_tmp);


	_walkDown = new Animation();
	_walkDown->setSpriteSheet(*imgAnim);
	_walkDown->addFrame(sf::IntRect(0, 0, 32, 32));
	_walkDown->addFrame(sf::IntRect(32, 0, 32, 32));
	_walkDown->addFrame(sf::IntRect(64, 0, 32, 32));

	_walkLeft = new Animation();
	_walkLeft->setSpriteSheet(*imgAnim);
	_walkLeft->addFrame(sf::IntRect(0, 32, 32, 32));
	_walkLeft->addFrame(sf::IntRect(32, 32, 32, 32));
	_walkLeft->addFrame(sf::IntRect(64, 32, 32, 32));

	_walkRight = new Animation();
	_walkRight->setSpriteSheet(*imgAnim);
	_walkRight->addFrame(sf::IntRect(0, 64, 32, 32));
	_walkRight->addFrame(sf::IntRect(32, 64, 32, 32));
	_walkRight->addFrame(sf::IntRect(64, 64, 32, 32));

	_walkUp = new Animation();
	_walkUp->setSpriteSheet(*imgAnim);
	_walkUp->addFrame(sf::IntRect(0, 96, 32, 32));
	_walkUp->addFrame(sf::IntRect(32, 96, 32, 32));
	_walkUp->addFrame(sf::IntRect(64, 96, 32, 32));


	_animatedSprite = new AnimatedSprite(sf::seconds(0.1), true, false);
	_curAnim = _walkDown;


	_animatedSprite->play(*_curAnim);
}