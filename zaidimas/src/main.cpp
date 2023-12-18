#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Objects.h"
#include "Defines.h"

using namespace sf;
using namespace std;

int main()
{
	RenderWindow app(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");
	app.setFramerateLimit(60);

	Texture tPlayer, tBackground;

	tPlayer.loadFromFile("resources/sprite.png");
	tBackground.loadFromFile("resources/background.png");

	Sprite sprPlayer(tPlayer);
	Sprite sprBackground(tBackground);

	sprPlayer.setTextureRect(IntRect(0, 0, 70, 70));
	

	Player player;
	player.x = 0;
	player.y = GROUND_LEVEL;
	
	Map map;
	map.x = 0;
	map.y = -325;
	float currentFrame = 0;
	sprBackground.setPosition(map.x, map.y);
	while (app.isOpen())
	{
		Event e;
		bool onGround;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (player.x <= WINDOW_WIDTH / 2 || map.x >= 0) 
			player.x -= 4;
			currentFrame += 0.12f;
			if (currentFrame > 9)
				currentFrame -= 9;
			sprPlayer.setTextureRect(IntRect(80 * int(currentFrame)+70, 0, -70, 70));

			if (player.x > WINDOW_WIDTH / 2 && map.x < 0) {
				map.x += 4;
				
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (player.x <= WINDOW_WIDTH / 2)
				player.x += 4;

			currentFrame += 0.12f;

			if (currentFrame > 9)
				currentFrame -= 9;

			sprPlayer.setTextureRect(IntRect(80 * int(currentFrame), 0, 70, 70));

			if (player.x > WINDOW_WIDTH / 2) {
				map.x -= 4;
				
			}
		}
		
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && player.y >= GROUND_LEVEL)
		{
				player.y -= 120;
		}

		if (player.y <= GROUND_LEVEL)
			player.y += 2;					// Griuvimas
		
		if (player.x <= 0 && map.x >= 0)
			player.x = 0;			// Kairinio kampo barjeras


		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}
		
		app.clear();
		sprBackground.setPosition(map.x, map.y);
		app.draw(sprBackground);
		sprPlayer.setPosition(player.x, player.y);
		app.draw(sprPlayer);
		app.display();
	}
	return 0;
}
