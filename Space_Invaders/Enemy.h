#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy {

public:

	Enemy(Texture& texture);
	~Enemy();
	
	// accessors / modifiers

	Sprite sprite();
	void centerOrigin();


private:
	Vector2f _position;
	Sprite _sprite;



};


#endif
