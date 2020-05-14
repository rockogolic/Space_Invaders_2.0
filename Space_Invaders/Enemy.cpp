#include "pch.h"
#include "Enemy.h"
#include <iostream>

Enemy::Enemy(Texture* texture) {

	sprite.setTexture(*texture);

	// center the origin of the sprite
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0f, sprite.getTexture()->getSize().y / 2.0f);

	// set startPosition. def = 0,0
	sprite.setPosition(0, 0);
}

Enemy::Enemy() {}

Enemy::~Enemy() { 
	delete new_enemy; 
}

Enemy::Enemy(const Enemy& enemy) {
	
	new_enemy = new Enemy;
	std::cout << "Enemy is copied" << std::endl;
	this->sprite = enemy.sprite;
}

bool Enemy::isActive() { return _active; }
bool Enemy::isDead() { return _dead; }

void Enemy::Update() {

}
 
void Enemy::setStartPosition(Vector2f startPos) {
	_startPos = startPos;
}

void Enemy::setPosition(Vector2f position) {
	sprite.setPosition(position);
	_position = position;
}
