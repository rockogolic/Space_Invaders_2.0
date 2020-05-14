#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace sf;

class Enemy {

public:

	Enemy(Texture* texture);
	Enemy(const Enemy& enemy);
	~Enemy();

	bool isActive();
	bool isDead();

	// functions, movement
	void Update();
	void setStartPosition( Vector2f startPos );

	Sprite sprite;


private:
	Vector2f _position;

	Vector2f _startPos;

	bool _active;
	bool _dead;



};


#endif
