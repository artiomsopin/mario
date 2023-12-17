#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Objects.h"
#include "Utils.h"

using namespace sf;
using namespace std;

int main()
{
	RenderWindow app(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");
	app.setFramerateLimit(60);


	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}
		app.clear();
		app.display();
	}

	return 0;
}
