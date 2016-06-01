#pragma once
#include "Player.h"
class UserPlayer :
	public Player
{
public:
	UserPlayer(common::Direction direction);
	~UserPlayer();
};
