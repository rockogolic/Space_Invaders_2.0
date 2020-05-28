#include "pch.h"
#include "Enemy.h"

// GLOBAL VARIABLES
std::random_device rd;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<> dis(1, 10000);
std::uniform_int_distribution<> dis2(1, 70000);

Enemy::Enemy(const Texture* texture, const Texture * textureShot,int health) 
{
	
	sprite.setTexture(*texture);
	spriteShot.setTexture(*textureShot);

	spriteShot.setPosition(700, 700);		// Possible way to eliminate the zero-bullet 

	// center the origin of the sprites
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0f, sprite.getTexture()->getSize().y / 2.0f);
	spriteShot.setOrigin(spriteShot.getTexture()->getSize().x / 2.0f, spriteShot.getTexture()->getSize().y / 2.0f);

	_active = true;
	_dead = false;
	_shot = false;
	_collision = false;
	_won = false;
	_allowed = false;	// for bounty

	enemy_side = _side::NONE;
	colorPlayer = _color::NONE;
	_score = 0;	// bounty variable (color)
	_health = health;
}

//*	
Enemy::Enemy(const Texture* texture, const Texture * textureShot, const char* type) {

	sprite.setTexture(*texture);
	spriteShot.setTexture(*textureShot);

	spriteShot.setPosition(700, 700);		// Possible way to eliminate the zero-bullet 

	// center the origin of the sprites
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0f, sprite.getTexture()->getSize().y / 2.0f);
	spriteShot.setOrigin(spriteShot.getTexture()->getSize().x / 2.0f, spriteShot.getTexture()->getSize().y / 2.0f);

	_active = true;
	_dead = false;
	_shot = false;
	_collision = false;
	_won = false;
	_allowed = false;	// for bounty

	enemy_side = _side::NONE;
	_score = 0;	// bounty variable (color)

	if (type == "red") {
		colorPlayer = _color::RED;
		_score = 15;
	}
	else if (type == "orange") {
		colorPlayer = _color::ORANGE;
		_score = 40;
	}
	else if (type == "green") {
		colorPlayer = _color::GREEN;
		_score = 90;
	}
	else if (type == "blue") {
		colorPlayer = _color::BLUE;
		_score = 190;
	}
	else if (type == "pink") {
		colorPlayer = _color::PINK;
		// adds health and 10 score
	}
	else if (type == "white") {
		colorPlayer = _color::WHITE;
		// adds shield and 10 score
	}
	else {
		colorPlayer = _color::NONE;
	}
}
//*/ 
// BOUNTY CONSTRUCTOR 

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
	this->_allowed = false;


	this->enemy_side = _side::NONE;
	this->colorPlayer = _color::NONE;
	this->_score = 0;		// bounty variable (color)
	this->_health = _health;

}

bool Enemy::isActive() { return _active; }
bool Enemy::hasWon() { return _won; }

// MOVEMENT

void Enemy::Move(RenderWindow * window, float deltaTime) {

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
			sprite.move((100 / (1 / deltaTime)), 0);
		}
		else if (enemy_side == _side::LEFT) {
			sprite.move(-(100 / (1 / deltaTime)), 0);
		}
		if (sprite.getPosition().y >= (window->getSize().y)) {
			_won = true;
			std::cout << "You lose" << std::endl;
			_active = false;
		}
	}
}

unsigned int Enemy::getHealth()
{
	return _health;
}
void Enemy::setHealth(unsigned int health) { _health = health; }

void Enemy::setWin() {_won = true;}
void Enemy::setInactive() { _active = false; }

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

void Enemy::setBounty(const char* type, RenderWindow * window) {

	if (type == "red") {
		colorPlayer = _color::RED;
		_score = 15;
	}
	else if (type == "orange") {
		colorPlayer = _color::ORANGE;
		_score = 40;
	}
	else if (type == "green") {
		colorPlayer = _color::GREEN;
		_score = 90;
	}
	else if (type == "blue") {
		colorPlayer = _color::BLUE;
		_score = 190;
	}
	else if (type == "pink") {
		colorPlayer = _color::PINK;
		// adds health and 10 score
	}
	else if (type == "white") {
		colorPlayer = _color::WHITE;
		// adds shield and 10 score
	}
	else {
		colorPlayer = _color::NONE;
	}
	
	// default pos
	this->sprite.setPosition(-0.5f * window->getSize().x, window->getSize().y / 15.0f);
}


void Enemy::setBountyAllowed(RenderWindow * window) {
	
	if (dis2(gen) == 1) {
		_allowed = true;
		_active = true;
		_collision = false;
	}
}


void Enemy::updateBounty(RenderWindow * window, float deltaTime) {
	if (_allowed) {
		sprite.move((100 * deltaTime), 0);
		if (_collision) {
			this->sprite.setPosition(-0.5f * window->getSize().x, window->getSize().y / 15.0f);
			_allowed = false;
		}
		else if (sprite.getPosition().x >= window->getSize().x * 2.0f) {
			_allowed = false;
			_active = false;

		}
	}


}

bool Enemy::isAllowed() { return _allowed; }
bool Enemy::isHit() { return _collision; }

void Enemy::Hit() {
	--_health;
	if (_health == 0) {
		_active = false;
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
		if (colorPlayer == _color::PINK) {
			player->addHealth();
		}
		player->addToScore(_score);

		std::cout << "You hit the alien" << std::endl;
		//this->Hit();		// replaces (_active = false) in case of variable health
		//_active = false;

		if (_active) {
			--_health;
			if (_health == 0) {
				_active = false;
			}
		}
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

		// for fun : remove pause for the pink cat
		_collision = true;
		player->hitEnemy();		// sets private _shot = false; (reset)
		 
		player->addToScore(this->_score);
		if (colorPlayer == _color::PINK) {
			player->addHealth();
		}
		else {	// EXCLUSIONS to HIT screen (if something can be "swallowed" or "picked"
			player->Hit();			// sets private _hit = true;
		}
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