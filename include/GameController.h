#pragma once
#include "Board.h"
#include "GameObjects.hpp"
#include "Screens/Screen.h"
#include "GeneralObjects/Button.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "GeneralObjects/Toolbar.h"
#include "CollisionHandling.h"

class GameController
{
public:
	GameController();
	~GameController() = default;
	screen_type run();
private:
	void goScreen(screen_type = screen_type::launcher);
	void play();
	void draw(bool drawButton = true);
	void resetLevel();
	void resetPlayers();
	bool checkNextRound() const;
	void addAliveScore();
	void goNextRound();
	void changeSettings();
	sf::RenderWindow m_window;
	const std::vector<std::unique_ptr<Screen>> m_screens;
	std::vector<std::unique_ptr<Snake>> m_snakes;
	Board m_board = Board{};
	Toolbar m_toolbar = { m_window, m_snakes };
	size_t m_snakesAlive = 0;
	Button<std::function<void()>> m_settingButton;
};