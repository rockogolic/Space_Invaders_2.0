#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(Texture& texture) {
	_sprite.setTexture(texture);


}

Enemy::~Enemy() {}

Sprite Enemy::sprite() {
	return _sprite;
}

void Enemy::centerOrigin() {
	_sprite.setOrigin(_sprite.getTexture()->getSize().x / 2.0f, _sprite.getTexture()->getSize().y / 2.0f);
}
