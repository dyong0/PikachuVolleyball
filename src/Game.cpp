#include "stdafx.h"
#include "Game.h"

#include <conio.h>
#include <boost/thread.hpp>
#include <boost/format.hpp>
#include <chrono>
#include <thread>

#include "common.h"
#include "MainMenuView.h"
#include "IngameView.h"

using namespace std;
using namespace common;

struct KeyInputJob
{
	void operator () () {
		while (1) {
			int key = _getch();
			if (key == 0 || key == 224){
				key = _getch();
			}

			Game::getInstance()->getInputQueue()->push(key);
		}
	}
};

const float Game::DEFAULT_FPS = 60.0f;

Game* Game::instance = NULL;
queue<int>* Game::keyInputQueue = new queue<int>();

Game::Game() :running(false), currentView(NULL), fps(DEFAULT_FPS)
{
}

Game::~Game()
{
}

Game* Game::getInstance(){
	if (instance == NULL){
		instance = new Game();
	}
	return instance;
}

std::queue<int>* Game::getInputQueue(){
	return this->keyInputQueue;
}

void Game::init(){
	KeyInputJob inputJob;
	boost::thread inputThread(inputJob);

	this->initViews();
	this->changeView(MainMenuView::MAIN_MENU_VIEW);
}

void Game::initViews(){
	{
		MainMenuView* view = new MainMenuView(this);
		view->registerMenuCallback(MENU_PLAY_ALONE, &Game::startGameAlone);
		view->registerMenuCallback(MENU_PLAY_WITH_FRIEND, &Game::startGameWithFriend);
		view->registerMenuCallback(MENU_EXIT, &Game::quit);
		this->registerGameView(MainMenuView::MAIN_MENU_VIEW, view);
	}
	{
		IngameView* view = new IngameView(this);
		this->registerGameView(IngameView::INGAME_VIEW, view);
	}
}

void Game::startGameAlone(){
	this->gameMode = GAME_MODE_PLAY_ALONE;
	this->players[0] = new UserPlayer(DIRECTION_RIGHT);
	this->players[1] = new AIPlayer(DIRECTION_LEFT);
	
	this->startGame();
};
void Game::startGameWithFriend(){
	this->gameMode = GAME_MODE_PLAY_WITH_FRIEND;
	this->players[0] = new UserPlayer(DIRECTION_RIGHT);
	this->players[1] = new UserPlayer(DIRECTION_LEFT);
	
	this->startGame();
};

void Game::startGame(){
	//TODO
	this->changeView(IngameView::INGAME_VIEW);

	this->players[0]->setPosition(Player::LEFT_PLAYER_START_POSITION_X, Player::LEFT_PLAYER_START_POSITION_Y);
	this->players[1]->setPosition(Player::RIGHT_PLAYER_START_POSITION_X, Player::RIGHT_PLAYER_START_POSITION_Y);
}

void Game::changeView(string viewName){
	auto view = this->views[viewName];
	if (view == NULL){
		string message = "Not found view ==> " + viewName;
		try{
			throw new NotRegisteredViewException();
		}
		catch (exception const& e){
			onFatalException(e);
		}
	}

	this->currentView = view;
}

void Game::onFatalException(exception const& e){
	//TODO : reports data
	
	//TODO : print sorry message

	exit(EXIT_FAILURE);
}

void Game::reset(){
	if (this->players[0]){
		delete this->players[0];
	}
	if (this->players[1]){
		delete this->players[1];
	}

	this->players[0] = new UserPlayer(DIRECTION_RIGHT);
	if (this->gameMode == GAME_MODE_PLAY_ALONE){
		this->players[1] = new UserPlayer(DIRECTION_LEFT);
	}
	else if (this->gameMode == GAME_MODE_PLAY_WITH_FRIEND){
		this->players[1] = new AIPlayer(DIRECTION_LEFT);
	}
}

void Game::quit(){
	this->running = false;
}

void Game::registerGameView(string viewName, GameView* view){
	this->views[viewName] = view;
}

void Game::run(){
	this->running = true;

	chrono::duration<double> minLoopDuration(1. / this->fps);
	auto currentClock = chrono::high_resolution_clock::now();
	auto lastClock = currentClock;
	float deltaFrame = 0.0f;

	while (this->running){
		currentClock = chrono::high_resolution_clock::now();
		chrono::duration<double> timeDelta = currentClock - lastClock;
		if (timeDelta < minLoopDuration){
			this_thread::sleep_for(chrono::duration_cast<chrono::milliseconds>(timeDelta));
			
			timeDelta = minLoopDuration;
		}

		deltaFrame = this->fps * chrono::duration_cast<chrono::milliseconds>(timeDelta).count() / 1000;

		this->currentView->processKey(this->getLastInputKey());
		for (int i = 0; i < 2; ++i){
			Player* player = this->players[i];
			if (player){
				player->update(deltaFrame);
			}
		}

		if (this->players[0]){
			Position* pos = this->players[0]->getPosition();
			cout << pos->x << ", " << pos->y << endl;
		}
		
		lastClock = currentClock;
	}
}

int Game::getLastInputKey(){
	int key = KEY_INVALID;
	if (this->keyInputQueue->empty() == false){
		key = this->keyInputQueue->front();
		this->keyInputQueue->pop();
	}

	return key;
}

Player* Game::getPlayer(int index){
	Player* player = this->players[index];
	if (player == NULL){
		throw new PlayerNotCreated();
	}

	return player;
}