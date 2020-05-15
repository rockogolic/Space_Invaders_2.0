#include "pch.h"
#include "setsprite.h"

setSprite::setSprite(const Texture* texture) {

	sprite.setTexture(*texture);
}

setSprite::~setSprite() {}