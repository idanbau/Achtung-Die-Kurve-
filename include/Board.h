#pragma once
#include<vector>
#include <utility>
#include <array>
#include "SFML/Graphics.hpp"
#include "GeneralObjects/VertexSet.h"
#include "Screens/Screen.h"
#include "GameObjects.hpp"
#include "GeneralObjects/State.h"


const auto DEAD = true;
const auto STILL_ALIVE = false;
typedef bool ALIVE;

enum class Exceeded : int
{
	notExceeded = -1, up = 0, right, down, left	// clockwise
};

class CollisionHandling;
class Gift;

class Board
{
public:
	void setBoard(size_t numOfPlayers);
	void insert(size_t index, const std::pair<sf::Vertex, sf::Vertex>& points);
	void draw(sf::RenderWindow& window) const;
	void splitLines();
	void clear();
	void clearLines();
	void removeBoundaries();
	bool checkCollise(size_t index, Snake& snake, CollisionHandling& collision);
	void clockUpdate(const sf::Time& time);
	bool isCollides(const Bot& bot) const;
	std::vector<sf::Vector2f> getVerticesNearPoint(const sf::Vector2f& head) const;
	Exceeded inBounderies(const sf::Vector2f& point, float radius) const;
private:
	static std::unique_ptr<Gift> createRandomGift();
	VertexSet m_lines;
	std::vector<std::unique_ptr<Gift>> m_gifts;
	sf::RectangleShape m_frame = sf::RectangleShape{ {(float)WIDTH_BOARD, (float)WINDOW_SIZE.y} };
	State m_removeBounderies;
	int m_bounderiesReflection = MIN_REFLECTION;
	int m_speedReflection = SPEED_REFLECTION;
	bool alighnWithBoard(Snake& snake, size_t index);
	bool isRemoveBoundaries(const Snake& snake);
};