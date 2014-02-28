#include "AEntity.h"

AEntity::AEntity(float pathToGo, bool isAMovingEntity, sf::Vector2f position, int damages, sf::FloatRect boxCollider, int life)
: _pathToGo(pathToGo), _isAMovingEntity(isAMovingEntity), _position(position), _damages(damages), _boxCollider(boxCollider), _life(life)
{
	_id = IEntityId++;
	_isSelected = false;
	_isMoving = false;
	_isPathFound = false;
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