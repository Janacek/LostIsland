#include "HarmfullAnimal.h"
#include "ImageManager.h"
#include "Map.h"
#include "Chunk.h"
#include "MapEnvironment.h"
#include "Player.h"
#include "Meat.h"
#include "ShadersManager.h"
#include "Fur.h"

std::string &HarmfullAnimal::serialize() const
{
	std::string toto;
	return (toto);
}

void HarmfullAnimal::deserialize(std::ifstream &) throw (MyException)
{
	// load
}

HarmfullAnimal::HarmfullAnimal(sf::Vector2f &position, int life, Camera *cam)
: _camera(cam), AEntity(1.f, true, sf::Vector2f(position), 0, sf::FloatRect(0, 0, 0, 0), life)
{
	_rect.setSize(sf::Vector2f(32, 32));
	_rect.setPosition(_position);
	_speed = 2;
	_oldTime = 0;
	_iterPath = 0;
	_hasAPath = false;
	_firstPath = true;
	_isSelected = true;
}

HarmfullAnimal::~HarmfullAnimal()
{

}
void HarmfullAnimal::changeAnimation(sf::Vector2f&pos, std::pair<float, float>front)
{
	if (front.first > floor(pos.x))
	{
		//_anim->setAnimation(2);
		_curAnim = _walkRight;
	}
	if (front.first < floor(pos.x))
	{
		//_anim->setAnimation(1);
		_curAnim = _walkLeft;
	}
	if (front.second < floor(pos.y))
	{
		//_anim->setAnimation(3);
		_curAnim = _walkUp;
	}
	if (front.second > floor(pos.y))
	{
		//_anim->setAnimation(0);
		_curAnim = _walkDown;
	}
}
void HarmfullAnimal::moveToNextWP()
{
	double dt = 0;
	double dt2 = 0;
	double time;

	time = _mvtClock.getElapsedTime().asSeconds();
	dt = time - _oldDtMvt;
	_oldDtMvt = time;
	_animatedSprite->play(*_curAnim);

	/*if (_iterPath > IT_BEF_STOP)
	{
	_isStop = true;
	_path.clear();
	if (_oldTime == 0)
	_oldTime = time;
	dt2 = time - _oldTime;
	}
	if (dt2 > TIMESTOP)
	{
	_isStop = false;
	_iterPath = 0;
	_oldTime = 0;
	}*/
	if (!_path.empty())
	{
		//_anim->play();
		_animatedSprite->play(*_curAnim);
		_isMoving = true;
		sf::Vector2f tmp(0, 0);
		tmp.x = ((_posDisp.x + 25) / Chunk::SIZE_OF_CELL) + _camera->_position.x;
		tmp.y = ((_posDisp.y + 25) / Chunk::SIZE_OF_CELL) + _camera->_position.y;
		//std::cout << "COIN HAUT GAUCHE : x " << floor(_pos.x) << " y " << floor(_pos.y) <<" pos reel droite  x " << floor(tmp.x) << " y "<< floor(tmp.y)  << std::endl;

		if (_path.front().first == floor(_position.x) && _path.front().second == floor(_position.y) &&
			_path.front().first == floor(tmp.x) && _path.front().second == floor(tmp.y)) // && que chaque coté est dans la case

		{

			_path.pop_front();
			changeAnimation(_position, _path.front());
			return;
		}

		if (_position.x > _path.front().first)
			_position.x -= static_cast<float>(dt * _speed);
		if (_position.x < _path.front().first)
			_position.x += static_cast<float>(dt * _speed);
		if (_position.y > _path.front().second)
			_position.y -= static_cast<float>(dt *_speed);
		if (_position.y < _path.front().second)
			_position.y += static_cast<float>(dt * _speed);
		//std::cout << "getBoxCollider : x " << _animatedSprite->getGlobalBounds().left << "y " << _animatedSprite->getGlobalBounds().top << std::endl;


	}
	else{

		//_anim->pause();
		_animatedSprite->pause();
		_isMoving = false;
		_hasAPath = false;
	}
	sf::Time t = sf::seconds(dt);;
	_animatedSprite->update(t);
}


void HarmfullAnimal::doAction(AEntity *o)
{
	o->getAction(this);
}

void HarmfullAnimal::getAction(AEntity *o)
{
	_life -= o->getDamage();
	if (_life <= 0)
	{
		Player *player = dynamic_cast<Player *>(o);
		player->addEntityInInventory(new Meat);
		if (std::rand() % 10 <= 4)
			player->addEntityInInventory(new Fur);
		_isDead = true;
	}
}

void HarmfullAnimal::loadAnimation(std::string const &string_anim, float)
{


}

void HarmfullAnimal::draw(sf::RenderTexture *, sf::Shader &shader) // To edit
{
	_posDisp.x = ((_position.x - _camera->_position.x) * Chunk::SIZE_OF_CELL);
	_posDisp.y = ((_position.y - _camera->_position.y) * Chunk::SIZE_OF_CELL);

	if (!_isDead)
	{
		_animatedSprite->setPosition(_posDisp);
		ShadersManager::getInstance().get(BLOOM)->setParameter("RenderedTexture", sf::Shader::CurrentTexture);
		Singleton::getInstance()._window->draw(*_animatedSprite, ShadersManager::getInstance().get(BLOOM));
	}
}

void HarmfullAnimal::draw(sf::RenderTexture *)
{
	_posDisp.x = ((_position.x - _camera->_position.x) * Chunk::SIZE_OF_CELL);
	_posDisp.y = ((_position.y - _camera->_position.y) * Chunk::SIZE_OF_CELL);

	if (!_isDead)
	{
		_animatedSprite->setPosition(_posDisp);
		Singleton::getInstance()._window->draw(*_animatedSprite);
	}
	//this->_anim->show(_posDisp);
}

void HarmfullAnimal::update(Map &map)
{
	if (!_path.empty() && _hasAPath == false) // on va check tous les draw qui sont en rapport aux lapins
	{
		_hasAPath = true;
		map.setEntityMap(NULL, static_cast<int>(floor(_position.y)), static_cast<int>(floor(_position.x)));
		if (map.getEntitiesMap()[static_cast<int>(floor(_path.back().second))][static_cast<int>(floor(_path.back().first))]._component == NULL)
		{
			map.setEntityMap(this, static_cast<int>(floor(_path.back().second)), static_cast<int>(floor(_path.back().first)));
		}
	}
	moveToNextWP();
	//std::cout << " x " << _animatedSprite->getGlobalBounds().left << " y " <<  _animatedSprite->getGlobalBounds().top << std::en
}

Type HarmfullAnimal::getType() const
{
	return HARMFULL_ANIMAL;
}
sf::FloatRect HarmfullAnimal::getBoxCollider() const
{
	return _animatedSprite->getGlobalBounds();
}

