#include "pch.h"
#include "Player.h"
#include "Enemy.h"

#include <iostream>

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
	/*
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
	//*/
	
	//*
	if (_shot == false) {
		_shot = true;
		Vector2f shotPosition = sprite.getPosition();
		spriteShot.setPosition(shotPosition);

	}
	//*/
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
	//*/
}

void Player::Collision(Enemy * enemy) {
	if (
		// shot - player collision
		(enemy->spriteShot.getPosition().y >= (sprite.getPosition().y - sprite.getTexture()->getSize().y / 2.0f))
		&&
		(enemy->spriteShot.getPosition().y <= (sprite.getPosition().y + sprite.getTexture()->getSize().y / 2.0f))
		&&
		(enemy->spriteShot.getPosition().x >= (sprite.getPosition().x - sprite.getTexture()->getSize().x / 2.0f))
		&&
		(enemy->spriteShot.getPosition().x <= (sprite.getPosition().x + sprite.getTexture()->getSize().x / 2.0f))
		&&
		(_dead == false)
		)
	{
		enemy->spriteShot.setPosition(-700, -700);

		_collision = true;
		enemy->hitPlayer();		// sets private _shot = false; (reset)
		std::cout << "You have been hit" << std::endl;
		_health--;
	}
}

void Player::updateShot() {
	spriteShot.move(0.0f, -0.45f);
	if (spriteShot.getPosition().y < -10) {
		_shot = false;
	}
}

void Player::hitEnemy() { _shot = false; }

void Player::isHit() { 
	_hit = true; 
	_health--; 
	if (_health <= 0) {
		_dead = true;
	}
}

const int Player::getHealth() const{
	return _health;
}
