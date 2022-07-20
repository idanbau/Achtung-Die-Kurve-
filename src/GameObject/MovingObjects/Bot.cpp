#include "GameObjects/MovingObjects/Bot.h"
#include "Board.h"
const auto DIAMETER = RADIUS * 2;
const auto LEFT = 0;
const auto RIGHT = 1;
const auto NUM_OF_OPTIONS = 3;

Bot::Bot(const sf::Color& color, const std::string& name, const Board& board) : Snake(color, name), m_board(board){};

void Bot::changeDirection(const sf::Time& deltaTime) {
	if (getState(state_type::immortal)) {
		changeRandomDirection(deltaTime);
		return;
	}

	auto point = getHead().getPosition();
	auto angle360 = m_head.getRotation();
	auto angle = sf::Vector2f(std::cosf(angle360), std::sinf(angle360));		// angle straight
	auto pointsArr = m_board.getVerticesNearPoint(point + (angle * (RADIUS + 20.f)));
	auto advanced = point + angle * DIAMETER;
	if (m_board.inBounderies(advanced, m_head.getRadius()) == Exceeded::notExceeded && pointsArr.empty()) {
		changeRandomDirection(deltaTime);
		return;
	}

	if (!checkDirection(point, angle, pointsArr)) {	// if straight is good direction
		return;		// not rotate
	}
	angle = { std::cosf(angle360 + 40.f), std::sinf(angle360 + 40.f) };
	rotate(!checkDirection(point, angle, pointsArr) ? ANGLE : -ANGLE, deltaTime);


}

ALIVE Bot::checkDirection( sf::Vector2f point, const sf::Vector2f& angle, const std::vector<sf::Vector2f>& pointsNearHead) const {
	for (auto snakeRadius = getHead().getRadius(); snakeRadius < DIAMETER; snakeRadius += getHead().getRadius()) {
		point += angle * getHead().getRadius();	
		if (!getState(state_type::removeBoundaries) && m_board.inBounderies(point, getHead().getRadius()) != Exceeded::notExceeded ){
				return DEAD;
		}
		for (const auto& currentPoint : pointsNearHead) {
			if (isContainByRadius(currentPoint, point, m_head.getRadius())){
				return DEAD;
			}
		}
	}
	return STILL_ALIVE;
}

void Bot::changeRandomDirection(const sf::Time& deltaTime) {
	switch (rand() % NUM_OF_OPTIONS)
	{
	case LEFT:
		rotate(ANGLE, deltaTime);
		break;
	case RIGHT:
		rotate(-ANGLE, deltaTime);
		break;
	}
}
