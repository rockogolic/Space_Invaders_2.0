#include "pch.h"
#include "CreateEnemy.h"

CreateEnemy::CreateEnemy(Vector2i number, Enemy& enemy, RenderWindow& window) : _dim(number) {
	if ( (_dim.x > 6 || _dim.x < 0) && (_dim.y > 6 || _dim.y < 0) ) {
		_dim.x = abs(number.x) % 6; 
		_dim.y = abs(number.y) % 6;
	}

	// will error by _dim.x or _dix.y =1.
	// Make an if statement to set dx to a new value in that case -> screen.x / 2 

	//_playground.x = window.getSize().x - 70.0f;
	//_playground.y = window.getSize().y - 200.0f;
	_playground.x = static_cast<float>(window.getSize().x);
	_playground.y = static_cast<float>(window.getSize().y - 200);

	for (int i = 0; i < _dim.x; i++) {
		for (int j = 0; j < _dim.y; j++) {
			Enemy new_enemy(enemy);
			//new_enemy.sprite.setPosition( (70.0f + (_playground.x - 70.0f) * i/(_dim.x-1)), _playground.y / _dim.y * (j+1));
			new_enemy.sprite.setPosition((_playground.x / (_dim.x + 1) * (i+1)), (_playground.y / (_dim.y + 1) * (j + 1)));
			Enemies.push_back(new_enemy);
		}
	}
}

CreateEnemy::~CreateEnemy() { }

//CreateEnemy::CreateEnemy(Boss& boss) {}





