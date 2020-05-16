#include "pch.h"
#include "Enemy.h"
#include <iostream>

Enemy::Enemy(const Texture* texture) {
	
	sprite.setTexture(*texture);

	// center the origin of the sprite
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0f, sprite.getTexture()->getSize().y / 2.0f);

	// set startPosition. def = 0,0
	this->_startPos = Vector2f( 0,0 );
	setPosition(_startPos);

	_active = true;
	_dead = false;

	enemy_side = _side::NONE;
}

Enemy::Enemy() {}

Enemy::~Enemy() { 
	delete new_enemy; 
}

Enemy::Enemy(const Enemy& enemy) {
	
	new_enemy = new Enemy;
	this->sprite = enemy.sprite;

	// def _startPos = 0,0
	this->_startPos = Vector2f(0, 0);
	this->setPosition(_startPos);

	this->_active = true;
	this->_dead = false;
	this->_collision = false;

	this->enemy_side = _side::NONE;

}

bool Enemy::isActive() { return _active; }
bool Enemy::isDead() { return _dead; }
bool Enemy::setDead() { return _dead = true; }

// MOVEMENT
void Enemy::Move(RenderWindow * window) {
	// if some condition (maybe if isActive || if canMove)
	// move (fction of deltaTime) to the right from the _startPos
	// if (spritegetPos >= screenX)
	// then move down by a bit
	// then if (spritegetPos >= 

	//float height = window->getSize().y - sprite.getPosition().y;

	_position = sprite.getPosition();	// update vector2f _position with the latest position

	if (sprite.getPosition().x >= (window->getSize().x - sprite.getTexture()->getSize().x / 2.0f)) {
		
		_position.y += sprite.getTexture()->getSize().y;
		sprite.setPosition((window->getSize().x - sprite.getTexture()->getSize().x / 2.0f), _position.y);
		//_startPos.y += 2 * sprite.getTexture()->getSize().y;
		enemy_side = _side::LEFT;
		
	}
	else if (sprite.getPosition().x <= (sprite.getTexture()->getSize().x / 2.0f)) {
		
		_position.y += sprite.getTexture()->getSize().y;
		//_startPos.y += 2 * sprite.getTexture()->getSize().y;
		sprite.setPosition((sprite.getTexture()->getSize().x / 2.0f), _position.y);
		enemy_side = _side::RIGHT;
	}

	if (_active){
		if (enemy_side == _side::RIGHT || enemy_side == _side::NONE) {
			sprite.move(0.05f, 0);
		}
		else if (enemy_side == _side::LEFT) {
			sprite.move(-0.05f, 0);
		}
		if (sprite.getPosition().y >= (window->getSize().y)) {
			_won = true;
			std::cout << "You lose" << std::endl;
			_active = false;
		}
	}
}

// Collision with Player

void Enemy::Collision(Player* player) {

	if (
		(player->spriteShot.getPosition().y >= (sprite.getPosition().y - sprite.getTexture()->getSize().y / 2.0f))
		&&
		(player->spriteShot.getPosition().y <= (sprite.getPosition().y + sprite.getTexture()->getSize().y / 2.0f))
		&&
		(player->spriteShot.getPosition().x >= (sprite.getPosition().x - sprite.getTexture()->getSize().x / 2.0f))
		&&
		(player->spriteShot.getPosition().x <= (sprite.getPosition().x + sprite.getTexture()->getSize().x / 2.0f))
		&&
		_active
		) 
	{
		player->spriteShot.setPosition(700, 700);

		_collision = true;
		player->hitEnemy();		// sets private _shot = false; (reset)
		std::cout << "You hit the alien" << std::endl;
		_active = false;
	}
}
 
void Enemy::setStartPosition(Vector2f startPos) {
	_startPos = startPos;
}

void Enemy::setPosition(Vector2f position) {
	sprite.setPosition(position);
	_position = position;
}
