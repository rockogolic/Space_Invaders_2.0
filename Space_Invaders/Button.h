#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Message.h"

using namespace sf;

class Button
	: public Message
{

public:
	
	Button(Texture * texture1, Texture * texture2); // number of buttons to be made
	~Button();

	void Position(Vector2f position);
	
	void setMessage(Message * message);		// number -> index of button (from 1 to number)
	void setOn();
	void setOff();

	bool isOn();
	bool isOff();
	
	bool Click();

	void updateUp();
	void updateDown();

	Sprite spriteButtonOn, spriteButtonOff;
	Text text;

private:
	Vector2f _position;
	bool _click;

	bool _on;
	bool _off;

	static int _whereAt;
	Text _text;

	std::vector<Button> Buttons;

};

#endif
