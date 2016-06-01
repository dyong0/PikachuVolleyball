#include <boost/unordered_map.hpp>

#include "GameView.h"

class Game;

typedef void(Game::*MenuCallback)();

enum Menu{
	MENU_PLAY_ALONE = 1,
	MENU_PLAY_WITH_FRIEND = 2,
	MENU_EXIT = 3,

	MENU_FIRST = MENU_PLAY_ALONE,
	MENU_LAST = MENU_EXIT
};

class MainMenuView : public GameView{
public:
	static const std::string MAIN_MENU_VIEW;

	MainMenuView(Game* game);
	void processKey(int key);
	void registerMenuCallback(Menu menu, MenuCallback callback);

private:

	Menu menu;
	boost::unordered_map <Menu, MenuCallback> menuCallbacks;

	void selectMenu(Menu menu);
	Menu getMenu();
	void runMenu(Menu menu);
};