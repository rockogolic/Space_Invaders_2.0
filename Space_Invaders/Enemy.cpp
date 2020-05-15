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

}

bool Enemy::isActive() { return _active; }
bool Enemy::isDead() { return _dead; }

// MOVEMENT
void Enemy::Update() {

}
 
void Enemy::setStartPosition(Vector2f startPos) {
	_startPos = startPos;
}

void Enemy::setPosition(Vector2f position) {
	sprite.setPosition(position);
	_position = position;
}
