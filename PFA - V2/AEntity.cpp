#include "AEntity.h"

AEntity::AEntity(float pathToGo, bool isAMovingEntity, sf::Vector2f position, int damages, sf::FloatRect boxCollider, int life)
: _pathToGo(pathToGo), _isAMovingEntity(isAMovingEntity), _position(position), _damages(damages), _boxCollider(boxCollider), _life(life)
{
	_id = AEntityId++;
	_isSelected = false;
	_isMoving = false;
	_isPathFound = false;
	_isDead = false;
	_isActionOver = false;
	_posDisp.x = 0;
	_posDisp.y = 0;

}

void AEntity::setIsDead(bool isdead)
{
	_isDead = isdead;
}

bool AEntity::getIsDead() const
{
	return _isDead;
}

void AEntity::setIsActionOver(bool b)
{
	_isActionOver = b;
}

bool AEntity::getIsActionOver() const
{
	return _isActionOver;
}

bool AEntity::getIsSelected() const
{
	return _isSelected;
}

void AEntity::setIsSelected(bool isSelected)
{
	_isSelected = isSelected;
}

void AEntity::setId(int id)
{
	_id = id;
}

void AEntity::setPath(std::list<std::pair<float, float> >&path)
{
	_path = path;
}

std::list<std::pair<float, float> > AEntity::getPath() const
{
	return _path;
}

void AEntity::setPosition(sf::Vector2f &pos)
{
	_position = pos;
}

sf::Vector2f  AEntity::getPosition() const
{
	return _position;
}

int AEntity::getDamage(void) const
{
	return _damages;
}

bool AEntity::getIsMoving() const
{
	return _isMoving;
}

float AEntity::getPathToGo() const
{
	return _pathToGo;
}

void AEntity::setPathToGo(float f)
{
	_pathToGo = f;
}

void AEntity::addToPathToGo(float f)
{
	_pathToGo += f;
}

sf::Vector2f const AEntity::getPosDisp() const
{
	return _posDisp;
}

bool const AEntity::getSelected() const
{
	return _isSelected;
}

bool const AEntity::getIsPathFound() const
{
	return _isPathFound;
}

void AEntity::setIsPathFound(bool pathFound)
{
	_isPathFound = pathFound;
}

bool AEntity::getIsStopped() const
{
	return _isStopped;
}

bool AEntity::getIsAMovingEntity() const
{
	return _isAMovingEntity;
}

sf::FloatRect AEntity::getBoxCollider() const
{
	return _boxCollider;
}

int AEntity::getLife() const
{
	return _life;
}

void AEntity::setLife(int life)
{
	_life = life;
}

int AEntity::getId() const
{
	return _id;
}