#include "pch.h"
#include "CreateEnemy.h"

CreateEnemy::CreateEnemy(Vector2i number, Enemy& enemy, RenderWindow& window) : _dim(number) {
	if ( (_dim.x > 6 || _dim.x < 0) && (_dim.y > 6 || _dim.y < 0) ) {
		_dim.x = abs(number.x) % 6; 
		_dim.y = abs(number.y) % 6;
	}

	// size of the screen given to enemies to spawn
	_playground.x = static_cast<float>(window.getSize().x);
	_playground.y = static_cast<float>(window.getSize().y - 200);

	for (int i = 0; i < _dim.x; i++) {
		for (int j = 0; j < _dim.y; j++) {
			Enemy new_enemy(enemy);
			//new_enemy.sprite.setPosition( (70.0f + (_playground.x - 70.0f) * i/(_dim.x-1)), _playground.y / _dim.y * (j+1));
			new_enemy.sprite.setPosition((_playground.x / (_dim.x + 1) * (i+1)), (_playground.y / (_dim.y + 1) * (j + 1)));
			new_enemy.enemy_side = Enemy::_side::NONE;
			Enemies.push_back(new_enemy);
		}
	}
}

CreateEnemy::CreateEnemy() {
		

}

void CreateEnemy::assignEnemy(const CreateEnemy& enemyMatrix ) {

	for (unsigned int i = 0; i < size(enemyMatrix.Enemies); i++) {
		this->Enemies.push_back(enemyMatrix.Enemies[i]);
	}
}

void CreateEnemy::clear() {
	this->Enemies.clear();
}

CreateEnemy::~CreateEnemy() { }

void CreateEnemy::getActive() {
	activeEnemies.clear();		// clear the vector from entries before executing
	for (unsigned int i = 0; i < size(Enemies); i++) {
		if (Enemies[i].isActive()) {
			activeEnemies.push_back(Enemies[i]);
		}
	}

}

void CreateEnemy::MoveClassic(RenderWindow* window, float deltaTime) {

	for (unsigned int i = 0; i < size(Enemies); i++) {
		if ( (Enemies[i].sprite.getPosition().x >= (window->getSize().x - Enemies[i].sprite.getTexture()->getSize().x / 2.0f)) 
			||
			 (Enemies[i].sprite.getPosition().x <= (Enemies[i].sprite.getTexture()->getSize().x / 2.0f)) ) {
			changeY = true;
			break;
		}
	}

	for (unsigned int i = 0; i < size(Enemies); i++) {
		if (Enemies[i].sprite.getPosition().x >= (window->getSize().x - Enemies[i].sprite.getTexture()->getSize().x / 2.0f)) {
			for (unsigned int j = 0; j < size(Enemies); j++) {
				Enemies[j].enemy_side = Enemy::_side::LEFT;
			}
		}
		else if (Enemies[i].sprite.getPosition().x <= (Enemies[i].sprite.getTexture()->getSize().x / 2.0f)) {
			for (unsigned int j = 0; j < size(Enemies); j++) {
				Enemies[j].enemy_side = Enemy::_side::RIGHT;
			}
		}
	}

	if (changeY == true) {
		for (unsigned int i = 0; i < size(Enemies); i++) {
			Enemies[i].sprite.setPosition(Enemies[i].sprite.getPosition().x, Enemies[i].sprite.getPosition().y + Enemies[i].sprite.getTexture()->getSize().y);
			changeY = false;
		}
	}

	for (unsigned int i = 0; i < size(Enemies); i++) {
		if (Enemies[i].isActive()) {
			if (Enemies[i].enemy_side == Enemy::_side::RIGHT || Enemies[i].enemy_side == Enemy::_side::NONE) {
				Enemies[i].sprite.move(40 * deltaTime, 0.0f);
			}
			else if (Enemies[i].enemy_side == Enemy::_side::LEFT) {
				Enemies[i].sprite.move(-40 * deltaTime, 0.0f);
			}
			else if (Enemies[i].sprite.getPosition().y >= window->getSize().y) {
				Enemies[i].setWin();
			}
		}

	}
}

//CreateEnemy::CreateEnemy(Boss& boss) {}





