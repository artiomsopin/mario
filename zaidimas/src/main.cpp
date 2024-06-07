#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Objects.h"
#include "Defines.h"

#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace sf;
using namespace std;

int main()
{
	RenderWindow app(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");
	app.setFramerateLimit(FRAMERATE_LIMIT);

	// Textures
	Texture tPlayer, tBackground, tLuckybox, tRedMushroom, tPurpleMushroom, tGreenMushroom, tEscape;
	tPlayer.loadFromFile("resources/sprite.png");
	tBackground.loadFromFile("resources/background.png");
	tLuckybox.loadFromFile("resources/luckybox.png");
	tRedMushroom.loadFromFile("resources/redmushroom.png");
	tPurpleMushroom.loadFromFile("resources/purplemushroom.png");
	tGreenMushroom.loadFromFile("resources/greenmushroom.png");
	tEscape.loadFromFile("resources/escape.png");
	
	//Fonts
	Font font;
	font.loadFromFile("resources/arialbd.ttf");

	// Texts
	Text text;
	text.setFont(font);
	text.setString("0");
	text.setCharacterSize(FONT_SIZE);
	text.setFillColor(Color::Yellow);
	text.setOutlineThickness(FONT_OUTLINE_THICKNESS);
	text.setOutlineColor(Color::Black);
	text.setPosition(WINDOW_WIDTH / 2 - TEXT_SHIFT, TEXT_Y_POSITION);

	// Sprites
	Sprite sprPlayer(tPlayer);
	Sprite sprBackground(tBackground);
	Sprite sprLuckybox(tLuckybox);
	Sprite sprRedMushroom(tRedMushroom);
	Sprite sprPurpleMushroom(tPurpleMushroom);
	Sprite sprGreenMushroom(tGreenMushroom);
	Sprite sprEscape(tEscape);

	// Set player animation texture
	sprPlayer.setTextureRect(
		IntRect(OBJECT_INIT_POSITION, 
			RECT_TOP, 
			RECT_WIDTH, 
			RECT_HEIGHT)
	);
	
	// Define player position
	Player player(FIRST_PLAYER_POSITION, GROUND_LEVEL);
	
	// Define map position
	Map map(OBJECT_INIT_POSITION, OBJECT_INIT_POSITION);

	// Define luckyboxes positions
	Luckybox luckybox(LUCKYBOX_FIRST_POSITION_X, LUCKYBOX_FIRST_POSITION_Y);
	sprLuckybox.setPosition(luckybox.getX(), luckybox.getY());
	
	// Define mushrooms and positions
	Mushroom redMushroom(LUCKYBOX_FIRST_POSITION_X, GROUND_LEVEL);
	sprRedMushroom.setPosition(redMushroom.getX(), redMushroom.getY());

	Mushroom purpleMushroom(LUCKYBOX_FIRST_POSITION_X + LUCKYBOX_NEW_POSITION, GROUND_LEVEL);
	sprPurpleMushroom.setPosition(purpleMushroom.getX(), purpleMushroom.getY());

	Mushroom greenMushroom(LUCKYBOX_FIRST_POSITION_X + LUCKYBOX_NEW_POSITION * 2, GROUND_LEVEL);
	sprGreenMushroom.setPosition(greenMushroom.getX(), greenMushroom.getY());
	
	// Define escape position
	Escape escape(MAP_WIDTH - ESCAPE_SHIFT_BY_X, GROUND_LEVEL - ESCAPE_SHIFT_BY_Y);
	sprEscape.setPosition(escape.getX(), escape.getY());

	// Define helping variables
	float currentPlayerAnimationFrame = 0;
	int coinsBalance = 0;
	vector <int> coinVec(COIN_VECTOR_SIZE);
	int coinIterator = 0;
	bool mushrooomMovementState = 1;

	srand(time(0));

	// Game start
	while (app.isOpen())
	{
		Event event;

		// Сollisions
		FloatRect playerBounds = sprPlayer.getGlobalBounds();
		FloatRect luckyboxBounds = sprLuckybox.getGlobalBounds();				
		FloatRect redMushroomBounds = sprRedMushroom.getGlobalBounds();					
		FloatRect purpleMushroomBounds = sprPurpleMushroom.getGlobalBounds();
		FloatRect greenMushroomBounds = sprGreenMushroom.getGlobalBounds();
		FloatRect escapeBounds = sprEscape.getGlobalBounds();

		// Left movement logic
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{
			// Reverse animation
			if (player.getX() <= WINDOW_WIDTH / 2 || map.getX() >= 0)
			player.moveByX(-GLOBAL_MOVEMENT_SPEED);

			currentPlayerAnimationFrame += ANIMATION_SHIFT;

			if (currentPlayerAnimationFrame > ANIMATION_FRAMES_COUNT)
				currentPlayerAnimationFrame -= ANIMATION_FRAMES_COUNT;

			sprPlayer.setTextureRect(
				IntRect(
					RECT_LEFT * int(currentPlayerAnimationFrame) + RECT_WIDTH, 
					RECT_TOP, 
					-RECT_WIDTH, 
					RECT_HEIGHT
				)
			); 

			if (player.getX() > WINDOW_WIDTH / 2 && map.getX() < 0) {
				map.moveByX(GLOBAL_MOVEMENT_SPEED);
				luckybox.moveByX(GLOBAL_MOVEMENT_SPEED);
				redMushroom.moveByX(GLOBAL_MOVEMENT_SPEED);
				purpleMushroom.moveByX(GLOBAL_MOVEMENT_SPEED);
				greenMushroom.moveByX(GLOBAL_MOVEMENT_SPEED);
				escape.moveByX(GLOBAL_MOVEMENT_SPEED);
			}
		}

		// Right movement logic
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		{
			if (player.getX() <= WINDOW_WIDTH / 2) {
				player.moveByX(5);
			}

			// Default animation
			currentPlayerAnimationFrame += ANIMATION_SHIFT;

			if (currentPlayerAnimationFrame > ANIMATION_FRAMES_COUNT) {
				currentPlayerAnimationFrame -= ANIMATION_FRAMES_COUNT;
			}
			sprPlayer.setTextureRect(IntRect(RECT_LEFT * int(currentPlayerAnimationFrame), RECT_TOP, RECT_WIDTH, RECT_HEIGHT)); 


			if (player.getX() > WINDOW_WIDTH / 2 && map.getY() <= MAP_WIDTH - WINDOW_WIDTH / 2) {
				map.moveByX(-GLOBAL_MOVEMENT_SPEED);
				luckybox.moveByX(-GLOBAL_MOVEMENT_SPEED);
				redMushroom.moveByX(-GLOBAL_MOVEMENT_SPEED);
				purpleMushroom.moveByX(-GLOBAL_MOVEMENT_SPEED);
				greenMushroom.moveByX(-GLOBAL_MOVEMENT_SPEED);
				escape.moveByX(-GLOBAL_MOVEMENT_SPEED);
			}
		}
		
		if (
			(Keyboard::isKeyPressed(Keyboard::Up) 
			|| Keyboard::isKeyPressed(Keyboard::Space) 
			|| Keyboard::isKeyPressed(Keyboard::W)) 
			&& player.getY() >= GROUND_LEVEL
		)
		{
				player.moveByY(-JUMP_HEIGHT);
		}

		// Falling
		if (player.getY() <= GROUND_LEVEL)
			player.moveByY(FALLING_SPEED);					
		
		// Left corner barrier
		if ( ((player.getX()) <= 0) && ((map.getX()) >= 0) )
			player.moveByX(-player.getX());						

		// Luckyboxes logic
		if (playerBounds.intersects(luckyboxBounds)) {
			int temp = 1 + rand() % COIN_MAX_RANDOM_COUNT;
			coinsBalance += temp;

			coinVec[coinIterator] = temp;				
			coinIterator++;

			luckybox.moveByX(LUCKYBOX_NEW_POSITION);
		}

		// Mushroom movement around one point
		if (mushrooomMovementState) {
			redMushroom.moveByX(-MUSHROOM_MOVEMENT_SPEED);
			purpleMushroom.moveByX(-MUSHROOM_MOVEMENT_SPEED);
			greenMushroom.moveByX(-MUSHROOM_MOVEMENT_SPEED);

			if (redMushroom.getX() <= LUCKYBOX_FIRST_POSITION_X + map.getX() - MUSHROOM_POSITION_BIAS) {
				mushrooomMovementState = 0;
			}
		}																		
		if (!mushrooomMovementState) {
			redMushroom.moveByX(MUSHROOM_MOVEMENT_SPEED);
			purpleMushroom.moveByX(MUSHROOM_MOVEMENT_SPEED);
			greenMushroom.moveByX(MUSHROOM_MOVEMENT_SPEED);

			if (redMushroom.getX() > LUCKYBOX_FIRST_POSITION_X + map.getX() + MUSHROOM_POSITION_BIAS) {
				mushrooomMovementState = 1;
			}
		}

		// Gameover menu initialization
		if (
			playerBounds.intersects(redMushroomBounds) || 
			playerBounds.intersects(purpleMushroomBounds) || 
			playerBounds.intersects(greenMushroomBounds) ||      
			playerBounds.intersects(escapeBounds) 
		) 
		{   
			GameOverMenu::menuInit(app, event, text, coinVec, coinsBalance);
		}
		
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				app.close();
			}
		}

		app.clear();

		// Texture drawing
		sprBackground.setPosition(map.getX(), map.getY());
		app.draw(sprBackground);

		sprLuckybox.setPosition(luckybox.getX(), luckybox.getY());
		app.draw(sprLuckybox);

		sprRedMushroom.setPosition(redMushroom.getX(), redMushroom.getY());
		app.draw(sprRedMushroom);

		sprPurpleMushroom.setPosition(purpleMushroom.getX(), purpleMushroom.getY());
		app.draw(sprPurpleMushroom);

		sprGreenMushroom.setPosition(greenMushroom.getX(), greenMushroom.getY());
		app.draw(sprGreenMushroom);

		sprPlayer.setPosition(player.getX(), player.getY());
		app.draw(sprPlayer);

		sprEscape.setPosition(escape.getX(), escape.getY());
		app.draw(sprEscape);
		
		// Coins calculation
		string strCoins = "Coins: " + to_string((int)coinsBalance);
		text.setString(strCoins);
		app.draw(text);

		app.display();
	}
	
	return 0;
}