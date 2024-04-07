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
		sprMenu.setPosition(-100, 0);
		sort(coinVec.begin(), coinVec.end());
		string strCoinsInfo = "Total coins: " + to_string((int)coinsBalance) + '\n' + "Max coins: " + to_string(coinVec[2]);
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				menuState = 0;
				app.close();
				fout << strCoinsInfo;
			}
		}
		text.setPosition(WINDOW_WIDTH / 2 - 300, 300);
		text.setString(strCoinsInfo);
		app.draw(sprMenu);
		app.draw(text);
		app.display();
	}
}

int main()
{
	RenderWindow app(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");
	app.setFramerateLimit(60);

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
	text.setCharacterSize(80);
	text.setFillColor(Color::Yellow);
	text.setOutlineThickness(3);
	text.setOutlineColor(Color::Black);
	text.setPosition(WINDOW_WIDTH / 2 - 140, 50);

	Sprite sprPlayer(tPlayer);
	Sprite sprBackground(tBackground);
	Sprite sprLuckybox(tLuckybox);
	Sprite sprRedMushroom(tRedMushroom);
	Sprite sprPurpleMushroom(tPurpleMushroom);
	Sprite sprGreenMushroom(tGreenMushroom);
	Sprite sprEscape(tEscape);

	sprPlayer.setTextureRect(IntRect(0, 0, 70, 70));
	
	Player player(FIRST_PLAYER_POSITION, GROUND_LEVEL);
	
	Map map(0,0);

	Luckybox luckybox(LUCKYBOX_FIRST_POSITION, 655);
	sprLuckybox.setPosition(luckybox.getX(), luckybox.getY());
	
	Mushroom redMushroom(LUCKYBOX_FIRST_POSITION, GROUND_LEVEL);
	sprRedMushroom.setPosition(redMushroom.getX(), redMushroom.getY());

	Mushroom purpleMushroom(LUCKYBOX_FIRST_POSITION + LUCKYBOX_NEW_POSITION, GROUND_LEVEL);
	sprPurpleMushroom.setPosition(purpleMushroom.getX(), purpleMushroom.getY());

	Mushroom greenMushroom(LUCKYBOX_FIRST_POSITION + LUCKYBOX_NEW_POSITION * 2, GROUND_LEVEL);
	sprGreenMushroom.setPosition(greenMushroom.getX(), greenMushroom.getY());
	
	Escape escape(MAP_WIDTH - 150, GROUND_LEVEL - 100);
	sprEscape.setPosition(escape.getX(), escape.getY());

	float currentFrame = 0;
	int coinsBalance = 0;
	vector <int> coinVec(3);
	int coinIter = 0;
	bool mushrooomMovementState = 1;

	srand(time(0));

	while (app.isOpen())
	{
		Event e;
		
		FloatRect playerBounds = sprPlayer.getGlobalBounds();
		FloatRect luckyboxBounds = sprLuckybox.getGlobalBounds();				
		FloatRect redMushroomBounds = sprRedMushroom.getGlobalBounds();					// Kolizijos
		FloatRect purpleMushroomBounds = sprPurpleMushroom.getGlobalBounds();
		FloatRect greenMushroomBounds = sprGreenMushroom.getGlobalBounds();
		FloatRect escapeBounds = sprEscape.getGlobalBounds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (player.getX() <= WINDOW_WIDTH / 2 || map.getX() >= 0)
			player.moveByX(-5);
			currentFrame += 0.12f;
			if (currentFrame > 9)		
				currentFrame -= 9;
			sprPlayer.setTextureRect(IntRect(RECT_LEFT * int(currentFrame) + RECT_WIDTH, RECT_TOP, -RECT_WIDTH, RECT_HEIGHT)); // Atvirkstine animacija

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

			currentFrame += 0.12f;

			if (currentFrame > 9)
				currentFrame -= 9;
			sprPlayer.setTextureRect(IntRect(RECT_LEFT * int(currentFrame), RECT_TOP, RECT_WIDTH, RECT_HEIGHT)); // Animacija

			if (player.getX() > WINDOW_WIDTH / 2 && map.getY() <= MAP_WIDTH - WINDOW_WIDTH / 2) {
				map.moveByX(-5);
				luckybox.moveByX(-5);
				redMushroom.moveByX(-5);
				purpleMushroom.moveByX(-5);
				greenMushroom.moveByX(-5);
				escape.moveByX(-5);
			}
		}
		
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && player.getY() >= GROUND_LEVEL)
		{
				player.moveByY(-JUMP_HEIGHT);
		}

		if (player.getY() <= GROUND_LEVEL)
			player.moveByY(2);					// Griuvimas
		
		if ( ((player.getX()) <= 0) && ((map.getX()) >= 0) )
			player.moveByX(-player.getX());						// Kairinio kampo barjeras

		if (playerBounds.intersects(luckyboxBounds)) {
			int temp = 1 + rand() % 5;		
			coinsBalance += temp;
			coinVec[coinIter] = temp;				// Luckybox'u logika
			coinIter++;
			luckybox.moveByX(LUCKYBOX_NEW_POSITION);
		}

		
		if (mushrooomMovementState) {
			redMushroom.moveByX(-1.5f);
			purpleMushroom.moveByX(-1.5f);
			greenMushroom.moveByX(-1.5f);
			if (redMushroom.getX() <= LUCKYBOX_FIRST_POSITION + map.getX() - MUSHROOM_POSITION_BIAS)
				mushrooomMovementState = 0;
		}																		//Grybo judejimas aplink vieno tasko
		if (!mushrooomMovementState) {
			redMushroom.moveByX(1.5f);
			purpleMushroom.moveByX(1.5f);
			greenMushroom.moveByX(1.5f);
			if (redMushroom.getX() > LUCKYBOX_FIRST_POSITION + map.getX() + MUSHROOM_POSITION_BIAS)
				mushrooomMovementState = 1;
		}
		
		if (playerBounds.intersects(redMushroomBounds) || 
			playerBounds.intersects(purpleMushroomBounds) || 
			playerBounds.intersects(greenMushroomBounds) ||      // zaidimo pasibaigimas
			playerBounds.intersects(escapeBounds) ) 
		{   
			GameOverMenu(app, e, text, coinVec, coinsBalance);
		}
		
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
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
 
		string strCoins = "Coins: " + to_string((int)coinsBalance);
		text.setString(strCoins);
		app.draw(text);

		app.display();
	}
	return 0;
}
