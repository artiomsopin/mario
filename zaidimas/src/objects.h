#pragma once
#include "Defines.h"


class Movement {
public:
	virtual void moveByY(float y) = 0;

	virtual void moveByX(float x) = 0;

	virtual float getX() const = 0;

	virtual float getY() const = 0;
};

class Player : Movement
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

class Map : Movement
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

class Luckybox : Movement
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

class Mushroom : Movement
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

class Escape : Movement
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
