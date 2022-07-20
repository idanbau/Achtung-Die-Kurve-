#pragma once
#include "GameObjects\MovingObjects\Snake.h"

class Player : public Snake
{
public:
	Player(const sf::Color& color, const std::string& name, const sf::Keyboard::Key& leftKey, const sf::Keyboard::Key& rightKey);
	const sf::Keyboard::Key& getLeft() const;
	const sf::Keyboard::Key& getRight() const;
	void setLeft(const sf::Keyboard::Key& key);
	void setRight(const sf::Keyboard::Key& key);
private:
	void changeDirection(const sf::Time& deltaTime) override;
	sf::Keyboard::Key m_leftKey;		//keys
	sf::Keyboard::Key m_rightKey;
};