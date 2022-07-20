#include "GameObjects/MovingObjects/Snake.h"
#include "Screens/Screen.h"
#include <iostream>
#include "GeneralObjects/Toolbar.h"
#include "Utilities.h"

const auto ANGLESUM = 360;
const auto RADIOS = 5.f;
const auto& HEAD_COLOR = sf::Color::Yellow;
const auto IMMORTAL_COLOR = sf::Uint8(250);//when has immortal
const auto THICKNESS = 8.f;


Snake::Snake(const sf::Color& color, const std::string& name)
	: m_color(color), m_name(name), m_head(RADIOS)
{
	m_head.setFillColor(HEAD_COLOR);
	setOriginCenter(m_head);
};

void Snake::draw(sf::RenderWindow& window) const {
	window.draw(m_head);
}

// move snake
void Snake::move(const sf::Time& deltaTime){
	handleStates(deltaTime);
	changeDirection(deltaTime);
	auto modifiedSpeed = SPEED;
	if (m_states[(size_t)state_type::fast].m_state)
		modifiedSpeed *= 2.f;
	if (m_states[(size_t)state_type::slow].m_state)
		modifiedSpeed /= 2.f;
	m_head.move(sf::Vector2f{ std::cosf(m_head.getRotation()), std::sinf(m_head.getRotation()) } * 
		(modifiedSpeed  * deltaTime.asSeconds()));	
}

// change location of snake (when starting a level)
void Snake::setPosition(const sf::Vector2f& pos) {
	m_head.setPosition(pos);
	m_lastPos = m_head.getPosition();
}

// add new vertices to data structures lines... bool draw is flag if the head his radius are contain last vertices..
std::optional<std::pair<sf::Vertex, sf::Vertex>> Snake::addVertices(bool draw) {
	if(!draw)
		m_lastPos = m_head.getPosition();
	if (m_head.getGlobalBounds().contains(m_lastPos)){
		return std::nullopt;
	}
	auto current = m_lastPos;
	m_lastPos = m_head.getPosition();
	auto direction = current - m_head.getPosition();
	auto unitDirection = direction / std::hypotf(direction.x, direction.y);
	decltype(unitDirection) unitPerpendicular(-unitDirection.y, unitDirection.x);

	auto modifiedThickness = THICKNESS;
	if (m_states[(size_t)state_type::thick].m_state)
		modifiedThickness *= 2.f;
	if (m_states[(size_t)state_type::thin].m_state)
		modifiedThickness /= 2.f;

	auto offset = (modifiedThickness / 2.f) * unitPerpendicular;
	return std::make_pair<sf::Vertex, sf::Vertex>({ current + offset, m_color },
		{ current - offset, m_color });
}

void Snake::addScore() {
	++m_score;
}

// reset snake setting and position (for next level)
void Snake::resetSetting() {
	setPosition(getRandomPosition());
	rotate(float(std::rand() % ANGLESUM), sf::seconds(1.f));
	m_lastPos = m_head.getPosition();
	m_alive = true;
	resetStates();
}

const sf::CircleShape& Snake::getHead() const {
	return m_head;
}

const sf::Color& Snake::getColor() const {
	return m_color;
}

// return if snake alive
bool Snake::alive() const{
	return m_alive;
}

void Snake::kill() {
	m_alive = false;
}

// rotate by angle
void Snake::rotate(const float& angle, const sf::Time& Deltatime) {
	m_head.rotate(angle * Deltatime.asSeconds());
}


size_t Snake::getScore() const {
	return m_score;
}

const std::string& Snake::getName() const {
	return m_name;
}

// handle the all states that come from gift and activates
void Snake::handleStates(const sf::Time& deltaTime) {
	auto inIf = false;
	if (m_states[size_t(state_type::immortal)].m_state)
	{
		m_head.setFillColor({ IMMORTAL_COLOR, 0, 0, setReflection(m_headReflection , m_speedReflection) });
		inIf = true;
	}
	else if (m_states[size_t(state_type::removeBoundaries)].m_state) {		// befor unset
		m_head.setFillColor({ m_head.getFillColor().r, m_head.getFillColor().g, m_head.getFillColor().b, setReflection(m_headReflection , m_speedReflection) });
		inIf = true;
	}
	for (auto& state : m_states) {
		if (state.m_state) {
			state -= deltaTime;
		}
	}

	if (inIf && !m_states[size_t(state_type::removeBoundaries)].m_state && !m_states[size_t(state_type::immortal)].m_state) {	// after -= maybe is not set anymore
		m_headReflection = MIN_REFLECTION;
		m_speedReflection = SPEED_REFLECTION;
		m_head.setFillColor(HEAD_COLOR);
	}
}

// reset all states
void Snake::resetStates() {
	for (auto& state : m_states) {
		state.m_state = false;
	}
	m_head.setFillColor(HEAD_COLOR); // for removeBoundaries state
}

// check if is statre are activate
bool Snake::getState(state_type  type) const {
	return m_states[(size_t)type].m_state;
}

// set state that come from taking gift
void Snake::setState(state_type type){
	m_states[(size_t)type].setState();
}

void Snake::setName(const std::string& name){
	m_name = name;
}

void Snake::setColor(const sf::Color& color) {
	m_color = color;
}
