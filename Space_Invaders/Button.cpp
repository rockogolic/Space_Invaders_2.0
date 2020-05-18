#include "pch.h"
#include "Button.h"

Button::Button(Texture * texture1, Texture * texture2) { // First - button Off, second - Button On
	spriteButtonOff.setTexture(*texture1);
	spriteButtonOn.setTexture(*texture2);

	// center
	spriteButtonOff.setOrigin( spriteButtonOff.getTexture()->getSize().x / 2.0f , spriteButtonOff.getTexture()->getSize().y / 2.0f );
	spriteButtonOn.setOrigin( spriteButtonOff.getTexture()->getSize().x / 2.0f, spriteButtonOff.getTexture()->getSize().y / 2.0f );

	// def position
	_position = Vector2f(0.0f, 0.0f);
	spriteButtonOff.setPosition(_position);
	spriteButtonOn.setPosition(_position);

	_on = false;
	_off = true;
}

Button::~Button() {}

void Button::Position(Vector2f position) {
	_position = position;
	spriteButtonOff.setPosition(position);
	spriteButtonOn.setPosition(position);
}

void Button::setMessage(Message * message) {
	message->position(this->_position.x, this->_position.y);
	this->text = message->get();
	this->text.setPosition(this->_position.x, this->_position.y);
}

void Button::setOn() {
	_on = true;
	_off = false;
}

void Button::setOff() {
	_on = false;
	_off = true;
}

bool Button::isOn() { return _on; }
bool Button::isOff() { return _off; }




