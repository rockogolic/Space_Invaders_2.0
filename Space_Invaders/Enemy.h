#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"

#include <math.h>	// for sin/cos calculations
constexpr auto PI = 3.14159265;

using namespace sf;

class Enemy {

public:

	Enemy(const Texture* texture, const Texture * textureShot, int health);
	Enemy(const Texture* texture, const Texture * textureShot, const char* type);			// bounty constructor
	Enemy();						
	Enemy(const Enemy& enemy);		
	~Enemy();

	bool isActive();
	bool hasWon();
	bool isAllowed();	// bounty
	bool isHit();		// collision (CreateEnemy)

	void Move(RenderWindow * window, float deltaTime);

	unsigned int getHealth();

	void shoot();
	void updateShot(RenderWindow * window, float deltaTime);

	void shootGrunt(int number_of_shots);
	void updateShotGrunt(RenderWindow * window, float deltaTime);

	void updateBounty(RenderWindow * window, float deltaTime);

	void setBounty(const char* , RenderWindow * window);
	void setStartPosition( Vector2f startPos );
	void setPosition( Vector2f position );

	void setHealth(unsigned int health);
	void setWin();
	void setInactive();
	void setBountyAllowed(RenderWindow * window);	// bounty

	void Collision(Player* player);
	void hitPlayer();
	void Hit();

	Sprite sprite;
	Sprite spriteShot;

	enum class _color { RED, ORANGE, GREEN, BLUE, PINK, WHITE, NONE };
	_color colorPlayer;

	enum class _side { LEFT, RIGHT, NONE };
	_side enemy_side;

	unsigned int _health;

	std::vector<Sprite> shotsGrunt;
	std::vector<bool> shot_Grunt_isActive;

private:


	Vector2f _position;
	Vector2f _startPos;

	bool _active;
	bool _dead;
	bool _won;
	bool _collision;
	bool _shot;
	bool _allowed; // for bounty

	unsigned int _score;

	Enemy * new_enemy;
};


#endif
