#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;

class Player;

class Message {
public:
	Message(std::string string, Color color, Font& font, int size);
	// make default constructor
	~Message();

	// accessors, modifiers

	void font(Font& font);			// set font
	void color(Color color);		// set fill-color
	void position(float x, float y);	// set position on the screen

	void updateMessage(const Player* player);

	// access the finalized text object of the class
	Text get();

	// functions

	void display(RenderWindow& window);

private:
	std::string _message;
	Font _font;
	Color _color;
	int _size;
	Vector2f _position;
	Text _text;
};

#endif
