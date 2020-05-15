#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "enemy.h"

using namespace sf;

class Player {

public:
	Player(const Texture* texturePlayer, const Texture* textureShot);
	~Player();

	void shoot();


	Sprite sprite;
	Sprite spriteShot;

private:

	Vector2f _position;
	static Vector2f _startPos;	// static -> same for all objects!

	bool _collision;
	bool _dead;
	bool _shot;

	unsigned int _health;


};


#endif