#pragma once

#include "Defines.h"


struct Player
{
	float LegsStartX() { return x + 24; }

	float LegsEndX() { return x + 64; }

	float LegsY() { return y + 73; }

	float x, y;
};