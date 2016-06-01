#include "stdafx.h"
#include "IngameView.h"

#include "common.h"
#include "Game.h"
#include "Player.h"

using namespace common;

const string IngameView::INGAME_VIEW = "ingame_view";

IngameView::IngameView(Game* game) :GameView(game), lastKey(KEY_INVALID)
{
}


IngameView::~IngameView()
{
}

void IngameView::processKey(int key){
	Player* leftPlayer = this->game->getPlayer(0);
	Player* rightPlayer = this->game->getPlayer(1);

	switch (key){
	case KEY_LEFT:
		leftPlayer->walkLeft();
		break;
	case KEY_RIGHT:
		leftPlayer->walkRight();
		break;
	case KEY_UP:
		leftPlayer->jump();
		break;
	case KEY_ENTER:
		leftPlayer->slide();
		break;
	case KEY_INVALID:
		if (lastKey == KEY_LEFT || lastKey == KEY_RIGHT){
			leftPlayer->stopWalking();
		}
		break;
	}

	this->lastKey = key;
}
