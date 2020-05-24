#include "pch.h"
#include "Message.h"
#include "Player.h"

Message::Message(std::string string, Color color, Font& font, int size) : _message(string), _font(font), _color(color), _size(size) {
	_text.setFont(font);

	_text.setString(_message);
	_text.setCharacterSize(_size);
	_text.setFillColor(color);

	// Reposition the origin of the text
	FloatRect textRect;
	textRect = _text.getLocalBounds();
	_text.setOrigin(
		textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f
	);
}

Message::Message() {}
Message::~Message() {}

void Message::font(Font& font) { _font = font; }
void Message::color(Color color) { _color = color; }
void Message::position(float x, float y) { _text.setPosition(x, y); }
void Message::display(RenderWindow& window) { window.draw(_text); }

void Message::updateMessageHealth(const Player* player) {
	int health = (player->getHealth());
	_text.setString(_message + std::to_string(player->getHealth()));
}

void Message::updateMessageScore(const Player* player) {
	int score = (player->getScore());
	_text.setString(_message + std::to_string(player->getScore()));
}

Text Message::getText() {
	Text text;
	text = _text;
	return text;
}

std::string Message::getString() {
	return _message;
}
