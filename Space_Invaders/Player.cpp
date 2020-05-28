#include "pch.h"
#include "Player.h"
#include "Enemy.h"

// one texture for Player and another for what he shoots with
Player::Player(const Texture* texturePlayer, const Texture* textureShot, const Texture* textureWinner, RenderWindow* window) {

	sprite.setTexture(*texturePlayer);
	spriteShot.setTexture(*textureShot);
	spriteWinner.setTexture(*textureWinner);

	// center the origin of every sprite
	sprite.setOrigin(texturePlayer->getSize().x / 2.0f, texturePlayer->getSize().y / 2.0f);
	spriteShot.setOrigin(textureShot->getSize().x / 2.0f, textureShot->getSize().y / 2.0f);
	spriteWinner.setOrigin(textureWinner->getSize().x / 2.0f, textureWinner->getSize().y / 2.0f);

	// set startPosition. def = 640/2 , 480-26
	this->_startPos = Vector2f(window->getSize().x / 2.0f, window->getSize().y - this->sprite.getTexture()->getSize().y / 2.0f);
	sprite.setPosition(_startPos);

	_health = 3;
	_score = 0;
}

Player::~Player() {}

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
		this->Hit();
		std::cout << "You have been hit. Your health is: " << this->getHealth() << std::endl;
	}
}

/* Speed calculation: 

For speed calculation, v = l * f; 
where v - speed in pixels per second (px/s)
l - length covered in pixels in one second (px)
f - frequency of screen-refresh (framerate) (Hz = 1/s)

Therefore, also v = l / dt; 
where dt - time difference between refresh rate of the screen. (s)

*/

void Player::updateShot(float deltaTime) {
	spriteShot.move(0.0f, -( 765 / (1/deltaTime) ) );
	if (spriteShot.getPosition().y < -70) {
		_shot = false;
	}
}

void Player::hitEnemy() { 
	_score += 10;
	_shot = false;

}

void Player::hitBounty(int value) {
	_shot = false;
	_score += value;
}

void Player::addToScore(int value) {
	_score += value;
}

bool Player::isHit() { return _hit; }

void Player::setAlive() { 
	if (_hit) {
		_hit = false;
	}
}

void Player::setPosition(Vector2f position)
{
	sprite.setPosition(position);
}

void Player::resetPosition()
{
	sprite.setPosition(_startPos);
}

void Player::Hit() { 
	_hit = true; 
	--_health; 
	if (_health <= 0) {
		_dead = true;
	}
}

void Player::addHealth() { ++_health; }

bool Player::isDead() { return _dead; }

const int Player::getHealth() const{
	return _health;
}

const int Player::getScore() const {
	return _score;
}

void Player::byebyeWinner(float deltaTime) {
	if (isWinner() == true )
	{
		if (spriteWinner.getPosition().y >= -100)
			spriteWinner.move(0.0f, -100 * deltaTime);
	}
}

void Player::setWinner() { 
	_won = true;
	spriteWinner.setPosition(sprite.getPosition());
}
bool Player::isWinner() { return _won; }

bool Player::hasShot()
{
	return _shot;
}
