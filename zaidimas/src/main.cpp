#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Objects.h"
#include "Defines.h"

#include <fstream>
#include <string>
#include <iostream>

using namespace sf;
using namespace std;


int main()
{
	ofstream fout("d.txt");
	RenderWindow app(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");
	app.setFramerateLimit(60);

	Texture tPlayer, tBackground, tLuckybox, tRedMushroom;
	tPlayer.loadFromFile("resources/sprite.png");
	tBackground.loadFromFile("resources/background.png");
	tLuckybox.loadFromFile("resources/luckybox.png");
	tRedMushroom.loadFromFile("resources/mushroom.png");

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
	sprPlayer.setTextureRect(IntRect(0, 0, 70, 70));
	
	Player player;
	player.x = 0;
	player.y = GROUND_LEVEL;
	
	Map map;
	map.x = 0;
	map.y = 0;

	Luckybox luckybox;
	luckybox.x = LUCKYBOX_FIRST_POSITION;
	luckybox.y = 655;
	sprLuckybox.setPosition(luckybox.x, luckybox.y);
	
	Mushroom redMushroom;
	redMushroom.x = LUCKYBOX_FIRST_POSITION;
	redMushroom.y = GROUND_LEVEL;
	sprRedMushroom.setPosition(redMushroom.x, redMushroom.y);
	float currentFrame = 0;
	int coinsBalance = 0;
	bool state = 1;
	srand(time(0));

	while (app.isOpen())
	{
		Event e;
		
		FloatRect playerBounds = sprPlayer.getGlobalBounds();
		FloatRect luckyboxBounds = sprLuckybox.getGlobalBounds();	// Kolizijos
		FloatRect redMushroomBounds = sprRedMushroom.getGlobalBounds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (player.x <= WINDOW_WIDTH / 2 || map.x >= 0) 
			player.x -= 5;
			currentFrame += 0.12f;
			if (currentFrame > 9)		
				currentFrame -= 9;
			sprPlayer.setTextureRect(IntRect(80 * int(currentFrame)+70, 0, -70, 70)); // Atvirkstine animacija

			if (player.x > WINDOW_WIDTH / 2 && map.x < 0) {
				map.x += 5;
				luckybox.x += 5;
				redMushroom.x += 5;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (player.x <= WINDOW_WIDTH / 2)
				player.x += 5;

			currentFrame += 0.12f;

			if (currentFrame > 9)
				currentFrame -= 9;
			sprPlayer.setTextureRect(IntRect(80 * int(currentFrame), 0, 70, 70)); // Animacija

			if (player.x > WINDOW_WIDTH / 2 && map.x <= MAP_WIDTH - WINDOW_WIDTH / 2) {
				map.x -= 5;
				luckybox.x -= 5;
				redMushroom.x -= 5;
			}
		}
		
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && player.y >= GROUND_LEVEL)
		{
				player.y -= JUMP_HEIGHT;
		}

		if (player.y <= GROUND_LEVEL)
			player.y += 2;					// Griuvimas
		
		if (player.x <= 0 && map.x >= 0)
			player.x = 0;			// Kairinio kampo barjeras

		if (playerBounds.intersects(luckyboxBounds)) {
			coinsBalance += 1 + rand() % 5;		// Luckybox'u logika
			luckybox.x += 1600;
		}

		
		if (state) {
			redMushroom.x -= 1.5f;
			if (redMushroom.x <= LUCKYBOX_FIRST_POSITION + map.x - 300) 
				state = 0;
		}																		//Grybo judejimas aplink vieno tasko
		if (!state) {
			redMushroom.x += 1.5f;
			if (redMushroom.x > LUCKYBOX_FIRST_POSITION + map.x + 300)
				state = 1;
		}
		

		if (playerBounds.intersects(redMushroomBounds)) {
			app.close();									// zaidimo pasibaigimas
		}

		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		app.clear();

		sprBackground.setPosition(map.x, map.y);
		app.draw(sprBackground);

		sprLuckybox.setPosition(luckybox.x, luckybox.y);
		app.draw(sprLuckybox);

		sprRedMushroom.setPosition(redMushroom.x, redMushroom.y);
		app.draw(sprRedMushroom);

		sprPlayer.setPosition(player.x, player.y);
		app.draw(sprPlayer);
 
		string strCoins = "Coins: " + to_string((int)coinsBalance);
		text.setString(strCoins);
		app.draw(text);

		app.display();
	}
	return 0;
}
