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

	Texture tPlayer;
	tPlayer.loadFromFile("resources/sprite.png");

	Sprite sprPlayer(tPlayer);
	sprPlayer.setTextureRect(IntRect(0, 0, 70, 70));

	Player player;
	player.x = 0;
	player.y = GROUND_LEVEL;
	
	float currentFrame = 0;

	while (app.isOpen())
	{
		Event e;
		bool onGround;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player.x -= 3.5f;
			currentFrame += 0.12;
			if (currentFrame > 9)
				currentFrame -= 9;
			sprPlayer.setTextureRect(IntRect(80 * int(currentFrame)+70, 0, -70, 70));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player.x += 3.5f;
			currentFrame += 0.12;
			if (currentFrame > 9)
				currentFrame -= 9;
			sprPlayer.setTextureRect(IntRect(80 * int(currentFrame), 0, 70, 70));
		}
		
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && player.y >= GROUND_LEVEL)
			{
				for (int i = 0; i < 4; i++)
				{
					player.y -= 30;
				}
			}
		if (player.y <= GROUND_LEVEL) {
			player.y += 2;					// Griuvimas
		}
		

		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		app.clear();
		sprPlayer.setPosition(player.x, player.y);
		app.draw(sprPlayer);
		app.display();
	}

	return 0;
}
