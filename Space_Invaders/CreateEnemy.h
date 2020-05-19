#ifndef CREATEENEMY_H
#define CREATEENEMY_H


#include "Enemy.h"
#include <vector>

class CreateEnemy
{
public:
	CreateEnemy(Vector2i number, Enemy& enemy, RenderWindow& window);
	//CreateEnemy(Boss& boss);
	CreateEnemy();
	~CreateEnemy();

	void getActive();
	void assignEnemy(const CreateEnemy& enemyMatrix);

	void MoveClassic(RenderWindow * window, float deltaTime);

	void clear();

	std::vector<Enemy> Enemies;
	std::vector<Enemy> activeEnemies;

	

private:
	Vector2i _dim;
	Vector2f _playground;	// size of the screen given to enemies to spawn

	Vector2f _position;

	enum class _side { LEFT, RIGHT, NONE };
	_side side;
};

#endif

