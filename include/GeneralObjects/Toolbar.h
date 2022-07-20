#pragma once
#include "GameObjects/MovingObjects/Snake.h"
#include "Screens/Screen.h"
#include "FileManager/FontHandle.h"


class Toolbar
{
public:
	Toolbar(sf::RenderWindow& window, const std::vector<std::unique_ptr<Snake>>& snakes);
	void resetSetting(size_t goal);
	void update();
	void draw() const;
private:
	sf::RectangleShape m_background = sf::RectangleShape{ sf::Vector2f{TOOLBAR_SIZE } };
	size_t m_goal = 0;
	sf::RenderWindow& m_window;
	const std::vector<std::unique_ptr<Snake>>& m_snakes;
	std::vector<std::pair<sf::Text, sf::Text>> m_names_scores;
	sf::Text m_goalTitleText;
	sf::Text m_goalText = { "", FontHandle::use().getFont(font_type::font1) };
};

