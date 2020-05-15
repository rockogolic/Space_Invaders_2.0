#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace sf;

class Enemy {

public:

	Enemy(const Texture* texture);	// constructor
	Enemy();						// default
	Enemy(const Enemy& enemy);		// copy constr
	~Enemy();

	bool isActive();
	bool isDead();

	// functions, movement
	void Update();
	void setStartPosition( Vector2f startPos );
	void setPosition( Vector2f position );

	Sprite sprite;

private:

	Vector2f _position;
	Vector2f _startPos;

	bool _active;
	bool _dead;

	Enemy * new_enemy;
};


#endif
