#pragma once
#include "Player.h"
class AIPlayer :
	public Player
{
public:
	AIPlayer(common::Direction direction);
	~AIPlayer();
};
