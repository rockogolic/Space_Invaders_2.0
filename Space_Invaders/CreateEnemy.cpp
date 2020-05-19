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


	// size of the screen given to enemies to spawn
	_playground.x = static_cast<float>(window.getSize().x);
	_playground.y = static_cast<float>(window.getSize().y - 200);

	for (int i = 0; i < _dim.x; i++) {
		for (int j = 0; j < _dim.y; j++) {
			Enemy new_enemy(enemy);
			//new_enemy.sprite.setPosition( (70.0f + (_playground.x - 70.0f) * i/(_dim.x-1)), _playground.y / _dim.y * (j+1));
			new_enemy.sprite.setPosition((_playground.x / (_dim.x + 1) * (i+1)), (_playground.y / (_dim.y + 1) * (j + 1)));
			Enemies.push_back(new_enemy);
			side = _side::NONE;
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

/*

void CreateEnemy::MoveClassic(RenderWindow * window, float deltaTime) {
	for (unsigned int i = 0; i < size(Enemies); i++) {
		if (Enemies[i].enemy_side == Enemy::_side::LEFT) {
			Enemies[i].sprite.setPosition(Enemies[i].sprite.getPosition().x, Enemies[i].sprite.getPosition().y + 2*Enemies[i].sprite.getTexture()->getSize().y);
		}
		else if (Enemies[i].enemy_side == Enemy::_side::RIGHT) {
			Enemies[i].sprite.setPosition(Enemies[i].sprite.getPosition().x, Enemies[i].sprite.getPosition().y + 2 * Enemies[i].sprite.getTexture()->getSize().y);
		}
	}
}

*/

//*
void CreateEnemy::MoveClassic(RenderWindow * window, float deltaTime) {
	for (unsigned int i = 0; i < size(Enemies); i++) {
		Vector2f position = Enemies[i].sprite.getPosition();	// update vector2f _position with the latest position

		if (Enemies[i].sprite.getPosition().x >= (window->getSize().x - Enemies[i].sprite.getTexture()->getSize().x / 2.0f)) {

			position.y += Enemies[i].sprite.getTexture()->getSize().y;
			Enemies[i].sprite.setPosition((window->getSize().x - Enemies[i].sprite.getTexture()->getSize().x / 2.0f), position.y);
			side = _side::LEFT;

		}
		else if (Enemies[i].sprite.getPosition().x <= (Enemies[i].sprite.getTexture()->getSize().x / 2.0f)) {

			position.y += Enemies[i].sprite.getTexture()->getSize().y;
			Enemies[i].sprite.setPosition((Enemies[i].sprite.getTexture()->getSize().x / 2.0f), position.y);
			side = _side::RIGHT;
		}

		if (Enemies[i].isActive()) {
			if (side == _side::RIGHT || side == _side::NONE) {
				Enemies[i].sprite.move(100 * deltaTime , 0);
			}
			else if (side == _side::LEFT) {
				Enemies[i].sprite.move(-100 * deltaTime, 0);
			}
			if (Enemies[i].sprite.getPosition().y >= (window->getSize().y)) {
				Enemies[i].setWin();
				Enemies[i].setInactive();
			}
		}
	}
}
//*/


//CreateEnemy::CreateEnemy(Boss& boss) {}





