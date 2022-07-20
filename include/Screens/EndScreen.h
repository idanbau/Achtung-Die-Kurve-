#pragma once
#include "Screen.h"
#include "GameObjects/MovingObjects/Snake.h"
#include "GeneralObjects/Button.h"

class EndScreen: public Screen
{
public:
	EndScreen(sf::RenderWindow& window, const std::vector<std::unique_ptr<Snake>>& snakes);
	screen_type run() override;
	void loadScores();
	
private:
	sf::Text m_scoresTitle;//title for end screen
	sf::RectangleShape m_scoresRect = sf::RectangleShape();//score rectangle dynamic according to number of snakes
	const std::vector<std::unique_ptr<Snake>>& m_snakes;	//snakes vector
	std::vector<std::pair<sf::Text, sf::Text>> m_namesScores;//pair: first for name and second for score
	Button<screen_type> m_mainMenu;
	void draw() const override;
};