#include "stdafx.h"
#include "Player.h"

using namespace common;

const float Player::DEFAULT_SPEED_X = 5.0f;
const float Player::DEFAULT_SPEED_Y = -0.5f;
const float Player::LEFT_PLAYER_START_POSITION_X = 0;
const float Player::LEFT_PLAYER_START_POSITION_Y = 0;
const float Player::RIGHT_PLAYER_START_POSITION_X = 600;
const float Player::RIGHT_PLAYER_START_POSITION_Y = 0;

Player::Player(Direction direction) : state(STATE_STANDING), direction(direction), x(0.0f), y(0.0f), speedX(0.0f), speedY(0.0f)
{
}

Player::~Player()
{
}

Position* Player::getPosition(){
	return new Position(this->x, this->y);
}

void Player::jump(){
	if (this->state == STATE_STANDING || this->state == STATE_WALKING){
		this->state = STATE_JUMPING;
	}
}

void Player::slide(){
	if (this->state == STATE_STANDING || this->state == STATE_WALKING){
		this->state = STATE_SLIDING;
	}
}

void Player::setPosition(float x, float y){
	this->x = x;
	this->y = y;
}

void Player::update(float deltaFrame){
	this->setPosition(this->x + this->speedX * deltaFrame, this->y + this->speedY * deltaFrame);
}

void Player::walkLeft(){
	this->speedX = -this->DEFAULT_SPEED_X;
}

void Player::walkRight(){
	this->speedX = this->DEFAULT_SPEED_X;
}

void Player::stopWalking(){
	this->speedX = 0;
}