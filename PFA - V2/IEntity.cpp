#include "IEntity.h"

IEntity::IEntity(float pathToGo, bool isAMovingEntity, sf::Vector2f position, int damages, sf::FloatRect boxCollider, int life)
: _pathToGo(pathToGo), _isAMovingEntity(isAMovingEntity), _position(position), _damages(damages), _boxCollider(boxCollider), _life(life)
{
	_id = IEntityId++;
	_isSelected = false;
	_isMoving = false;
	_isPathFound = false;
}

bool IEntity::getIsSelected() const
{
	return _isSelected;
}

void IEntity::setIsSelected(bool isSelected)
{
	_isSelected = isSelected;
}

void IEntity::setId(int id)
{
	_id = id;
}

void IEntity::setPath(std::list<std::pair<float, float> >&path)
{
	_path = path;
}

std::list<std::pair<float, float> > IEntity::getPath() const
{
	return _path;
}

void IEntity::setPosition(sf::Vector2f &pos)
{
	_position = pos;
}

sf::Vector2f  IEntity::getPosition() const
{
	return _position;
}

int IEntity::getDamage(void) const
{
	return _damages;
}

bool IEntity::getIsMoving() const
{
	return _isMoving;
}

float IEntity::getPathToGo() const
{
	return _pathToGo;
}

void IEntity::setPathToGo(float f)
{
	_pathToGo = f;
}

void IEntity::addToPathToGo(float f)
{
	_pathToGo += f;
}

bool const IEntity::getSelected() const
{
	return _isSelected;
}

bool const IEntity::getIsPathFound() const
{
	return _isPathFound;
}

void IEntity::setIsPathFound(bool pathFound)
{
	_isPathFound = pathFound;
}

bool IEntity::getIsStopped() const
{
	return _isStopped;
}

bool IEntity::getIsAMovingEntity() const
{
	return _isAMovingEntity;
}

sf::FloatRect IEntity::getBoxCollider() const
{
	return _boxCollider;
}

int IEntity::getLife() const
{
	return _life;
}

void IEntity::setLife(int life)
{
	_life = life;
}

int IEntity::getId() const
{
	return _id;
}