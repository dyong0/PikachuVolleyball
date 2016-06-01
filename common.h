#pragma once

namespace common{
	enum Key{
		KEY_INVALID = -1,
		KEY_UP = 72, KEY_DOWN = 80, KEY_LEFT = 75, KEY_RIGHT = 77,
		KEY_ENTER = 13
	};

	enum Direction{
		DIRECTION_LEFT = 1,
		DIRECTION_RIGHT = 2
	};

	typedef struct _Position{
		_Position(float x, float y) :x(x), y(y) {}

		float x;
		float y;

	} Position;
}