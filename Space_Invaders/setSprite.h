#ifndef SETSPRITE_H
#define SETSPRITE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class setSprite
{

public:
	setSprite(const Texture * texture);
	~setSprite();

	// copy constructor! -> deep copy: operator = redefinition

	Sprite sprite;

private:

	// add private members

};


#endif
