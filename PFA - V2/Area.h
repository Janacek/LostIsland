#pragma once

#include		<iostream>
#include		"Coordinates.hpp"

	class		Area : public Coordinates 
{
public:
	Area(Coordinates &);
	virtual ~Area();
	void		print() const;
private:
	//sf::image ou sf::sprite?
};