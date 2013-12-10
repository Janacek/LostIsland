#pragma once

#include		<iostream>
#include		"Coordinates.hpp"

class			Object : public Coordinates
{
public:
	Object(Coordinates&);
	virtual ~Object();
	void		print() const;
	void		draw(sf::RenderWindow *);
	void		update(sf::Event *);
private:
	//sf::image ou sf::sprite ?
};