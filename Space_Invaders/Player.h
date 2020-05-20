#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy;					// forward declaration

class Player {

public:
	Player(const Texture* texturePlayer, const Texture* textureShot);
	~Player();

	void shoot();
	void updateShot(float deltaTime);

	const int getHealth() const;
	const int getScore() const;

	void setAlive();
	void addHealth();
	void addToScore(int value);

	void hitEnemy();
	void hitBounty(int value);
	void Hit();
	
	bool isHit();
	bool isDead();

	void Collision(Enemy * enemy);

	Sprite sprite;
	Sprite spriteShot;

private:

	Vector2f _position;
	static Vector2f _startPos;	// static -> same for all objects!

	bool _collision = false;
	bool _dead = false;
	bool _shot = false;
	bool _hit = false;
	bool _lost = false;

	unsigned int _score;
	unsigned int _health;
};


#endif