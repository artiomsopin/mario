#pragma once
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

class LocalObjectMovement {
public:
	virtual void moveByY(float y) = 0;

	virtual void moveByX(float x) = 0;

	virtual float getX() const = 0;

	virtual float getY() const = 0;
};

class Player : LocalObjectMovement
{
private:
	float x;
	float y;
public:
	Player(float x, float y) : x(x), y(y) {}

	void moveByY(float y) override {
		this->y += y;
	};

	void moveByX(float x) override {
		this->x += x;
	}

	float getX() const override {
		return this->x;
	}

	float getY() const override {
		return this->y;
	}
};

class Map : LocalObjectMovement
{
private:
	float x;
	float y;
public:
	Map(float x, float y) :
		x(x),
		y(y) {}

	void moveByY(float y) override {
		this->y += y;
	};

	void moveByX(float x) override {
		this->x += x;
	}

	float getX() const override {
		return this->x;
	}

	float getY() const override {
		return this->y;
	}

};

class Luckybox : LocalObjectMovement
{
private:
	float x;
	float y;
public:
	Luckybox(float x, float y) :
		x(x),
		y(y) {}

	void moveByY(float y) override {
		this->y += y;
	};

	void moveByX(float x) override {
		this->x += x;
	}

	float getX() const override {
		return this->x;
	}

	float getY() const override {
		return this->y;
	}
};

class Mushroom : LocalObjectMovement
{
private:
	float x;
	float y;
public:
	Mushroom(float x, float y) :
		x(x),
		y(y) {}

	void moveByY(float y) override {
		this->y += y;
	};

	void moveByX(float x) override {
		this->x += x;
	}

	float getX() const override {
		return this->x;
	}

	float getY() const override {
		return this->y;
	}
};

class Escape : LocalObjectMovement
{
private:
	float x;
	float y;
public:
	Escape(float x, float y) :
		x(x),
		y(y) {}

	void moveByY(float y) override {
		this->y += y;
	};

	void moveByX(float x) override {
		this->x += x;
	}

	float getX() const override {
		return this->x;
	}

	float getY() const override {
		return this->y;
	}
};

class GameOverMenu
{
	public:
		static void menuInit(RenderWindow& app, Event& e, Text& text, vector<int>& coinVec, int coinsBalance) {
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
					|| Keyboard::isKeyPressed(Keyboard::Enter)
					|| Keyboard::isKeyPressed(Keyboard::Escape)
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
};
