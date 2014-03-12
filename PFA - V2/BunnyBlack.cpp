#include "BunnyBlack.h"

BunnyBlack::BunnyBlack(sf::Vector2f &position, int life, Camera *cam)
: Bunny(position, life, cam)
{
	loadAnimation("Media/images/rabbit.png", 0.1f);
}

BunnyBlack::~BunnyBlack()
{

}

void BunnyBlack::loadAnimation(std::string const &string_anim, float time)
{
	sf::Texture *imgAnim = new sf::Texture;
	if (!imgAnim->loadFromFile(string_anim))
		std::cerr << "image non charge" << std::endl;
	sf::Image img_tmp = imgAnim->copyToImage();
	imgAnim->loadFromImage(img_tmp);


	_walkDown = new Animation();
	_walkDown->setSpriteSheet(*imgAnim);
	_walkDown->addFrame(sf::IntRect(96, 0, 32, 32));
	_walkDown->addFrame(sf::IntRect(128, 0, 32, 32));
	_walkDown->addFrame(sf::IntRect(160, 0, 32, 32));

	_walkLeft = new Animation();
	_walkLeft->setSpriteSheet(*imgAnim);
	_walkLeft->addFrame(sf::IntRect(96, 32, 32, 32));
	_walkLeft->addFrame(sf::IntRect(128, 32, 32, 32));
	_walkLeft->addFrame(sf::IntRect(160, 32, 32, 32));

	_walkRight = new Animation();
	_walkRight->setSpriteSheet(*imgAnim);
	_walkRight->addFrame(sf::IntRect(96, 64, 32, 32));
	_walkRight->addFrame(sf::IntRect(128, 64, 32, 32));
	_walkRight->addFrame(sf::IntRect(160, 64, 32, 32));

	_walkUp = new Animation();
	_walkUp->setSpriteSheet(*imgAnim);
	_walkUp->addFrame(sf::IntRect(96, 96, 32, 32));
	_walkUp->addFrame(sf::IntRect(128, 96, 32, 32));
	_walkUp->addFrame(sf::IntRect(160, 96, 32, 32));


	_animatedSprite = new AnimatedSprite(sf::seconds(0.1), true, false);
	_curAnim = _walkDown;


	_animatedSprite->play(*_curAnim);
}