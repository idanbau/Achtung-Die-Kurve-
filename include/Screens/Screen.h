#pragma once
#include <SFML/Graphics.hpp>
#include "FileManager/TextureHandle.h"


const auto WINDOW_SIZE = sf::Vector2u{ 1200U, 800U };
const auto  WIDTH_TOOLBAR = 200U;
const auto WIDTH_BOARD = WINDOW_SIZE.x - WIDTH_TOOLBAR;
const auto TOOLBAR_SIZE = sf::Vector2u{ WINDOW_SIZE.x - WIDTH_BOARD, WINDOW_SIZE.y};

enum class screen_type
{
	exit = -2, back = -1, launcher, goesStages, settings, endScreen, screensCount
};


class Screen {
public:
	Screen(sf::RenderWindow& window) : m_window(window) {}
	virtual ~Screen() = default;
	virtual screen_type run() = 0;
protected:
	static sf::RectangleShape m_background;
	sf::RenderWindow& m_window;
	virtual void draw() const = 0;
private:
};

