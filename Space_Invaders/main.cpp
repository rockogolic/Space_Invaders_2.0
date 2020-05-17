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

int main()
{
	// to allow to resize the window -> Style::default and remove other Style::Close && Style::Titlebar
	RenderWindow window(VideoMode(640, 480), "Space Invaders", Style::None);
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
	Enemy enemy1(enemy);
	Enemy enemy2(enemy);
	Enemy enemy3(enemy);
	Enemy enemy4(enemy);
	Enemy enemy5(enemy);
	enemy.setPosition(Vector2f(50.0f, 80.0f));
	enemy2.setPosition(Vector2f(185.0f, 80.0f));
	enemy3.setPosition(Vector2f(320.0f, 80.0f));
	enemy4.setPosition(Vector2f(455.0f, 80.0f));
	enemy5.setPosition(Vector2f(590.0f, 80.0f));

	Texture texturePawn;
	texturePawn.loadFromFile("graphics/pawn.png");
	Sprite spritePawn;
	spritePawn.setTexture(texturePawn);
	spritePawn.setPosition(screenSize.x/2.0f , screenSize.y/2.0f);
	Animation animationPawn(&texturePawn, Vector2u(3,1), 0.3f);

	/* NEW SPRITES CLASSES */


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

	Message messageHit(
		"Hit ENTER to continue",
		Color::White, font_CubicCoreMono, 40
	);
	messageHit.position(screenSize.x / 2.0f, screenSize.y / 2.0f);

	Message messageGameOver(
		"GAME OVER",
		Color::Red, font_CubicCoreMono, 60
	);
	messageGameOver.position(screenSize.x / 2.0f, screenSize.y / 2.0f);

	Message messageHealth(
		"Health: ",
		Color::White, font_CubicCoreMono, 30
	);
	messageHealth.position(screenSize.x / 8.0f, screenSize.y / 15.0f);

	Message messageScore(
		"Score: ",
		Color::White, font_CubicCoreMono, 30
	);
	messageScore.position(6.0f * screenSize.x / 8.0f, screenSize.y / 15.0f);

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
				}
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					if (!intro && !menu && !hit && !game_over) {
						player.shoot();
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					if (menu) {

					}
				}

				// More buttons
			}
		}

		/* Long-run commands -> Player movement and Game-related mechanics */

		// Player's movement
		if (!intro && !menu && !hit && !game_over) {
			if (Keyboard::isKeyPressed(Keyboard::A) && player.sprite.getPosition().x > 26)
				player.sprite.move(-0.1f, 0.0f);
			if (Keyboard::isKeyPressed(Keyboard::D) && player.sprite.getPosition().x < (window.getSize().x - 26))
				player.sprite.move(0.1f, 0.0f);
			if (Keyboard::isKeyPressed(Keyboard::W) && player.sprite.getPosition().y > 26)
				player.sprite.move(0.0f, -0.1f);
			if (Keyboard::isKeyPressed(Keyboard::S) && player.sprite.getPosition().y < (window.getSize().y - 26))
				player.sprite.move(0.0f, 0.1f);
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

			//enemy movement
			enemy.Move(&window);
			enemy2.Move(&window);
			enemy3.Move(&window);
			enemy4.Move(&window);
			enemy5.Move(&window);

			//player actions
			player.updateShot();

			player.Collision(&enemy);
			player.Collision(&enemy2);
			player.Collision(&enemy3);
			player.Collision(&enemy4);
			player.Collision(&enemy5);

			if (player.isHit()) {
				if (player.isDead() == true) {
					game_over = true;
				}
				else {
					hit = true;
					player.setAlive();
				}
			}
			else if (enemy.hasWon() || enemy2.hasWon() || enemy3.hasWon() || enemy4.hasWon() || enemy5.hasWon()) {
				game_over = true;
			}

			//enemy collision detection
			enemy.Collision(&player);
			enemy2.Collision(&player);
			enemy3.Collision(&player);
			enemy4.Collision(&player);
			enemy5.Collision(&player);

			// enemy shooting
			enemy.shoot();
			enemy2.shoot();
			enemy3.shoot();
			enemy4.shoot();
			enemy5.shoot();

			enemy.updateShot();
			enemy2.updateShot();
			enemy3.updateShot();
			enemy4.updateShot();
			enemy5.updateShot();

			messageHealth.updateMessage(&player);

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

			if (enemy.isActive())
				window.draw(enemy.sprite);
			if (enemy2.isActive())
				window.draw(enemy2.sprite);
			if (enemy3.isActive())
				window.draw(enemy3.sprite);
			if (enemy4.isActive())
				window.draw(enemy4.sprite);
			if (enemy5.isActive())
				window.draw(enemy5.sprite);

			window.draw(player.spriteShot);

			window.draw(enemy.spriteShot);
			window.draw(enemy2.spriteShot);
			window.draw(enemy3.spriteShot);
			window.draw(enemy4.spriteShot);
			window.draw(enemy5.spriteShot);

			messageHealth.display(window);
			messageScore.display(window);

			if (hit)
				messageHit.display(window);

			if (menu) {
				window.draw(spriteMenu);
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