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
	bool hasWon();

	// functions, movement
	void Move(RenderWindow * window, float deltaTime);

	void shoot();
	void updateShot(float deltaTime);
	void updateBounty(const char* type, Player* player, float deltaTime, RenderWindow * window);

	void setStartPosition( Vector2f startPos );
	void setPosition( Vector2f position );

	void Collision(Player* player);
	void hitPlayer();

	bool setDead();

	Sprite sprite;
	Sprite spriteShot;

	enum class _color { RED, ORANGE, GREEN, BLUE, PINK, WHITE };
	_color colorPlayer;

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

	unsigned int _score;

	Enemy * new_enemy;
};


#endif
