#include "MainMenuView.h"
#include "stdafx.h"

#include "common.h"

using namespace std;
using namespace common;

const string MainMenuView::MAIN_MENU_VIEW = "main_menu_view";

MainMenuView::MainMenuView(Game* game) : GameView(game), menu(MENU_FIRST){
};

void MainMenuView::processKey(int key){
	switch (key){
	case KEY_DOWN:
		this->selectMenu((Menu)((int)this->getMenu() + 1));
		break;
	case KEY_UP:
		this->selectMenu((Menu)((int)this->getMenu() - 1));
		break;
	case KEY_ENTER:
		this->runMenu(this->getMenu());
		break;
	}
}

void MainMenuView::registerMenuCallback(Menu menu, MenuCallback callback){
	this->menuCallbacks[menu] = callback;
}

void MainMenuView::selectMenu(Menu menu){
	if (menu > MENU_FIRST && menu <= MENU_LAST){
		this->menu = menu;
	}
}

Menu MainMenuView::getMenu(){
	return this->menu;
}

void MainMenuView::runMenu(Menu menu){
	MenuCallback callback = this->menuCallbacks[menu];
	if (callback == NULL){
		return;
	}

	(game->*callback)();
}