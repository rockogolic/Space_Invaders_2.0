#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(Texture* texture) {

	sprite.setTexture(*texture);

	// center the origin of the sprite
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0f, sprite.getTexture()->getSize().y / 2.0f);

	// set startPosition. def = 0,0
	sprite.setPosition(0, 0);
}

Enemy::~Enemy() {}

Enemy::Enemy(const Enemy& enemy) {
	Enemy * new_enemy;
}

bool Enemy::isActive() { return _active; }
bool Enemy::isDead() { return _dead; }

void Enemy::Update() {

}
 
void Enemy::setStartPosition(Vector2f startPos) {
	_startPos = startPos;
}
