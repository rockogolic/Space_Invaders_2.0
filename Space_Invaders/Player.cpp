#include "pch.h"
#include "Player.h"

// one texture for Player and another for what he shoots with
Player::Player(const Texture * texturePlayer, const Texture* textureShot) {

	sprite.setTexture(*texturePlayer);
	spriteShot.setTexture(*textureShot);

	// center the origin of the sprite
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0f, sprite.getTexture()->getSize().y / 2.0f);
	spriteShot.setOrigin(spriteShot.getTexture()->getSize().x / 2.0f, spriteShot.getTexture()->getSize().y / 2.0f);

	// set startPosition. def = 640/2 , 480-26
	sprite.setPosition(_startPos);

	_collision = false;
	_dead = false;
	_shot = false;

	_health = 3;

}

Player::~Player() {}

Vector2f Player::_startPos = { 640 / 2, 480 - 26 };

void Player::shoot() {
	// do I need the first if loop?
	// leave only the second one. Think. With the current code I will press "SPACE" 2 times to fire a missile
	if (_shot == false) {
		spriteShot.setPosition(sprite.getPosition());
		_shot = true;
	}
	else if (_shot == true) {
		spriteShot.move(0.0f, -0.45f);
		if (spriteShot.getPosition().y < -10) {
			_shot = false;
		}
	}
	/* 
	if (_shot == false) {
		_shot = true;
		spriteShot.setPosition(sprite.getPosition());
		spriteShot.move(0.0f, -0.45f);
		if (spriteShot.getPosition().y < -10) {
			_shot = false;
		}
	}
	*/

	// OR

	/*
	if (_shot == false) {
		spriteShot.setPosition(sprite.getPosition());
		_shot = true;
		if (_shot == true) {
			spriteShot.move(0.0f, -0.45f);
			if (spriteShot.getPosition().y < -10) {
				_shot = false;
			}
		}
	}
	*/


}


