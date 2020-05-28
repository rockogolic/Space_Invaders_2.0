#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy;					// forward declaration

class Player {

public:
	Player(const Texture* texturePlayer, const Texture* textureShot, const Texture * textureWinner, RenderWindow * window);
	~Player();

	void shoot();
	void updateShot(float deltaTime);
	void byebyeWinner(float deltaTime);

	const int getHealth() const;
	const int getScore() const;

	void setWinner();
	void setAlive();
	void setPosition(Vector2f position);
	void resetPosition();	// resets the position to startPosition
	void addHealth();
	void addToScore(int value);

	void hitEnemy();
	void hitBounty(int value);
	void Hit();
	
	bool isHit();
	bool isDead();
	bool isWinner();
	bool hasShot();

	void Collision(Enemy * enemy);

	Sprite sprite;
	Sprite spriteShot;
	Sprite spriteWinner;

private:

	Vector2f _position;
	Vector2f _startPos;	// if static -> same for all objects!

	bool _collision = false;
	bool _dead = false;
	bool _shot = false;
	bool _hit = false;
	bool _lost = false;
	bool _won = false;

	unsigned int _score;
	unsigned int _health;
};


#endif