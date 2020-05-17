#ifndef CREATEENEMY.H
#define CREATEENEMY.H


#include "Enemy.h"
#include <list>
#include <iterator>

class CreateEnemy :
	public Enemy
{
public:
	CreateEnemy( Enemy& enemy );
	~CreateEnemy();

	// accessors / modifiers

	// functions

private:
	const int _number;

};

#endif

