#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Animation
{

public:
	Animation(Texture* texture, Vector2u imageCount, float switchTime);
	~Animation();

	IntRect uvRect; // instead of Sprite

	void Update(int row, float deltaTime);

private:
	Vector2u _imageCount;
	Vector2u _currentImage; 

	float _totalTime;
	float _switchTime;

	//Sprite _sprite;

};


#endif
