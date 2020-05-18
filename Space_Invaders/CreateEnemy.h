#ifndef CREATEENEMY_H
#define CREATEENEMY_H


#include "Enemy.h"
#include <vector>

class CreateEnemy :
	public Enemy
{
public:
	CreateEnemy(Vector2i number, Enemy& enemy, RenderWindow& window);
	//CreateEnemy(Boss& boss);
	~CreateEnemy();

	std::vector<Enemy> Enemies;

private:
	Vector2i _dim;
	Vector2f _playground;

};

#endif

