#include "GameObjects/MovingObjects/Player.h"
#include "Utilities.h"
#include "iostream"


Player::Player(const sf::Color& color, const std::string& name, const sf::Keyboard::Key& leftKey, const sf::Keyboard::Key& rightKey)
	: m_leftKey(leftKey), m_rightKey(rightKey), Snake(color, name) {}

const sf::Keyboard::Key& Player::getLeft() const {
	return m_leftKey;
}

const sf::Keyboard::Key& Player::getRight() const {
	return m_rightKey;
}

void Player::setLeft(const sf::Keyboard::Key& key) {
	m_leftKey = key;
}

void Player::setRight(const sf::Keyboard::Key& key) {
	m_rightKey = key;
}

// change the angle dirction
void Player::changeDirection(const sf::Time& deltaTime) {
	if (sf::Keyboard::isKeyPressed(m_leftKey)){
		rotate(getState(state_type::invertMove) ? ANGLE : -ANGLE, deltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(m_rightKey)) {
		rotate(getState(state_type::invertMove) ? -ANGLE : ANGLE, deltaTime);
	}
}