#pragma once
#include "GameObjects\MovingObjects\Snake.h"

class Board;

class Bot : public Snake
{
public:
	Bot(const sf::Color& color, const std::string& name, const Board& board);
	void changeDirection(const sf::Time& deltaTime) override;
private:
	const Board& m_board;
	bool checkDirection(sf::Vector2f point, const sf::Vector2f& angle, const std::vector<sf::Vector2f>& pointsNearHead) const;
	void changeRandomDirection(const sf::Time& deltaTime);
};