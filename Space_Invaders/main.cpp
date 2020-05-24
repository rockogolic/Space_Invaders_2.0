// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>
#include "pch.h"
#include "Message.h"
#include "Animation.h"
#include "setSprite.h"
#include "Button.h"
#include "Enemy.h"
#include "CreateEnemy.h"
#include "Player.h"

using namespace sf;

const Vector2f spriteSize(Sprite& sprite);		//  gets the Vector2f in size of the sprite
void Center(Sprite& sprite);					// changes the origin of the sprite to its center

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
	Texture textureEnemy_red;
	textureEnemy_red.loadFromFile("graphics/enemy_red_54x54.png");
	Enemy enemyRed(&textureEnemy_red, &textureShotEnemy);
	
	Texture textureEnemy_green;
	textureEnemy_green.loadFromFile("graphics/enemy_green_54x54.png");
	Enemy enemyGreen(&textureEnemy_green, &textureShotEnemy);

	Texture textureEnemy_purple;
	textureEnemy_purple.loadFromFile("graphics/enemy_purple_54x54.png");
	Enemy enemyPurple(&textureEnemy_purple, &textureShotEnemy);

	/*
	Texture texturePawn;
	texturePawn.loadFromFile("graphics/pawn.png");
	Sprite spritePawn;
	spritePawn.setTexture(texturePawn);
	spritePawn.setPosition(window.getSize().x/2.0f , window.getSize().y/2.0f);
	Animation animationPawn(&texturePawn, Vector2u(3,1), 0.3f);
	//*/

	// BOUNTIES
	
	//std::list <Enemy> bounties;
	//std::vector <Enemy> bounties;

	Texture textureBountyRed;
	textureBountyRed.loadFromFile("graphics/bonus1_red.png");
	Enemy bounty_red(&textureBountyRed, &textureShot);
	//bounties.push_back(bounty_red);
	//bounties[0].colorPlayer;
	bounty_red.setBounty("red", &window);

	Texture textureBountyPink;
	textureBountyPink.loadFromFile("graphics/bonus1_pink.png");
	Enemy bounty_pink(&textureBountyPink, &textureShot);
	bounty_pink.setBounty("pink", &window);

	Texture textureBountyGreen;
	textureBountyGreen.loadFromFile("graphics/bonus1_green.png");
	Enemy bounty_green(&textureBountyGreen, &textureShot);
	bounty_green.setBounty("green", & window);
	//bounties.push_back(bounty_green);

	Texture textureBountyBlue;
	textureBountyBlue.loadFromFile("graphics/bonus1_blue.png");
	Enemy bounty_blue(&textureBountyBlue, &textureShot);
	bounty_blue.setBounty("blue", & window);
	//bounties.push_back(bounty_blue);

	Texture textureBountyOrange;
	textureBountyOrange.loadFromFile("graphics/bonus1_orange.png");
	Enemy bounty_orange(&textureBountyOrange, &textureShot);
	bounty_orange.setBounty("orange", & window);
	//bounties.push_back(bounty_orange);

	Texture textureBountyWhite;
	textureBountyWhite.loadFromFile("graphics/bonus1_white.png");
	Enemy bounty_white(&textureBountyWhite, &textureShot);
	bounty_white.setBounty("white", & window);
	//bounties.push_back(bounty_white);

	/* NEW SPRITES CLASSES */
	
	CreateEnemy wave1_red(Vector2i(1, 1), enemyRed, window);
	CreateEnemy wave1_green(Vector2i(2, 2), enemyGreen, window);
	CreateEnemy wave1_purple(Vector2i(4, 4), enemyPurple, window);

	CreateEnemy wave1;
	wave1.assignEnemy(wave1_green);
	wave1.assignEnemy(wave1_red);
	wave1.assignEnemy(wave1_purple);
	
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
		"Turn off the music",
		Color::White, font_CubicCoreMono, 20
	);

	Message messageWave1(
		"Wave 1",
		Color::White, font_CubicCoreMono, 40
	);
	messageWave1.position(window.getSize().x / 2.0f, window.getSize().y / 3.0f);

	Message messageGetReady(	// will display seconds 3..2..1.. go
		"get ready.. ",
		Color::White, font_CubicCoreMono, 20
	);
	messageGetReady.position(window.getSize().x / 2.0f, 2.0f * window.getSize().y / 3.0f);

	Message messageWave2(
		"Wave 2",
		Color::White, font_CubicCoreMono, 40
	);

	Message messageWave3(
		"Wave 3",
		Color::White, font_CubicCoreMono, 40
	);

	Message messageWave4(
		"Wave 4",
		Color::White, font_CubicCoreMono, 40
	);

	Message messageWave5(
		"Wave 5",
		Color::White, font_CubicCoreMono, 40
	);

	Message messageWave6(
		"Wave 6",
		Color::White, font_CubicCoreMono, 40
	);

	Message messageRoundOver(
		"Round cleared!",
		Color::White, font_CubicCoreMono, 40
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

	bool pause = false;
	bool round1_over = false;
	bool round2_over = false;
	bool round3_over = false;
	bool boss_over = false;

	bool round1 = false;

	// TIME creation
	float deltaTime = 0.0f;
	Clock clock;

	float timePassed = 0.0f;
	unsigned int resTime = 3;	// IS NOT PROPERLY USED! (check the DRAWING section and correct it)

	// Random Generator
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(1, 6);

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
						round1 = true;
						pause = true;
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
		if (!intro && !menu && !hit && !game_over && !pause) {
			if (Keyboard::isKeyPressed(Keyboard::A) && player.sprite.getPosition().x > 26)
				player.sprite.move(-(130 * deltaTime), 0.0f);
			if (Keyboard::isKeyPressed(Keyboard::D) && player.sprite.getPosition().x < (window.getSize().x - 26))
				player.sprite.move( (130 * deltaTime), 0.0f);
			if (Keyboard::isKeyPressed(Keyboard::W) && player.sprite.getPosition().y > 26)
				player.sprite.move(0.0f, -(130 * deltaTime));
			if (Keyboard::isKeyPressed(Keyboard::S) && player.sprite.getPosition().y < (window.getSize().y - 26))
				player.sprite.move(0.0f, (130 * deltaTime));
		}

		/*
		++++++++++++++++++++++
		******* UPDATE *******
		++++++++++++++++++++++
		*/

		//animation

		//animationPawn.Update(0, deltaTime);
		//spritePawn.setTextureRect(animationPawn.uvRect);

		/*
		if (pause) {
			timePassed += deltaTime;
			if (timePassed >= 2.0f) {
				// display wave1
				if (timePassed >= 4.0f) {
					// display "begins in.. " message
					if (timePassed >= 6.0f) {
						resTime--;
						// update to 3.. 2.. 1..
						messageGetReady.getText().setString(messageGetReady.getString() + std::to_string(resTime));
						if (resTime == 0) {
							timePassed = 0.0f;
							resTime = 3;
							pause = false;
						}
					}
				}
			}
		}
		*/
		if (!intro && !menu && !hit && !game_over && !pause) {

			//player actions and game_over conditions
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
			if (wave1.isWinner()) { // || wave2 || wave3 etc. ..
				game_over = true;
			}

			// BOUNTIES
			
			/*
			for (unsigned int i = 0; i < size(bounties); i++) {
				player.Collision(&bounties[i]);
				bounties[i].setBountyAllowed(&window);
				bounties[i].updateBounty(&player, &window, deltaTime);
				bounties[i].Collision(&player);
			}
			//*/

			// __collisions
			
			//*
			player.Collision(&bounty_red);
			player.Collision(&bounty_orange);
			player.Collision(&bounty_green);
			player.Collision(&bounty_blue);
			player.Collision(&bounty_pink);
			player.Collision(&bounty_white);

			bounty_red.setBountyAllowed(&window);
			bounty_orange.setBountyAllowed(&window);
			bounty_green.setBountyAllowed(&window);
			bounty_blue.setBountyAllowed(&window);
			bounty_pink.setBountyAllowed(&window);
			bounty_white.setBountyAllowed(&window);
			
			bounty_red.updateBounty(&window, deltaTime);
			bounty_orange.updateBounty(&window, deltaTime);
			bounty_green.updateBounty(&window, deltaTime);
			bounty_blue.updateBounty(&window, deltaTime);
			bounty_pink.updateBounty(&window, deltaTime);
			bounty_white.updateBounty(&window, deltaTime);
			
			bounty_red.Collision(&player);
			bounty_orange.Collision(&player);
			bounty_green.Collision(&player);
			bounty_blue.Collision(&player);
			bounty_pink.Collision(&player);
			bounty_white.Collision(&player);
			//*/
			// WAVE 1


			wave1.getActive();

			//*
			if (size(wave1.activeEnemies) <= size(wave1.Enemies) && (size(wave1.activeEnemies) > 1))
				wave1.MoveClassic(&window, 1.0f*deltaTime);
			else if (size(wave1.activeEnemies) == 1)
				wave1.MoveClassic(&window, 6.0f * deltaTime);
			//*/

			for (unsigned int i = 0; i < size(wave1.Enemies); i++) {

				player.Collision(&wave1.Enemies[i]);
				
				wave1.Enemies[i].Collision(&player);
				wave1.Enemies[i].shoot();
				wave1.Enemies[i].updateShot(deltaTime);
				//wave1.Enemies[i].Move(&window, deltaTime);
			}

			wave1.updateWinner(&window);

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

			/*
			for (unsigned int i = 0; i < size(bounties); i++) {
				if (bounties[i].isActive()) {
					window.draw(bounties[i].sprite);
				}
			}
			//*/

			//*
			if (bounty_red.isActive())
				window.draw(bounty_red.sprite);
			if (bounty_orange.isActive())
				window.draw(bounty_orange.sprite);
			if (bounty_green.isActive())
				window.draw(bounty_green.sprite);
			if (bounty_blue.isActive())
				window.draw(bounty_blue.sprite);
			if (bounty_pink.isActive())
				window.draw(bounty_pink.sprite);
			if (bounty_white.isActive())
				window.draw(bounty_white.sprite);

			//*/

			//window.draw(bounty_red.sprite);

			for (unsigned int i = 0; i < size(wave1.Enemies); i++) {
				if (wave1.Enemies[i].isActive()) {
					window.draw(wave1.Enemies[i].sprite);
				}
				// continues drawing shot when enemy died
			}

			for (unsigned int i = 0; i < size(wave1.Enemies); i++) {
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

			// PAUSE SCREENS with WAVE nr. information
			if (pause) {
				timePassed += deltaTime;
				if (timePassed >= 2.0f) {
					messageWave1.display(window);
					if (timePassed >= 4.0f) {
						messageGetReady.display(window);
						if (timePassed >= 6.0f) {
							resTime--;
							// update to 3.. 2.. 1.. (FIX and make the FOR loop for counting 3 seconds correctly)
							messageGetReady.getText().setString(messageGetReady.getString() + std::to_string(resTime));
							if (resTime == 0) {
								timePassed = 0.0f;
								resTime = 3;
								pause = false;
							}
						}
					}
				}
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