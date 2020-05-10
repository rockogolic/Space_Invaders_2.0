#include "pch.h"
#include "setSprite.h"

setSprite::setSprite(RenderWindow& _window, std::string _address) {

	(*_texture).loadFromFile(_address);
	(*_sprite).setTexture((*_texture));
	//_texture.loadFromFile(_address);
	//_sprite.setTexture(_texture);
}

setSprite::~setSprite() { 
	delete _texture;
	delete _sprite;
}

Sprite setSprite::sprite() { return (*_sprite); }