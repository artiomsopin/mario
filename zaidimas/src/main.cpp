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

void GameOverMenu(RenderWindow& app, Event& e, Text& text, vector<int>& coinVec, int coinsBalance) {
	ofstream fout("rezults.txt");
	bool menuState = 1;

	while (menuState) {
		Texture tMenu;
		tMenu.loadFromFile("resources/gameover.png");

		Sprite sprMenu(tMenu);
		sprMenu.setPosition(-MENU_FIRST_POSITION, 0);

		sort(coinVec.begin(), coinVec.end());
		string strCoinsInfo = "Total coins: " + to_string((int)coinsBalance) + '\n' + "Max coins: " + to_string(coinVec[2]);

		while (app.pollEvent(e))
		{
			if (
				e.type == Event::Closed 
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) 
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
			) {
				menuState = 0;
				app.close();
				fout << strCoinsInfo;
			}
		}

		text.setPosition(WINDOW_WIDTH / 2 - MENU_SHIFT, MENU_SHIFT);
		text.setString(strCoinsInfo);

		app.draw(sprMenu);
		app.draw(text);

		app.display();
	}
}

int main()
{
	RenderWindow app(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");
	app.setFramerateLimit(FRAMERATE_LIMIT);

	Texture tPlayer, tBackground, tLuckybox, tRedMushroom, tPurpleMushroom, tGreenMushroom, tEscape;
	tPlayer.loadFromFile("resources/sprite.png");
	tBackground.loadFromFile("resources/background.png");
	tLuckybox.loadFromFile("resources/luckybox.png");
	tRedMushroom.loadFromFile("resources/redmushroom.png");
	tPurpleMushroom.loadFromFile("resources/purplemushroom.png");
	tGreenMushroom.loadFromFile("resources/greenmushroom.png");
	tEscape.loadFromFile("resources/escape.png");

	Font font;
	font.loadFromFile("resources/arialbd.ttf");

	Text text;
	text.setFont(font);
	text.setString("0");
	text.setCharacterSize(FONT_SIZE);
	text.setFillColor(Color::Yellow);
	text.setOutlineThickness(FONT_OUTLINE_THICKNESS);
	text.setOutlineColor(Color::Black);
	text.setPosition(WINDOW_WIDTH / 2 - TEXT_SHIFT, TEXT_Y_POSITION);

	Sprite sprPlayer(tPlayer);
	Sprite sprBackground(tBackground);
	Sprite sprLuckybox(tLuckybox);
	Sprite sprRedMushroom(tRedMushroom);
	Sprite sprPurpleMushroom(tPurpleMushroom);
	Sprite sprGreenMushroom(tGreenMushroom);
	Sprite sprEscape(tEscape);

	sprPlayer.setTextureRect(IntRect(0, RECT_TOP, RECT_WIDTH, RECT_HEIGHT));
	
	Player player(FIRST_PLAYER_POSITION, GROUND_LEVEL);
	
	Map map(0,0);

	Luckybox luckybox(LUCKYBOX_FIRST_POSITION_X, LUCKYBOX_FIRST_POSITION_Y);
	sprLuckybox.setPosition(luckybox.getX(), luckybox.getY());
	
	Mushroom redMushroom(LUCKYBOX_FIRST_POSITION_X, GROUND_LEVEL);
	sprRedMushroom.setPosition(redMushroom.getX(), redMushroom.getY());

	Mushroom purpleMushroom(LUCKYBOX_FIRST_POSITION_X + LUCKYBOX_NEW_POSITION, GROUND_LEVEL);
	sprPurpleMushroom.setPosition(purpleMushroom.getX(), purpleMushroom.getY());

	Mushroom greenMushroom(LUCKYBOX_FIRST_POSITION_X + LUCKYBOX_NEW_POSITION * 2, GROUND_LEVEL);
	sprGreenMushroom.setPosition(greenMushroom.getX(), greenMushroom.getY());
	
	Escape escape(MAP_WIDTH - ESCAPE_SHIFT_BY_X, GROUND_LEVEL - ESCAPE_SHIFT_BY_Y);
	sprEscape.setPosition(escape.getX(), escape.getY());

	float currentFrame = 0;
	int coinsBalance = 0;
	vector <int> coinVec(COIN_VECTOR_SIZE);
	int coinIter = 0;
	bool mushrooomMovementState = 1;

	srand(time(0));

	while (app.isOpen())
	{
		Event e;

		// Kolizijos
		FloatRect playerBounds = sprPlayer.getGlobalBounds();
		FloatRect luckyboxBounds = sprLuckybox.getGlobalBounds();				
		FloatRect redMushroomBounds = sprRedMushroom.getGlobalBounds();					
		FloatRect purpleMushroomBounds = sprPurpleMushroom.getGlobalBounds();
		FloatRect greenMushroomBounds = sprGreenMushroom.getGlobalBounds();
		FloatRect escapeBounds = sprEscape.getGlobalBounds();

		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{
			// Atvirkstine animacija
			if (player.getX() <= WINDOW_WIDTH / 2 || map.getX() >= 0)
			player.moveByX(-5);

			currentFrame += ANIMATION_SHIFT;

			if (currentFrame > ANIMATION_FRAMES_COUNT)
				currentFrame -= ANIMATION_FRAMES_COUNT;

			sprPlayer.setTextureRect(
				IntRect(
					RECT_LEFT * int(currentFrame) + RECT_WIDTH, 
					RECT_TOP, 
					-RECT_WIDTH, 
					RECT_HEIGHT
				)
			); 

			if (player.getX() > WINDOW_WIDTH / 2 && map.getX() < 0) {
				map.moveByX(5);
				luckybox.moveByX(5);
				redMushroom.moveByX(5);
				purpleMushroom.moveByX(5);
				greenMushroom.moveByX(5);
				escape.moveByX(5);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (player.getX() <= WINDOW_WIDTH / 2)
				player.moveByX(5);

			currentFrame += ANIMATION_SHIFT;

			// Animacija
			if (currentFrame > ANIMATION_FRAMES_COUNT)
				currentFrame -= ANIMATION_FRAMES_COUNT;
			sprPlayer.setTextureRect(IntRect(RECT_LEFT * int(currentFrame), RECT_TOP, RECT_WIDTH, RECT_HEIGHT)); 

			if (player.getX() > WINDOW_WIDTH / 2 && map.getY() <= MAP_WIDTH - WINDOW_WIDTH / 2) {
				map.moveByX(-5);
				luckybox.moveByX(-5);
				redMushroom.moveByX(-5);
				purpleMushroom.moveByX(-5);
				greenMushroom.moveByX(-5);
				escape.moveByX(-5);
			}
		}
		
		if (
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) 
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Space) 
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
			&& player.getY() >= GROUND_LEVEL
		)
		{
				player.moveByY(-JUMP_HEIGHT);
		}

		// Griuvimas
		if (player.getY() <= GROUND_LEVEL)
			player.moveByY(FALLING_SPEED);					
		
		// Kairinio kampo barjeras
		if ( ((player.getX()) <= 0) && ((map.getX()) >= 0) )
			player.moveByX(-player.getX());						

		// Luckybox'u logika
		if (playerBounds.intersects(luckyboxBounds)) {
			int temp = 1 + rand() % COIN_MAX_RANDOM_COUNT;
			coinsBalance += temp;
			coinVec[coinIter] = temp;				
			coinIter++;
			luckybox.moveByX(LUCKYBOX_NEW_POSITION);
		}

		// Grybo judejimas aplink vieno tasko
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

		// Zaidimo pasibaigimas
		if (
			playerBounds.intersects(redMushroomBounds) || 
			playerBounds.intersects(purpleMushroomBounds) || 
			playerBounds.intersects(greenMushroomBounds) ||      
			playerBounds.intersects(escapeBounds) 
		) 
		{   
			GameOverMenu(app, e, text, coinVec, coinsBalance);
		}
		
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed) {
				app.close();
			}
		}

		app.clear();

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
		
		// Monetu apskaiciavimas
		string strCoins = "Coins: " + to_string((int)coinsBalance);
		text.setString(strCoins);
		app.draw(text);

		app.display();
	}
	return 0;
}
