#pragma once

#include "common.h"

class Player
{
public:
	enum State{
		STATE_STANDING = 1,
		STATE_WALKING = 2,
		STATE_JUMPING = 3,
		STATE_SLIDING = 4
	};

	static const float DEFAULT_SPEED_X;
	static const float DEFAULT_SPEED_Y;
	static const float LEFT_PLAYER_START_POSITION_X;
	static const float LEFT_PLAYER_START_POSITION_Y;
	static const float RIGHT_PLAYER_START_POSITION_X;
	static const float RIGHT_PLAYER_START_POSITION_Y;

	Player(common::Direction direction);
	~Player();

	common::Position* getPosition();
	void setPosition(float x, float y);
	void update(float deltaFrame);

	void jump();
	void slide();
	void walkLeft();
	void walkRight();
	void stopWalking();

private :
	common::Direction direction;
	State state;
	float x;
	float y;
	float speedX;
	float speedY;

	
};