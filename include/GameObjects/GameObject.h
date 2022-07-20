#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	~GameObject() = default;
	virtual void draw(sf::RenderWindow&) const = 0;
protected:
	static sf::Vector2f getRandomPosition();
};