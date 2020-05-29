// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


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

	/* DECLARE and LOAD sounds, sprites, fonts, etc. ... */

	// SOUNDS
	SoundBuffer bufferIntro;
	bufferIntro.loadFromFile("sounds/intro.wav");
	Sound soundIntro;
	soundIntro.setBuffer(bufferIntro);

	SoundBuffer bufferMain;
	bufferMain.loadFromFile("sounds/mainTheme.wav");
	Sound soundMain;
	soundMain.setBuffer(bufferMain);

	SoundBuffer bufferShot;
	bufferShot.loadFromFile("sounds/shot.wav");
	Sound soundShot;
	soundShot.setBuffer(bufferShot);

	SoundBuffer bufferRevived;
	bufferRevived.loadFromFile("sounds/revived.wav");
	Sound soundRevived;
	soundRevived.setBuffer(bufferRevived);

	SoundBuffer bufferDead;
	bufferDead.loadFromFile("sounds/dead.wav");
	Sound soundDead;
	soundDead.setBuffer(bufferDead);

	SoundBuffer bufferHit;
	bufferHit.loadFromFile("sounds/hit.wav");
	Sound soundHit;
	soundHit.setBuffer(bufferHit);

	SoundBuffer bufferVictory;
	bufferVictory.loadFromFile("sounds/victory.wav");
	Sound soundVictory;
	soundVictory.setBuffer(bufferVictory);


	// FONTS 
	Font font_MKPixelProject;
	font_MKPixelProject.loadFromFile("fonts/MKPixelProject.ttf");

	Font font_CubicCoreMono;
	font_CubicCoreMono.loadFromFile("fonts/CubicCoreMono.ttf");

	// SPRITE INTRO
	Texture textureIntro;
	textureIntro.loadFromFile("graphics/space_640x480.png");
	Sprite spriteIntro;
	spriteIntro.setTexture(textureIntro);
	
	// BACKGROUND
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/game_640x480.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);

	Texture textureStarBig;
	textureStarBig.loadFromFile("graphics/star1.png");
	Texture textureStarSmall;
	textureStarSmall.loadFromFile("graphics/star2.png");

	Sprite spriteStarBig1;
	spriteStarBig1.setTexture(textureStarBig);
	spriteStarBig1.setPosition(300,100);
	Sprite spriteStarBig2;
	spriteStarBig2.setTexture(textureStarBig);
	spriteStarBig2.setPosition(200,200);

	Sprite spriteStarSmall1;
	spriteStarSmall1.setTexture(textureStarSmall);
	spriteStarSmall1.setPosition(400,250);
	Sprite spriteStarSmall2;
	spriteStarSmall2.setTexture(textureStarSmall);
	Sprite spriteStarSmall3;
	spriteStarSmall3.setTexture(textureStarSmall);

	Sprite spriteFallingStar1;
	spriteFallingStar1.setTexture(textureStarSmall);

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

	Texture textureWinner;
	textureWinner.loadFromFile("graphics/player_speed_54x54.png");

	Texture texturePlayer_left;			// LEFT-Facing
	texturePlayer_left.loadFromFile("graphics/player_left_54x54.png");

	Texture texturePlayer_right;		// RIGHT-Facing
	texturePlayer_right.loadFromFile("graphics/player_right_54x54.png");

	Player player(&texturePlayer_idle, &textureShot, &textureWinner, &window);
	
	// ENEMY
	Texture textureEnemy_red;
	textureEnemy_red.loadFromFile("graphics/enemy_red_54x54.png");
	Enemy enemyRed(&textureEnemy_red, &textureShotEnemy, 1);
	
	Texture textureEnemy_green;
	textureEnemy_green.loadFromFile("graphics/enemy_green_54x54.png");
	Enemy enemyGreen(&textureEnemy_green, &textureShotEnemy, 2);

	Texture textureEnemy_purple;
	textureEnemy_purple.loadFromFile("graphics/enemy_purple_54x54.png");
	Enemy enemyPurple(&textureEnemy_purple, &textureShotEnemy, 3);

	Texture textureEnemy_pink;
	textureEnemy_pink.loadFromFile("graphics/enemy_pink_54x54.png");
	Enemy enemyPink(&textureEnemy_pink, &textureShotEnemy, 5);

	/*
	Texture texturePawn;
	texturePawn.loadFromFile("graphics/pawn.png");
	Sprite spritePawn;
	spritePawn.setTexture(texturePawn);
	spritePawn.setPosition(window.getSize().x/2.0f , window.getSize().y/2.0f);
	Animation animationPawn(&texturePawn, Vector2u(3,1), 0.3f);
	//*/

	// BOUNTIES
	Texture textureBountyRed;
	textureBountyRed.loadFromFile("graphics/bonus1_red.png");
	Enemy bounty_red(&textureBountyRed, &textureShot, 1);
	bounty_red.setBounty("red", &window);

	Texture textureBountyPink;
	textureBountyPink.loadFromFile("graphics/bonus1_pink.png");
	Enemy bounty_pink(&textureBountyPink, &textureShot, 1);
	bounty_pink.setBounty("pink", &window);

	Texture textureBountyGreen;
	textureBountyGreen.loadFromFile("graphics/bonus1_green.png");
	Enemy bounty_green(&textureBountyGreen, &textureShot, 1);
	bounty_green.setBounty("green", & window);

	Texture textureBountyBlue;
	textureBountyBlue.loadFromFile("graphics/bonus1_blue.png");
	Enemy bounty_blue(&textureBountyBlue, &textureShot, 1);
	bounty_blue.setBounty("blue", & window);

	Texture textureBountyOrange;
	textureBountyOrange.loadFromFile("graphics/bonus1_orange.png");
	Enemy bounty_orange(&textureBountyOrange, &textureShot, 1);
	bounty_orange.setBounty("orange", & window);

	Texture textureBountyWhite;
	textureBountyWhite.loadFromFile("graphics/bonus1_white.png");
	Enemy bounty_white(&textureBountyWhite, &textureShot, 1);
	bounty_white.setBounty("white", & window);

	/* NEW SPRITES CLASSES */
	
	CreateEnemy wave1_red(Vector2i(2, 1), enemyRed, window);
	CreateEnemy wave1;
	wave1.assignEnemy(wave1_red);

	CreateEnemy wave2_red(Vector2i(3, 2), enemyRed, window);
	CreateEnemy wave2_green(Vector2i(2, 1), enemyGreen, window);
	CreateEnemy wave2;
	wave2.assignEnemy(wave2_red);
	wave2.assignEnemy(wave2_green);

	CreateEnemy wave3_green(Vector2i(2, 2), enemyGreen, window);
	CreateEnemy wave3;
	wave3.assignEnemy(wave3_green);

	CreateEnemy wave4_green(Vector2i(2, 2), enemyGreen, window);
	CreateEnemy wave4_purple(Vector2i(1, 1), enemyPurple, window);
	CreateEnemy wave4;
	wave4.assignEnemy(wave4_green);
	wave4.assignEnemy(wave4_purple);

	CreateEnemy wave5_red(Vector2i(5, 2), enemyRed, window);
	CreateEnemy wave5_green(Vector2i(3, 1), enemyGreen, window);
	CreateEnemy wave5_purple(Vector2i(2, 1), enemyPurple, window);
	CreateEnemy wave5;
	wave5.assignEnemy(wave5_red);
	wave5.assignEnemy(wave5_green);
	wave5.assignEnemy(wave5_purple);

	// other waves

	CreateEnemy wave6_pink(Vector2i(1, 1), enemyPink, window);
	CreateEnemy wave6_green(Vector2i(2, 2), enemyGreen, window);
	CreateEnemy wave6_purple(Vector2i(4, 4), enemyPurple, window);
	CreateEnemy wave6;
	wave6.assignEnemy(wave6_green);
	wave6.assignEnemy(wave6_pink);
	wave6.assignEnemy(wave6_purple);
	
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

	Message messageWave(
		"Wave ",
		Color::White, font_CubicCoreMono, 40
	);
	messageWave.position(window.getSize().x / 2.0f, window.getSize().y / 3.0f);

	Message messageGetReady(	// will display seconds 3..2..1.. go
		"get ready.. ",
		Color::White, font_CubicCoreMono, 20
	);
	messageGetReady.position(window.getSize().x / 2.0f, 2.0f * window.getSize().y / 3.0f);

	Message messageRoundOver(
		"Round cleared!",
		Color::White, font_CubicCoreMono, 40
	);
	messageRoundOver.position(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

	Message messageGlory(
		"G L O R Y",
		Color::White, font_CubicCoreMono, 60
	);
	messageGlory.position(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

	Message messageVictory(
		"V I C T O R Y ...",
		Color::White, font_CubicCoreMono, 60
	);
	messageVictory.position(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

	Message messageMenuExit(
		"Quit game",
		Color::White, font_CubicCoreMono, 20
	);
	Message messageMenuMusicOff(
		"Turn the music OFF",
		Color::White, font_CubicCoreMono, 20
	);
	Message messageMenuMusicOn(
		"Turn the music ON",
		Color::White, font_CubicCoreMono, 20
	);
	Message messageAbout(
		"About",
		Color::White, font_CubicCoreMono, 20
	);

	// BUTTONS

	Button buttonExit(&textureButtonOff, &textureButtonOn);
	Button buttonSound(&textureButtonOff, &textureButtonOn);
	Button buttonSoundOn(&textureButtonOff, &textureButtonOn);
	Button buttonAbout(&textureButtonOff, &textureButtonOn);
	
	buttonExit.Position(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 4.0f));
	buttonSound.Position(Vector2f(window.getSize().x / 2.0f, window.getSize().y * 2.0f / 4.0f));
	buttonSoundOn.Position(Vector2f(window.getSize().x / 2.0f, window.getSize().y * 2.0f / 4.0f));
	buttonAbout.Position(Vector2f(window.getSize().x / 2.0f, window.getSize().y * 3.0f / 4.0f));

	buttonExit.setMessage(&messageMenuExit);
	buttonSound.setMessage(&messageMenuMusicOff);
	buttonSoundOn.setMessage(&messageMenuMusicOn);
	buttonAbout.setMessage(&messageAbout);

	int buttonChoice = 0;

	/* BOOLEANS to control phases of the GAME */

	bool intro = true;			// introduction screen; def -> true;
	bool menu = false;			// menu screen in the game; if !intro -> def->false; 
	bool hit = false;			// show a message when player is hit, to continue
	bool game_over = false;
	bool winScreen = false;		// shows a win screen with animation when player wins

	bool pause = false;
	bool round_cleared = false;
	bool round_isON = false;	// for wave statistics and whenever the new wave begins
	// continuous sound management
	bool play_intro = false;	// sound Intro
	bool play_main = false;		// sound Main Theme
	bool play_victory = false;	// sound Victory
	bool play_gameover = false; // sound GameOver

	bool stop_music = false;	// stops by pressing button in menu

	unsigned int wave_count = 0;

	// TIME creation
	float deltaTime = 0.0f;
	Clock clock;

	float timePassed_roundCleared = 0.0f;
	float timePassed_pause = 0.0f;
	float timePassed_winner = 0.0f;
	float time = 0.0f;			// for the final animation of the player

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
					else if (!intro && !menu && !hit && !game_over && !pause && !round_cleared && !winScreen) {
						std::cout << "\n A Menu is open!" << std::endl;

						// refresh the button layout (set all to OFF)
						if (buttonChoice != 0) {
							buttonChoice = 0;

							buttonExit.setOff();
							buttonSound.setOff();
							buttonAbout.setOff();
						}

						menu = true;
					}
					else if (!intro && menu && !hit && !game_over && !pause && !round_cleared && !winScreen) {
						std::cout << "\n A Menu is closed!" << std::endl;
						menu = false;
					}
					else if (!intro && !menu && (hit || game_over || winScreen)) {
						window.close();
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Return)) {
					if (intro) {
						intro = false;
						play_intro = false;
						soundIntro.stop();

						round_isON = true;
						pause = true;
					}
					if (hit) {
						hit = false;

						if (!round_isON && !player.isDead() && !game_over) {
							soundRevived.setVolume(50.0f);
							soundRevived.play();
						}
					}
					if (menu) {
						if (buttonExit.isOn()) {
							window.close();
						}
						if (buttonSound.isOn() && menu) {
							if (stop_music == false) {
								stop_music = true;
								soundMain.stop();
							}
							else if (stop_music == true)
								stop_music = false;
						}

						// configure other menu buttons

					}

					// configure other keys
				}
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					if (!intro && !menu && !hit && !game_over && !pause && !round_isON && player.hasShot() == false) {
						player.shoot();

						soundShot.setVolume(50.0f);
						soundShot.play();
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					if (menu) {
						if (buttonChoice == 0 || buttonChoice == 1)
							buttonChoice = 3;
						else if (buttonChoice == 2)
							buttonChoice = 1;
						else if (buttonChoice == 3)
							buttonChoice = 2;

						if (buttonChoice == 1) {
							buttonExit.setOn();
							buttonSound.setOff();
							buttonAbout.setOff();
						}
						else if (buttonChoice == 2) {
							buttonExit.setOff();
							buttonSound.setOn();
							buttonAbout.setOff();
						}
						else if (buttonChoice == 3) {
							buttonExit.setOff();
							buttonSound.setOff();
							buttonAbout.setOn();
						}
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Down)) {
					if (menu) {
						if (buttonChoice == 0 || buttonChoice == 3)
							buttonChoice = 1;
						else if (buttonChoice == 1)
							buttonChoice = 2;
						else if (buttonChoice == 2)
							buttonChoice = 3;

						if (buttonChoice == 1) {
							buttonExit.setOn();
							buttonSound.setOff();
							buttonAbout.setOff();
						}
						else if (buttonChoice == 2) {
							buttonExit.setOff();
							buttonSound.setOn();
							buttonAbout.setOff();
						}
						else if (buttonChoice == 3) {
							buttonExit.setOff();
							buttonSound.setOff();
							buttonAbout.setOn();
						}
						/*
						buttonChoice++;
						if (buttonChoice % 2 == 0) {
							buttonExit.setOn();
							buttonSoundOff.setOff();
						}
						else if (buttonChoice % 2 == 1) {
							buttonExit.setOff();
							buttonSoundOff.setOn();
						}
						//*/
					}
				}

				// More buttons
			}
		}

		/* continuous sound management */
		if (intro && !play_intro) {
			play_intro = true;

			soundIntro.setVolume(50.0f);
			soundIntro.play();
		}
		if (player.isWinner() && !play_victory) {
			play_victory = true;

			soundVictory.setVolume(50.0f);
			soundVictory.play();
		}

		if (game_over && !play_gameover) {
			soundMain.stop();
			
			soundDead.setVolume(50.0f);
			soundDead.play();
			play_gameover = true;
		}

		if (!intro && !player.isWinner() && !winScreen && !play_main && !game_over) {
			play_main = true;
			if (play_main) {
				soundMain.play();
			}
		}
		if ( soundMain.getStatus() == SoundSource::Stopped && stop_music == false ) {
			play_main = false;
		}

		/* Long-run commands -> Player movement and Game-related mechanics */

		// Player's movement
		if (!intro && !menu && !hit && !game_over && !pause && !round_cleared && !player.isWinner()) {
			if (Keyboard::isKeyPressed(Keyboard::A) && player.sprite.getPosition().x > player.sprite.getTexture()->getSize().x / 2.0f)
				player.sprite.move(-(130 * deltaTime), 0.0f);
			if (Keyboard::isKeyPressed(Keyboard::D) && player.sprite.getPosition().x < (window.getSize().x - player.sprite.getTexture()->getSize().x / 2.0f))
				player.sprite.move( (130 * deltaTime), 0.0f);
			if (Keyboard::isKeyPressed(Keyboard::W) && player.sprite.getPosition().y > player.sprite.getTexture()->getSize().x / 2.0f)
				player.sprite.move(0.0f, -(130 * deltaTime));
			if (Keyboard::isKeyPressed(Keyboard::S) && player.sprite.getPosition().y < (window.getSize().y - player.sprite.getTexture()->getSize().x / 2.0f))
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

		if (pause) {
			if (round_isON && !game_over) {
				// reset position of player and player's shot (sets off)
				player.resetPosition();
				player.spriteShot.setPosition(-700,-700);
				
				++wave_count;
				messageWave.updateMessage(wave_count);
				round_isON = false;
			}			
		}

		// Background animation
		if (!intro) {
			



		}

		if (!intro && !menu && !hit && !game_over && !pause && !round_cleared && !(player.isWinner())) {

			//player actions and game_over conditions
			player.updateShot(deltaTime);

			if (player.isHit()) {
				if (player.isDead()) {
					game_over = true;
				}
				else {
					hit = true;
					soundHit.setVolume(50.0f);
					soundHit.play();
					player.setAlive();
				}
			}
			if (
				wave1.isWinner() || wave2.isWinner()
				|| 
				wave3.isWinner() || wave4.isWinner()
				|| 
				wave5.isWinner() || wave6.isWinner()
				) 
			{
				game_over = true;
			}

			// BOUNTIES
			
			player.Collision(&bounty_red);
			player.Collision(&bounty_orange);
			player.Collision(&bounty_green);
			player.Collision(&bounty_blue);
			player.Collision(&bounty_pink);

			bounty_red.setBountyAllowed(&window);
			bounty_orange.setBountyAllowed(&window);
			bounty_green.setBountyAllowed(&window);
			bounty_blue.setBountyAllowed(&window);
			bounty_pink.setBountyAllowed(&window);
			
			bounty_red.updateBounty(&window, deltaTime);
			bounty_orange.updateBounty(&window, deltaTime);
			bounty_green.updateBounty(&window, deltaTime);
			bounty_blue.updateBounty(&window, deltaTime);
			bounty_pink.updateBounty(&window, deltaTime);
			
			bounty_red.Collision(&player);
			bounty_orange.Collision(&player);
			bounty_green.Collision(&player);
			bounty_blue.Collision(&player);
			bounty_pink.Collision(&player);

			// WAVES
			
			// wave 1
			if (wave_count == 1) {
				wave1.getActive();

				if (size(wave1.activeEnemies) <= size(wave1.Enemies) && (size(wave1.activeEnemies) > 1))
					wave1.MoveClassic(&window, 1.0f * deltaTime);
				else if (size(wave1.activeEnemies) == 1)
					wave1.MoveClassic(&window, 6.0f * deltaTime);

				for (unsigned int i = 0; i < size(wave1.Enemies); i++) {

					player.Collision(&wave1.Enemies[i]);

					wave1.Enemies[i].Collision(&player);
					//wave1.Enemies[i].shoot();
					//wave1.Enemies[i].updateShot(&window, deltaTime);
					wave1.Enemies[i].shootGrunt(5);
					wave1.Enemies[i].updateShotGrunt(&window, deltaTime);
				}
				wave1.updateWinner(&window);

				if (size(wave1.activeEnemies) == 0) {
					round_isON = true;		// next round is ON (activates line 387 through round_cleared in UPDATE)
					round_cleared = true;	// this round is cleared (activates line 596 in DRAW)
				}
			}

			// wave 2
			if (wave_count == 2) {
				wave2.getActive();

				if (size(wave2.activeEnemies) <= size(wave2.Enemies) && (size(wave2.activeEnemies) > 1))
					wave2.MoveClassic(&window, 1.0f * deltaTime);
				else if (size(wave2.activeEnemies) == 1)
					wave2.MoveClassic(&window, 6.0f * deltaTime);

				for (unsigned int i = 0; i < size(wave2.Enemies); i++) {

					player.Collision(&wave2.Enemies[i]);

					wave2.Enemies[i].Collision(&player);
					wave2.Enemies[i].shoot();
					wave2.Enemies[i].updateShot(&window, deltaTime);
				}
				
				wave2.updateWinner(&window);

				if (size(wave2.activeEnemies) == 0) {
					round_isON = true;		// next round is ON (activates line 387 through round_cleared in UPDATE)
					round_cleared = true;	// this round is cleared (activates line 596 in DRAW)
				}
			}

			// wave 3
			if (wave_count == 3) {
				wave3.getActive();

				if (size(wave3.activeEnemies) <= size(wave3.Enemies) && (size(wave3.activeEnemies) > 1))
					wave3.MoveClassic(&window, 1.0f * deltaTime);
				else if (size(wave3.activeEnemies) == 1)
					wave3.MoveClassic(&window, 6.0f * deltaTime);

				for (unsigned int i = 0; i < size(wave3.Enemies); i++) {

					player.Collision(&wave3.Enemies[i]);

					wave3.Enemies[i].Collision(&player);
					wave3.Enemies[i].shoot();
					wave3.Enemies[i].updateShot(&window, deltaTime);
				}

				wave3.updateWinner(&window);

				if (size(wave3.activeEnemies) == 0) {
					round_isON = true;		// next round is ON (activates line 387 through round_cleared in UPDATE)
					round_cleared = true;	// this round is cleared (activates line 596 in DRAW)
				}
			}

			// wave 4
			if (wave_count == 4) {
				wave4.getActive();

				if (size(wave4.activeEnemies) <= size(wave4.Enemies) && (size(wave4.activeEnemies) > 1))
					wave4.MoveClassic(&window, 1.0f * deltaTime);
				else if (size(wave4.activeEnemies) == 1)
					wave4.MoveClassic(&window, 6.0f * deltaTime);

				for (unsigned int i = 0; i < size(wave4.Enemies); i++) {

					player.Collision(&wave4.Enemies[i]);

					wave4.Enemies[i].Collision(&player);
					wave4.Enemies[i].shoot();
					wave4.Enemies[i].updateShot(&window, deltaTime);
				}

				wave4.updateWinner(&window);

				if (size(wave4.activeEnemies) == 0) {
					round_isON = true;		// next round is ON (activates line 387 through round_cleared in UPDATE)
					round_cleared = true;	// this round is cleared (activates line 596 in DRAW)
				}
			}

			// wave 5
			if (wave_count == 5) {
				wave5.getActive();

				if (size(wave5.activeEnemies) <= size(wave5.Enemies) && (size(wave5.activeEnemies) > 1))
					wave5.MoveClassic(&window, 1.0f * deltaTime);
				else if (size(wave5.activeEnemies) == 1)
					wave5.MoveClassic(&window, 6.0f * deltaTime);

				for (unsigned int i = 0; i < size(wave5.Enemies); i++) {

					player.Collision(&wave5.Enemies[i]);

					wave5.Enemies[i].Collision(&player);
					wave5.Enemies[i].shoot();
					wave5.Enemies[i].updateShot(&window, deltaTime);
				}

				wave5.updateWinner(&window);

				if (size(wave5.activeEnemies) == 0) {
					round_isON = true;		// next round is ON (activates line 387 through round_cleared in UPDATE)
					round_cleared = true;	// this round is cleared (activates line 596 in DRAW)
				}
			}

			// wave 6
			if (wave_count == 6) {
				wave6.getActive();

				//*
				if (size(wave6.activeEnemies) <= size(wave6.Enemies) && (size(wave6.activeEnemies) > 1))
					wave6.MoveClassic(&window, 1.0f * deltaTime);
				else if (size(wave6.activeEnemies) == 1)
					wave6.MoveClassic(&window, 6.0f * deltaTime);

				for (unsigned int i = 0; i < size(wave6.Enemies); i++) {

					player.Collision(&wave6.Enemies[i]);

					wave6.Enemies[i].Collision(&player);
					wave6.Enemies[i].shoot();
					wave6.Enemies[i].updateShot(&window, deltaTime);
					//wave6.Enemies[i].Move(&window, deltaTime);
				}

				wave6.updateWinner(&window);

				if (size(wave6.activeEnemies) == 0) {
					player.setWinner();
				}
			}
			messageHealth.updateMessageHealth(&player);
			messageScore.updateMessageScore(&player);

		} 

		if (player.isWinner() && winScreen) {
			time += deltaTime;
			// animation of another sprite of player, when he wins
			player.byebyeWinner(0.50f * deltaTime * time);
		}

		/*
		+++++++++++++++++++++
		DRAWING to the Screen
		+++++++++++++++++++++
		*/

		window.clear();

		
		if (intro) {
			window.draw(spriteIntro);

			window.draw(spriteStarBig1);
			window.draw(spriteStarBig2);
			window.draw(spriteStarSmall1);

			messageTitle.display(window);
			messageEnter.display(window);

		}
		else if (!intro) {
			window.draw(spriteBackground);

			/*  DRAW EVERYTHING ELSE */
			if (winScreen == false) {
				window.draw(player.sprite);

				window.draw(player.spriteShot);
			}
			else if (player.isWinner() && winScreen) {
				window.draw(player.spriteWinner);
			}

			//window.draw(spritePawn);
			if (player.isWinner() == false) {
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
			}

			if (wave_count == 1) {
				for (unsigned int i = 0; i < size(wave1.Enemies); i++) {
					if (wave1.Enemies[i].isActive()) {
						window.draw(wave1.Enemies[i].sprite);
					}
					// continues drawing shot when enemy died
				}
				for (unsigned int i = 0; i < size(wave1.Enemies); i++) {
					window.draw(wave1.Enemies[i].spriteShot);
					for (unsigned int j = 0; j < size(wave1.Enemies[i].shotsGrunt); j++) {
						window.draw(wave1.Enemies[i].shotsGrunt[j]);
					}
				}
			}

			if (wave_count == 2) {
				for (unsigned int i = 0; i < size(wave2.Enemies); i++) {
					if (wave2.Enemies[i].isActive()) {
						window.draw(wave2.Enemies[i].sprite);
					}
					// continues drawing shot when enemy died
				}
				for (unsigned int i = 0; i < size(wave2.Enemies); i++) {
					window.draw(wave2.Enemies[i].spriteShot);
				}
			}

			if (wave_count == 3) {
				for (unsigned int i = 0; i < size(wave3.Enemies); i++) {
					if (wave3.Enemies[i].isActive()) {
						window.draw(wave3.Enemies[i].sprite);
					}
					// continues drawing shot when enemy died
				}
				for (unsigned int i = 0; i < size(wave3.Enemies); i++) {
					window.draw(wave3.Enemies[i].spriteShot);
				}
			}

			if (wave_count == 4) {
				for (unsigned int i = 0; i < size(wave4.Enemies); i++) {
					if (wave4.Enemies[i].isActive()) {
						window.draw(wave4.Enemies[i].sprite);
					}
					// continues drawing shot when enemy died
				}
				for (unsigned int i = 0; i < size(wave4.Enemies); i++) {
					window.draw(wave4.Enemies[i].spriteShot);
				}
			}

			if (wave_count == 5) {
				for (unsigned int i = 0; i < size(wave5.Enemies); i++) {
					if (wave5.Enemies[i].isActive()) {
						window.draw(wave5.Enemies[i].sprite);
					}
					// continues drawing shot when enemy died
				}
				for (unsigned int i = 0; i < size(wave5.Enemies); i++) {
					window.draw(wave5.Enemies[i].spriteShot);
				}
			}

			if (wave_count == 6) {
				for (unsigned int i = 0; i < size(wave6.Enemies); i++) {
					if (wave6.Enemies[i].isActive()) {
						window.draw(wave6.Enemies[i].sprite);
					}
					// continues drawing shot when enemy died
				}
				for (unsigned int i = 0; i < size(wave6.Enemies); i++) {
					window.draw(wave6.Enemies[i].spriteShot);
				}
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
				if (buttonSound.isOff())
					window.draw(buttonSound.spriteButtonOff);
				else if (buttonSound.isOn())
					window.draw(buttonSound.spriteButtonOn);
				if (buttonAbout.isOff())
					window.draw(buttonAbout.spriteButtonOff);
				else if (buttonAbout.isOn())
					window.draw(buttonAbout.spriteButtonOn);

				window.draw(buttonExit.text);
				if (stop_music == false)
					window.draw(buttonSound.text);
				else if (stop_music == true)
					window.draw(buttonSoundOn.text);

				window.draw(buttonAbout.text);
			}

			// PAUSE SCREENS with WAVE nr. information
			
			if (round_cleared && !hit && !game_over) {
				timePassed_roundCleared += deltaTime;
				if (timePassed_roundCleared >= 2.0f) {
					messageRoundOver.display(window);
					if (timePassed_roundCleared >= 4.0f) {
						round_cleared = false;
						pause = true;
						timePassed_roundCleared = 0.0f;
					}
				}
			}
			
			if (player.isWinner() && !hit && !game_over) {
				// stops the main melody
				soundMain.stop();

				timePassed_winner += deltaTime;
				if (timePassed_winner >= 3.0f && timePassed_winner < 5.0f) {
					messageGlory.display(window);
				}
				else if (timePassed_winner >= 5.0f) {
					messageVictory.display(window);
					winScreen = true;		// permits the final animation to be drawn in line 644, section UPDATE
					//if (timePassed_winner >= 8.0f) {
					//	window.close();
					//}
				}
			}

			if (pause) {
				timePassed_pause += deltaTime;
				if (timePassed_pause >= 2.0f) {
					messageWave.display(window);
				}
				if (timePassed_pause >= 4.0f) {
					messageGetReady.display(window);
				}
				if (timePassed_pause >= 6.5f) {
					timePassed_pause = 0.0f;
					pause = false;
				}
			}

			if (game_over) {
				messageGameOver.display(window);
			}

		} // end of DRAW -- if (!intro)

		window.display();

	} // end of while(window.isOpen())

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