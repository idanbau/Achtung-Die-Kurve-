#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <functional>
#include <iostream>



class VertexSet : public sf::Drawable
{
public:
	void setLine(size_t numOfPlayers);
	void newLine();
	void newLine(size_t index);
	void assign(size_t index, const std::pair<sf::Vertex, sf::Vertex>& vertecies);
	void clear();
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
	bool checkCollise(size_t index, const sf::FloatRect& rect) const;
	std::vector<sf::Vector2f> getVerticesNearPoint(const sf::Vector2f & head) const;
private:
	std::vector<std::vector<std::vector<sf::Vertex>>> m_vertices;
};
