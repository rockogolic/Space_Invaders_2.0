#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
//#include "enemy.h"

using namespace sf;

class Enemy;					// forward declaration

class Player {

public:
	Player(const Texture* texturePlayer, const Texture* textureShot);
	~Player();

	void shoot();
	void updateShot();

	const int getHealth() const;

	void hitEnemy();
	void isHit();

	void Collision(Enemy * enemy);

	Sprite sprite;
	Sprite spriteShot;

private:

	Vector2f _position;
	static Vector2f _startPos;	// static -> same for all objects!

	bool _collision;
	bool _dead;
	bool _shot;
	bool _hit;

	unsigned int _health;


};


#endif