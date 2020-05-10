#include "pch.h"
#include "Message.h"

// Set the color and font to display the message:
// through message.color(), and message.font();

// ERROR:Color& color etc. already has a body (SOLVE IT!)


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

Message::~Message() {}

void Message::font(Font& font) { _font = font; }
void Message::color(Color color) { _color = color; }
void Message::position(float x, float y) { _text.setPosition(x, y); }
void Message::display(RenderWindow& window) { window.draw(_text); }

Text Message::get() {
	Text text;
	text = _text;
	return text;
}
