#include "Board.h"
#include "FileManager/TextureHandle.h"
#include "GameObjects.hpp"
#include "CollisionHandling.h"
#include "Utilities.h"


const auto BOARDER_FIX = 10.f;


void Board::setBoard(size_t numOfPlayers){
	m_frame.setTexture(&TextureHandle::use().getTexture(textures_type::frame));
	m_lines.setLine(numOfPlayers);
}

void Board::insert(size_t index, const std::pair<sf::Vertex, sf::Vertex>& points) {
	m_lines.assign(index, points);
}

void Board::draw(sf::RenderWindow& window) const{
	window.draw(m_frame);
	m_lines.draw(window);
	for (const auto& gift : m_gifts) {
		gift->draw(window);
	}
}
void Board::splitLines(){
	m_lines.newLine();
	m_gifts.push_back( createRandomGift() );
}


void Board::clear(){
	clearLines();
	m_gifts.clear();
	m_removeBounderies.m_state = false;
	m_frame.setFillColor({ MAX_COLOR, MAX_COLOR, MAX_COLOR, sf::Uint8(MAX_REFLECTION) });
}

void Board::clearLines() {
	m_lines.clear();
}

void Board::removeBoundaries() {
	m_removeBounderies.setState();
}

bool Board::checkCollise(size_t index, Snake& snake, CollisionHandling& collision) {
	auto rect = snake.getHead().getGlobalBounds();
	for (auto& gift : m_gifts) {
		if (rect.intersects(gift->getGlobalBounds())){
			gift->collise(collision, index);
		}
	}
	m_gifts.erase(std::remove_if(m_gifts.begin(), //remove used presents
		m_gifts.end(), [&](const auto& gift)
		{
			return gift->isTaken();
		}), m_gifts.end());

	return alighnWithBoard(snake, index) || (!snake.getState(state_type::immortal) && m_lines.checkCollise(index, rect));
}

std::unique_ptr<Gift> Board::createRandomGift()
{
	switch ((gifts_type)(rand() % size_t(gifts_type::giftsCount)))
	{
	case gifts_type::fast:						return std::make_unique<Fast>();
	case gifts_type::clear:						return std::make_unique<Clear>();
	case gifts_type::invertMove:				return std::make_unique<InvertMove>();
	case gifts_type::immortal:					return std::make_unique<Immortal>();
	case gifts_type::removeBoundaries:			return std::make_unique<RemoveBoundaries>();
	case gifts_type::slow:						return std::make_unique<Slow>();
	case gifts_type::thick:						return std::make_unique<Thick>();
	case gifts_type::thin:						return std::make_unique<Thin>();
	case gifts_type::fastAll:					return std::make_unique<FastAll>();
	case gifts_type::removeBoundariesAll:		return std::make_unique<RemoveBoundariesAll>();
	case gifts_type::slowAll:					return std::make_unique<SlowAll>();
	case gifts_type::thickAll:					return std::make_unique<ThickAll>();
	case gifts_type::thinAll:					return std::make_unique<ThinAll>();
	default:
		throw std::out_of_range("Invalid Gift");
	}
}

void Board::clockUpdate(const sf::Time& time) {
	if (m_removeBounderies.m_state) {		// befor unset
		m_frame.setFillColor({ MAX_COLOR, MAX_COLOR, MAX_COLOR, setReflection(m_bounderiesReflection, m_speedReflection) });

		m_removeBounderies -= time;			// update and maybe unset the state

		if (!m_removeBounderies.m_state) {	// after -= maybe is not set anymore
			m_bounderiesReflection = MIN_REFLECTION;
			m_speedReflection = SPEED_REFLECTION;
			m_frame.setFillColor({ MAX_COLOR, MAX_COLOR, MAX_COLOR, sf::Uint8(MAX_REFLECTION) });
		}
	}
}

Exceeded Board::inBounderies(const sf::Vector2f& point, float radius) const {

	if (point.y - radius <=  BOARDER_FIX)					// up
		return Exceeded::up;

	if (point.x - radius >= WIDTH_BOARD - BOARDER_FIX)		// right
		return Exceeded::right;

	if (point.y - radius >= WINDOW_SIZE.y - BOARDER_FIX)	//down
		return Exceeded::down;

	if (point.x - radius <= BOARDER_FIX)					// left
		return Exceeded::left;

	return Exceeded::notExceeded;
}

ALIVE Board::alighnWithBoard(Snake& snake, size_t index)
{
	if (auto option = inBounderies(snake.getHead().getPosition(), snake.getHead().getRadius()); option != Exceeded::notExceeded && (m_removeBounderies.m_state || snake.getState(state_type::removeBoundaries) || snake.getState(state_type::immortal)))
	{
		switch (option)
		{
		case Exceeded::up:
			snake.setPosition(sf::Vector2f(snake.getHead().getPosition().x, WINDOW_SIZE.y - BOARDER_FIX));
			break;
		case Exceeded::right:
			snake.setPosition(sf::Vector2f(BOARDER_FIX + snake.getHead().getRadius(), snake.getHead().getPosition().y));
			break;
		case Exceeded::down:
			snake.setPosition(sf::Vector2f(snake.getHead().getPosition().x, BOARDER_FIX + snake.getHead().getRadius()));
			break;
		case Exceeded::left:
			snake.setPosition(sf::Vector2f(WIDTH_BOARD - BOARDER_FIX, snake.getHead().getPosition().y));
			break;
		default:
			throw std::out_of_range("Invalid exceeded");
		}
		m_lines.newLine(index);
	}
	else if (option != Exceeded::notExceeded) {
		return DEAD;
	}
	return STILL_ALIVE;
}

bool Board::isRemoveBoundaries(const Snake& snake) {
	return m_removeBounderies.m_state || snake.getState(state_type::removeBoundaries) || snake.getState(state_type::immortal);
}


ALIVE Board::isCollides(const Bot& bot) const {
	return bot.getState(state_type::immortal) ||
		((inBounderies(bot.getHead().getPosition(), bot.getHead().getRadius()) != Exceeded::notExceeded) ||
			(!bot.getState(state_type::removeBoundaries) && m_lines.checkCollise(0, bot.getHead().getGlobalBounds())));
}

std::vector<sf::Vector2f> Board::getVerticesNearPoint(const sf::Vector2f& head) const {
	return m_lines.getVerticesNearPoint(head);
}
