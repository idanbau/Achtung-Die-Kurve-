#pragma once
#include <array>
#include <utility>
#include <SFML/Graphics.hpp>

const auto NUM_OF_COLORS = 13;

class ColorContainer
{
public:
	const sf::Color& useColor();
	ColorContainer& releaseColor(const sf::Color& color);
	void clear();
private:
	std::array<std::pair<sf::Color, bool>, NUM_OF_COLORS> m_colors = {
		std::make_pair(sf::Color::Cyan, false),
		std::make_pair(sf::Color::Red, false),
		std::make_pair(sf::Color::Blue, false),
		std::make_pair(sf::Color::Green, false),
		std::make_pair(sf::Color::Magenta, false),
		std::make_pair(sf::Color::Yellow, false),
		std::make_pair(sf::Color::White, false),
		std::make_pair(sf::Color(125, 255, 126), false),
		std::make_pair(sf::Color(139, 163, 140), false),
		std::make_pair(sf::Color(159, 0, 47), false),
		std::make_pair(sf::Color(79, 47, 0), false),		
		std::make_pair(sf::Color(255, 117, 95), false),
		std::make_pair(sf::Color(230, 186, 123), false)
	};
	size_t m_nextColor = 0;
	void continueNextColor();
};
