#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"

using namespace sf;

class Enemy {

public:

	Enemy(const Texture* texture, const Texture * textureShot);
	Enemy();						
	Enemy(const Enemy& enemy);		
	~Enemy();

	bool isActive();
	bool hasWon();

	void Move(RenderWindow * window, float deltaTime);

	void shoot();
	void updateShot(float deltaTime);
	void updateBounty(RenderWindow * window, float deltaTime);

	void setBounty(const char* type, RenderWindow * window);
	void setStartPosition( Vector2f startPos );
	void setPosition( Vector2f position );

	void setWin();
	void setInactive();

	void Collision(Player* player);
	void hitPlayer();

	Sprite sprite;
	Sprite spriteShot;

	enum class _color { RED, ORANGE, GREEN, BLUE, PINK, WHITE };
	_color colorPlayer;

	enum class _side { LEFT, RIGHT, NONE };
	_side enemy_side;

private:

	Vector2f _position;
	Vector2f _startPos;

	bool _active;
	bool _dead;
	bool _won;
	bool _collision;
	bool _shot;

	float _speed;
	unsigned int _score;

	Enemy * new_enemy;
};


#endif
