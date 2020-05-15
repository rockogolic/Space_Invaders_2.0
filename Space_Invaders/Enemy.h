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
	void Move(RenderWindow * window);
	void setStartPosition( Vector2f startPos );
	void setPosition( Vector2f position );
	bool setDead();

	Sprite sprite;

private:

	enum class _side { LEFT, RIGHT, NONE };
	_side enemy_side;

	Vector2f _position;
	Vector2f _startPos = { 0.0f,0.0f };

	bool _active;
	bool _dead;
	bool _won;

	Enemy * new_enemy;
};


#endif
