#include "pch.h"
#include "Enemy.h"
#include <iostream>
#include <random>

// GLOBAL VARIABLES
std::random_device rd;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<> dis(1, 10000);
std::uniform_int_distribution<> dis2(1, 100000);

Enemy::Enemy(const Texture* texture, const Texture * textureShot) {
	
	sprite.setTexture(*texture);
	spriteShot.setTexture(*textureShot);

	spriteShot.setPosition(700, 700);		// Possible way to eliminate the zero-bullet 

	// center the origin of the sprites
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0f, sprite.getTexture()->getSize().y / 2.0f);
	spriteShot.setOrigin(spriteShot.getTexture()->getSize().x / 2.0f, spriteShot.getTexture()->getSize().y / 2.0f);

	// set startPosition. def = 0,0
	//this->_startPos = Vector2f( 0,0 );
	//setPosition(_startPos);

	_active = true;
	_dead = false;
	_shot = false;
	_collision = false;
	_won = false;

	enemy_side = _side::NONE;
	_score = 0;	// bounty variable (color)
}

Enemy::Enemy() {}

Enemy::~Enemy() { 
	delete new_enemy; 
}

Enemy::Enemy(const Enemy& enemy) {
	
	new_enemy = new Enemy;
	this->sprite = enemy.sprite;
	this->spriteShot = enemy.spriteShot;

	this->_active = true;
	this->_dead = false;
	this->_collision = false;
	this->_shot = false;
	this->_won = false;

	this->enemy_side = _side::NONE;
	this->_score = 0;		// bounty variable (color)
}

bool Enemy::isActive() { return _active; }
bool Enemy::isDead() { return _dead; }
bool Enemy::setDead() { return _dead = true; }
bool Enemy::hasWon() { return _won; }

// MOVEMENT
void Enemy::Move(RenderWindow * window, float deltaTime) {
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
		enemy_side = _side::LEFT;
		
	}
	else if (sprite.getPosition().x <= (sprite.getTexture()->getSize().x / 2.0f)) {
		
		_position.y += sprite.getTexture()->getSize().y;
		sprite.setPosition((sprite.getTexture()->getSize().x / 2.0f), _position.y);
		enemy_side = _side::RIGHT;
	}

	if (_active){
		if (enemy_side == _side::RIGHT || enemy_side == _side::NONE) {
			sprite.move( ( 100 / (1 / deltaTime)), 0);
		}
		else if (enemy_side == _side::LEFT) {
			sprite.move(-( 100 / (1 / deltaTime)), 0);
		}
		if (sprite.getPosition().y >= (window->getSize().y)) {
			_won = true;
			std::cout << "You lose" << std::endl;
			_active = false;
		}
	}
}

// shoot

void Enemy::shoot() {
	if (_shot == false && _active) {
		if (dis(gen) == 1) {
			spriteShot.setPosition(sprite.getPosition());
			_shot = true;
		}
	}
}

void Enemy::updateShot(float deltaTime) {	
	if (_shot == true) {
		spriteShot.move(0, +( 150 / (1 / deltaTime)));
		if (spriteShot.getPosition().y > 490) {
			_shot = false;
		}
	}
}


// BOUNTY
void Enemy::updateBounty(const char* type, Player* player, float deltaTime, RenderWindow * window) {
	if (type == "red") {
		colorPlayer = _color::RED;
		_score = 25;
	}
	else if (type == "orange") {
		colorPlayer = _color::ORANGE;
		_score = 50;
	}
	else if (type == "green") {
		colorPlayer = _color::GREEN;
		_score = 100;
	}
	else if (type == "blue") {
		colorPlayer = _color::BLUE;
		_score = 200;
	}
	else if (type == "pink") {
		colorPlayer = _color::PINK;
	}
	else if (type == "white") {
		colorPlayer = _color::WHITE;
	}

	// default sprite position
	this->sprite.setPosition(window->getSize().x / 15.0f,0);

	if (_active) {
		sprite.move((100 / (1 / deltaTime)), 0);
		if (sprite.getPosition().x >= window->getSize().x * 2.0f) {
			_active = false;
		}
	}


}

// Collision with Player

void Enemy::Collision(Player* player) {

	if (
	 // shot - enemy collision
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

	else if (
	// sprite - sprite collision (player - enemy)
		(player->sprite.getPosition().y >= (sprite.getPosition().y - sprite.getTexture()->getSize().y / 2.0f))
		&&
		(player->sprite.getPosition().y <= (sprite.getPosition().y + sprite.getTexture()->getSize().y / 2.0f))
		&&
		(player->sprite.getPosition().x >= (sprite.getPosition().x - sprite.getTexture()->getSize().x / 2.0f))
		&&
		(player->sprite.getPosition().x <= (sprite.getPosition().x + sprite.getTexture()->getSize().x / 2.0f))
		&&
		_active
		)
	{
		_collision = true;
		player->hitEnemy();		// sets private _shot = false; (reset)
		player->Hit();			// sets private _hit = true; 
		player->addToScore(this->_score);
		std::cout << "You have been hit. Your health is: " << player->getHealth() << std::endl;
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

void Enemy::hitPlayer() { _shot = false; }