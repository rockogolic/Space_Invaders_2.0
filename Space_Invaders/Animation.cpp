#include "pch.h"
#include "Animation.h"
#include <iostream>

Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime) {
	this->_imageCount = imageCount;
	this->_switchTime = switchTime;
	this->_totalTime = 0.0f;
	this->_currentImage.x = 0;			// for horizontal spriteSheet layout. 0 is always first, just choose row

	uvRect.width = texture->getSize().x / (_imageCount.x);
	uvRect.height = texture->getSize().y / (_imageCount.y);

} 

Animation::~Animation() {}

void Animation::Update(int row, float deltaTime) {

	_currentImage.y = row;
	_totalTime += deltaTime;
	
	if (_totalTime >= _switchTime) {

		_totalTime -= _switchTime;
		_currentImage.x++;
		if (_currentImage.x >= _imageCount.x)
			_currentImage.x = 0; // resets the image
	}

	// Offset between frames! and why??
	uvRect.left = _currentImage.x * uvRect.width;
	uvRect.top = _currentImage.y * uvRect.height;
}

