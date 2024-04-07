#pragma once
#include "Defines.h"


class Player
{
private:
	float x;
	float y;
public:
	Player(float x, float y) :
		x(x),
		y(y) {}

	void moveByY(float y) {
		this->y += y;
	};

	void moveByX(float x) {
		this->x += x;
	}

	float getX() {
		return this->x;
	}

	float getY() {
		return this->y;
	}

};

struct Map
{
private:
	float x;
	float y;
public:
	Map(float x, float y) :
		x(x),
		y(y) {}

	void moveByY(float y) {
		this->y += y;
	};

	void moveByX(float x) {
		this->x += x;
	}

	float getX() {
		return this->x;
	}

	float getY() {
		return this->y;
	}

};

struct Luckybox
{
private:
	float x;
	float y;
public:
	Luckybox(float x, float y) :
		x(x),
		y(y) {}

	void moveByY(float y) {
		this->y += y;
	};

	void moveByX(float x) {
		this->x += x;
	}

	float getX() {
		return this->x;
	}

	float getY() {
		return this->y;
	}
};

struct Mushroom
{
private:
	float x;
	float y;
public:
	Mushroom(float x, float y) :
		x(x),
		y(y) {}

	void moveByY(float y) {
		this->y += y;
	};

	void moveByX(float x) {
		this->x += x;
	}

	float getX() {
		return this->x;
	}

	float getY() {
		return this->y;
	}
};

struct Escape
{
private:
	float x;
	float y;
public:
	Escape(float x, float y) :
		x(x),
		y(y) {}

	void moveByY(float y) {
		this->y += y;
	};

	void moveByX(float x) {
		this->x += x;
	}

	float getX() {
		return this->x;
	}

	float getY() {
		return this->y;
	}
};