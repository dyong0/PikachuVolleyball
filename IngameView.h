#pragma once
#include "GameView.h"
class IngameView :
	public GameView
{
public:
	static const std::string INGAME_VIEW;

	IngameView(Game* game);
	~IngameView();

	void processKey(int key);

private :
	int lastKey;
};