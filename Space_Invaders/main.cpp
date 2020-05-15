// HelloSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/* NOTE to self:
1) break; in switch -> redundant
2) If we have a Vector2i (call it, vector) and we need Vector2f for a function -> we can cast integer to floats:
there are two ways to do that:
2.1) :C-STYLE CAST: unsafe and short -> (float)vector.x and (float)vector.y
2.2) :STATIC CAST: safe and long (safe for casting one class to another (?) ) -> static_cast<float>(vector.x) and (or, if only one), static_cast<float>(vector.y)

*/

#include <SFML/Graphics.hpp>
#include "pch.h"
#include "Message.h"
#include "Animation.h"
#include "setSprite.h"
#include "Enemy.h"
#include "Player.h"
#include <iostream>

using namespace sf;

const Vector2f spriteSize(Sprite& sprite);		//  gets the Vector2f in size of the sprite
void Center(Sprite& sprite);					// changes the origin of the sprite to its center

// Enemy's movement
enum class enemy_side { LEFT, RIGHT, NONE };
enemy_side enemy_pos;

int main()
{
	// to allow to resize the window -> Style::default and remove other Style::Close && Style::Titlebar
	RenderWindow window(VideoMode(640, 480), "Space Invaders", Style::Default);
	Vector2f screenSize(window.getSize().x, window.getSize().y);		// Vector2f of size of the RenderWindow object, window

	/* LOAD and INITIALIZE sounds, sprites and fonts */

	Font font_MKPixelProject;
	font_MKPixelProject.loadFromFile("fonts/MKPixelProject.ttf");

	Font font_CubicCoreMono;
	font_CubicCoreMono.loadFromFile("fonts/CubicCoreMono.ttf");

	// SPRITE INTRO
	Texture textureIntro;
	textureIntro.loadFromFile("graphics/space_640x480.png");
	Sprite spriteIntro;
	spriteIntro.setTexture(textureIntro);
	
	// SPRITE BACKGROUND
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/game_640x480.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);

	// SPRITE MENU
	Texture textureMenu;
	textureMenu.loadFromFile("graphics/menu_500x375.png");
	Sprite spriteMenu;
	spriteMenu.setTexture(textureMenu);
	Center(spriteMenu);
	spriteMenu.setPosition(screenSize.x / 2.0f, screenSize.y / 2.0f);

	// PLAYER
	Texture texturePlayer_idle;			// IDLE 
	texturePlayer_idle.loadFromFile("graphics/player_54x54.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer_idle);
	Center(spritePlayer);
	spritePlayer.setPosition(screenSize.x / 2.0f, screenSize.y - 26);				

	Texture texturePlayer_left;			// LEFT-Facing
	texturePlayer_left.loadFromFile("graphics/player_left_54x54.png");
	Sprite spritePlayer_left;
	spritePlayer_left.setTexture(texturePlayer_left);
	Center(spritePlayer_left);

	Texture texturePlayer_right;		// RIGHT-Facing
	texturePlayer_right.loadFromFile("graphics/player_right_54x54.png");
	Sprite spritePlayer_right;
	spritePlayer_right.setTexture(texturePlayer_right);
	Center(spritePlayer_right);

	// SHOT
	Texture textureShot;
	textureShot.loadFromFile("graphics/shot_13x6.png");
	Sprite spriteShot;
	spriteShot.setTexture(textureShot);
	Center(spriteShot);
	
	// ENEMY
	Texture textureEnemy;
	textureEnemy.loadFromFile("graphics/enemy_red_54x54.png");
	Sprite spriteEnemy;
	spriteEnemy.setTexture(textureEnemy);
	Center(spriteEnemy);

	Texture texturePawn;
	texturePawn.loadFromFile("graphics/pawn.png");

	Sprite spritePawn;
	spritePawn.setTexture(texturePawn);
	spritePawn.setPosition(screenSize.x/2.0f , screenSize.y/2.0f);

	Animation animationPawn(&texturePawn, Vector2u(3,1), 0.3f);

	/* NEW SPRITES CLASSES */

	Enemy enemy(&textureEnemy);
	Enemy enemy2(enemy);
	Enemy enemy3(enemy2);
	
	enemy2.setPosition(Vector2f(100.0f, 100.0f));
	enemy3.setPosition(Vector2f(400.0f, 400.0f));


	Texture textureKaboom;
	textureKaboom.loadFromFile("graphics/kaboom.png");
	Sprite spriteKaboom;
	spriteKaboom.setTexture(textureKaboom);
	Center(spriteKaboom);


	/* CREATION of MESSAGES for the game */
	Message messageTitle(
		"S p a c e      I n v a d e r s",
		Color::White, font_MKPixelProject, 50
	);
	messageTitle.position(screenSize.x / 2.0f, screenSize.y / 2.0f);

	Message messageEnter(
		"Press ENTER to start..",
		Color::White, font_CubicCoreMono, 40
	);
	messageEnter.position(screenSize.x / 2.0f, screenSize.y / 1.5f);

	Message messageMenu_1(
		"Main menu",
		Color::White, font_CubicCoreMono, 20
	);

	/* BOOLEANS to control phases of the GAME */

	bool intro = true; // introduction screen; def -> true;
	bool menu = false; // menu screen in the game; if !intro -> def->false; 

	bool fired = false; // state of a fired missile; if !intro && !menu; def->false;
	bool enemy_active = false; // state of the enemy's ship
	bool enemy_boom = false;
	bool collision = false;	// did the collision happen? default -> false

	bool round1_over = false;
	bool round2_over = false;
	bool round3_over = false;
	bool boss_over = false;

	// TIME creation
	float deltaTime = 0.0f;
	Clock clock;

	/*
	++++++++++++++
	MAIN game loop
	++++++++++++++
	*/

	
	while (window.isOpen()) {

		deltaTime = clock.restart().asSeconds();

		/* One time button press trigger -> Menu, Escape, Shoot, Enter etc...*/

		Event evnt;

		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case Event::Closed:
				window.close();
				break;
			case Event::Resized:
				printf("New window width: %i New window height: %i \n", evnt.size.width, evnt.size.height);		// same as std::cout would be
				break;
			case Event::TextEntered:
				// checks if the text is ASCII (excl. cntr,alt...  (so on) keys)
				if (evnt.text.unicode < 128) {
					printf("%c", evnt.text.unicode);
				}
				break;
			case Event::KeyPressed:
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					if (intro) {
						window.close();
					}
					else if (!intro && !menu) {
						//printf("\n A Menu is open! \n");
						std::cout << "\n A Menu is open!" << std::endl;
						menu = true;
					}
					else if (!intro && menu) {
						//printf("\n A Menu is closed! \n");
						std::cout << "\n A Menu is closed!" << std::endl;
						menu = false;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Return)) {
					if (intro) {
						intro = false;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					if (!intro && !menu) {
						if (!fired) {
							Vector2f positionShot = spritePlayer.getPosition();
							spriteShot.setPosition(positionShot);
							fired = true;
						}
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					if (menu) {

					}
				}

				// More buttons
				
				// bullet: reset if out of screen, OR if collided -> then you can fire again
			}
		}

		/* Long-run commands -> Player movement and Game-related mechanics */
		// a.k.a. UPDATE THE SCENE
		
		// Player's movement
		if (!intro && !menu) {
			if (Keyboard::isKeyPressed(Keyboard::A) && spritePlayer.getPosition().x > 26)
				spritePlayer.move(-0.1f, 0.0f);
			if (Keyboard::isKeyPressed(Keyboard::D) && spritePlayer.getPosition().x < (window.getSize().x - 26))
				spritePlayer.move(0.1f, 0.0f);
			if (Keyboard::isKeyPressed(Keyboard::W) && spritePlayer.getPosition().y > 26)
				spritePlayer.move(0.0f, -0.1f);
			if (Keyboard::isKeyPressed(Keyboard::S) && spritePlayer.getPosition().y < (window.getSize().y - 26))
				spritePlayer.move(0.0f, 0.1f);
		}

		// Fired missile (player)
		if (fired && !menu) {
			spriteShot.move(0.0f, -0.45f);					// initial speed: 0.2f
			if (spriteShot.getPosition().y < -10 ) {			// ADD: OR collision = true;
				fired = false;
			}
		}

		// Collission detection

		if (spriteShot.getPosition().y >= (spriteEnemy.getPosition().y - spriteSize(spriteEnemy).y / 2.0f)
			&&
			spriteShot.getPosition().y <= (spriteEnemy.getPosition().y + spriteSize(spriteEnemy).y / 2.0f)
			&&
			spriteShot.getPosition().x >= (spriteEnemy.getPosition().x - spriteSize(spriteEnemy).x / 2.0f)
			&&
			spriteShot.getPosition().x <= (spriteEnemy.getPosition().x + spriteSize(spriteEnemy).x / 2.0f)) 
		{
			/// ... some pause for animation ...
			enemy_active = false;
			spriteShot.setPosition(700,0);		// sets the shot out of range, hence -> INACTIVE
		}


		/*
		++++++++++++++++++++++
		******* UPDATE *******
		++++++++++++++++++++++
		*/

		animationPawn.Update(0, deltaTime);
		spritePawn.setTextureRect(animationPawn.uvRect);

		if (!intro && !menu) {
			enemy.Move(&window);
			enemy2.Move(&window);
			enemy3.Move(&window);
		}
			
		/*
		+++++++++++++++++++++
		DRAWING to the Screen
		+++++++++++++++++++++
		*/

		window.clear();

		
		if (intro) {
			
			window.draw(spriteIntro);

			messageTitle.display(window);
			messageEnter.display(window);

		}
		else if (!intro && !menu) {
			window.draw(spriteBackground);

			/*  DRAW EVERYTHING ELSE */

			// Draw player
			window.draw(spritePlayer);
			
			window.draw(spritePawn);

			window.draw(enemy.sprite);

			window.draw(enemy2.sprite);

			window.draw(enemy3.sprite);

			window.draw(spriteShot);
		}

		else if (menu) {

			window.draw(spriteMenu);

			/* DRAW BUTTONS */

		}

		window.display();

	}

	return 0;
}

const Vector2f spriteSize(Sprite& sprite) {
	Vector2f size = {
		(sprite.getTexture()->getSize().x * sprite.getScale().x),
		(sprite.getTexture()->getSize().y * sprite.getScale().y) 
	};
	return size;
}

void Center(Sprite& sprite) {
	sprite.setOrigin( sprite.getTexture()->getSize().x / 2.0f , sprite.getTexture()->getSize().y / 2.0f );
}