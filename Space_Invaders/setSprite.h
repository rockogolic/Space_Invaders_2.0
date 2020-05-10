#ifndef SETSPRITE_H
#define SETSPRITE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class setSprite
{

public:
	setSprite(RenderWindow& _window, std::string _address);
	~setSprite();

	// copy constructor! -> deep copy: operator = redefinition

	// accessors/modifiers/functions
	Sprite sprite();

private:
	Texture * _texture = new Texture;
	Sprite * _sprite = new Sprite;

};


#endif
