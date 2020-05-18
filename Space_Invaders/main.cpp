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
#include "Button.h"
#include "Enemy.h"
#include "CreateEnemy.h"
#include "Player.h"
#include <iostream>

using namespace sf;

const Vector2f spriteSize(Sprite& sprite);		//  gets the Vector2f in size of the sprite
void Center(Sprite& sprite);					// changes the origin of the sprite to its center
void FPS(float deltaTime);						// measures average FPS of the run

int main()
{
	// to allow to resize the window -> Style::default and remove other Style::Close && Style::Titlebar
	RenderWindow window(VideoMode(640, 480), "Space Invaders", Style::None);
	
	//Vector2f screenSize(window.getSize().x, window.getSize().y);		// Vector2f of size of the RenderWindow object, window

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

	// SPRITES MENU
	Texture textureMenu;
	textureMenu.loadFromFile("graphics/menu_500x375.png");
	Sprite spriteMenu;
	spriteMenu.setTexture(textureMenu);
	Center(spriteMenu);
	spriteMenu.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

	Texture textureButtonOff, textureButtonOn;
	textureButtonOff.loadFromFile("graphics/button_off_190x50.png");
	textureButtonOn.loadFromFile("graphics/button_on_190x50.png");
	Sprite spriteButtonOff, spriteButtonOn;
	spriteButtonOff.setTexture(textureButtonOff);
	spriteButtonOn.setTexture(textureButtonOn);
	Center(spriteButtonOff);
	Center(spriteButtonOn);

	// SHOTS
	Texture textureShot;
	textureShot.loadFromFile("graphics/shot_13x6.png");
	Texture textureShotEnemy;
	textureShotEnemy.loadFromFile("graphics/shot_enemy.png");

	// PLAYER
	Texture texturePlayer_idle;			// IDLE 
	texturePlayer_idle.loadFromFile("graphics/player_54x54.png");
	Player player(&texturePlayer_idle, &textureShot);

	Texture texturePlayer_left;			// LEFT-Facing
	texturePlayer_left.loadFromFile("graphics/player_left_54x54.png");

	Texture texturePlayer_right;		// RIGHT-Facing
	texturePlayer_right.loadFromFile("graphics/player_right_54x54.png");
	
	// ENEMY
	Texture textureEnemy;
	textureEnemy.loadFromFile("graphics/enemy_red_54x54.png");
	Enemy enemy(&textureEnemy, &textureShotEnemy);

	Texture texturePawn;
	texturePawn.loadFromFile("graphics/pawn.png");
	Sprite spritePawn;
	spritePawn.setTexture(texturePawn);
	spritePawn.setPosition(window.getSize().x/2.0f , window.getSize().y/2.0f);
	Animation animationPawn(&texturePawn, Vector2u(3,1), 0.3f);

	// BOUNTIES
	Texture textureBountyRed;
	textureBountyRed.loadFromFile("graphics/bonus1_red.png");
	Enemy bounty(&textureBountyRed, &textureShot);
	bounty.setBounty("red", &window);

	Texture textureBountyPink;
	textureBountyPink.loadFromFile("graphics/bonus1_pink.png");
	Enemy bounty_pink(&textureBountyPink, &textureShot);
	bounty_pink.setBounty("pink", &window);
	

	/* NEW SPRITES CLASSES */

	CreateEnemy wave1(Vector2i(6,5), enemy, window);
	

	// Explosions

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
	messageTitle.position(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

	Message messageEnter(
		"Press ENTER to start..",
		Color::White, font_CubicCoreMono, 40
	);
	messageEnter.position(window.getSize().x / 2.0f, window.getSize().y / 1.5f);

	Message messageMenu_1(
		"Main menu",
		Color::White, font_CubicCoreMono, 20
	);

	Message messageHit(
		"Hit ENTER to continue",
		Color::White, font_CubicCoreMono, 40
	);
	messageHit.position(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

	Message messageGameOver(
		"GAME OVER",
		Color::Red, font_CubicCoreMono, 60
	);
	messageGameOver.position(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

	Message messageHealth(
		"Health: ",
		Color::White, font_CubicCoreMono, 30
	);
	messageHealth.position(window.getSize().x / 8.0f, window.getSize().y / 15.0f);

	Message messageScore(
		"Score: ",
		Color::White, font_CubicCoreMono, 30
	);
	messageScore.position(6.0f * window.getSize().x / 8.0f, window.getSize().y / 15.0f);

	Message messageMenuExit(
		"Quit game",
		Color::White, font_CubicCoreMono, 20	
	);
	Message messageMenuMusic(
		"Turn off the main theme",
		Color::White, font_CubicCoreMono, 20
	);

	// BUTTONS

	Button buttonSoundOff(&textureButtonOff, &textureButtonOn);
	Button buttonExit(&textureButtonOff, &textureButtonOn);
	
	buttonSoundOff.Position(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 4.0f));
	buttonExit.Position(Vector2f(window.getSize().x / 2.0f, window.getSize().y * 3.0f / 4.0f));
	
	buttonSoundOff.setMessage(&messageMenuMusic);
	buttonExit.setMessage(&messageMenuExit);

	int buttonChoice = 0;

	/* BOOLEANS to control phases of the GAME */

	bool intro = true;			// introduction screen; def -> true;
	bool menu = false;			// menu screen in the game; if !intro -> def->false; 
	bool hit = false;			// show a message when player is hit, to continue
	bool game_over = false;

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
					else if (!intro && !menu && !hit && !game_over) {
						//printf("\n A Menu is open! \n");
						std::cout << "\n A Menu is open!" << std::endl;
						menu = true;
					}
					else if (!intro && menu && !hit && !game_over) {
						//printf("\n A Menu is closed! \n");
						std::cout << "\n A Menu is closed!" << std::endl;
						menu = false;
					}
					else if (!intro && !menu && (hit || game_over)) {
						window.close();
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Return)) {
					if (intro) {
						intro = false;
					}
					if (hit) {
						hit = false;
					}
					if (buttonExit.isOn()) {
						window.close();
					}
					
					// configure other buttons
				}
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					if (!intro && !menu && !hit && !game_over) {
						player.shoot();
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					std::cout << 1 / (deltaTime) << std::endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Down)) {
					if (menu) {
						buttonChoice++;
						if (buttonChoice % 2 == 0) {
							buttonExit.setOn();
							buttonSoundOff.setOff();
						}
						else if (buttonChoice % 2 == 1) {
							buttonExit.setOff();
							buttonSoundOff.setOn();
						}
					}
				}

				// More buttons
			}
		}

		/* Long-run commands -> Player movement and Game-related mechanics */

		// Player's movement
		if (!intro && !menu && !hit && !game_over) {
			if (Keyboard::isKeyPressed(Keyboard::A) && player.sprite.getPosition().x > 26)
				player.sprite.move(-(230 * deltaTime), 0.0f);
			if (Keyboard::isKeyPressed(Keyboard::D) && player.sprite.getPosition().x < (window.getSize().x - 26))
				player.sprite.move( (230 * deltaTime), 0.0f);
			if (Keyboard::isKeyPressed(Keyboard::W) && player.sprite.getPosition().y > 26)
				player.sprite.move(0.0f, -(230 * deltaTime));
			if (Keyboard::isKeyPressed(Keyboard::S) && player.sprite.getPosition().y < (window.getSize().y - 26))
				player.sprite.move(0.0f, (230 * deltaTime));
		}

		/*
		++++++++++++++++++++++
		******* UPDATE *******
		++++++++++++++++++++++
		*/

		//animation

		//animationPawn.Update(0, deltaTime);
		//spritePawn.setTextureRect(animationPawn.uvRect);

		if (!intro && !menu && !hit && !game_over) {

			//player actions
			player.updateShot(deltaTime);

			if (player.isHit()) {
				if (player.isDead() == true) {
					game_over = true;
				}
				else {
					hit = true;
					player.setAlive();
				}
			}

			// BOUNTIES
			player.Collision(&bounty_pink);
			bounty_pink.updateBounty(&window,deltaTime);
			bounty_pink.Collision(&player);
			
			// WAVE 1
			for (unsigned int i = 0; i < size(wave1.Enemies); i++) {
				
				player.Collision(&wave1.Enemies[i]);

				wave1.Enemies[i].Move(&window, deltaTime);
				wave1.Enemies[i].Collision(&player);
				wave1.Enemies[i].shoot();
				wave1.Enemies[i].updateShot(deltaTime);

				if (wave1.Enemies[i].hasWon()) {
					game_over = true;
				}
			}

			messageHealth.updateMessageHealth(&player);
			messageScore.updateMessageScore(&player);

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
		else if (!intro) {
			window.draw(spriteBackground);

			/*  DRAW EVERYTHING ELSE */
			window.draw(player.sprite);

			//window.draw(spritePawn);

			window.draw(player.spriteShot);

			if (bounty_pink.isActive()) {
				window.draw(bounty_pink.sprite);
			}

			for (unsigned int i = 0; i < size(wave1.Enemies); i++) {
				if (wave1.Enemies[i].isActive()) {
					window.draw(wave1.Enemies[i].sprite);
				}
				// continues drawing shot when enemy died
				window.draw(wave1.Enemies[i].spriteShot);		
			}
			

			messageHealth.display(window);
			messageScore.display(window);

			
			if (hit)
				messageHit.display(window);

			if (menu) {
				window.draw(spriteMenu);

				if (buttonExit.isOff())
					window.draw(buttonExit.spriteButtonOff);
				else if (buttonExit.isOn())
					window.draw(buttonExit.spriteButtonOn);
				if (buttonSoundOff.isOff())
					window.draw(buttonSoundOff.spriteButtonOff);
				else if (buttonSoundOff.isOn())
					window.draw(buttonSoundOff.spriteButtonOn);

				window.draw(buttonExit.text);
				window.draw(buttonSoundOff.text);
			}

			if (game_over) {
				messageGameOver.display(window);
			}
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

void FPS(float deltaTime) {

	float time = 0.0f;
	float total = 0.0f;
	time += deltaTime;
	std::vector<float> _timeMeas;
	while (time < 2) {
		_timeMeas.push_back(deltaTime);
	}
	
	for (unsigned int i = 0; i < size(_timeMeas); i++) {
		total += _timeMeas[i];
	}
	std::cout << "Average FPS is: " << 1/(total / size(_timeMeas)) << std::endl;


}