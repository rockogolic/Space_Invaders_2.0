#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"

using namespace sf;

//class Player;						// forward declaration

class Enemy {

public:

	Enemy(const Texture* texture, const Texture * textureShot);	// constructor
	Enemy();						// default
	Enemy(const Enemy& enemy);		// copy constr
	~Enemy();

	bool isActive();
	bool isDead();

	// functions, movement
	void Move(RenderWindow * window);

	void shoot();
	void updateShot();

	void setStartPosition( Vector2f startPos );
	void setPosition( Vector2f position );

	void Collision(Player* player);
	void hitPlayer();

	bool setDead();

	Sprite sprite;
	Sprite spriteShot;

private:

	enum class _side { LEFT, RIGHT, NONE };
	_side enemy_side;

	Vector2f _position;
	Vector2f _startPos;

	bool _active;
	bool _dead;
	bool _won;
	bool _collision;
	bool _shot;

	Enemy * new_enemy;

	//std::uniform_int_distribution<> _dis;
};


#endif
