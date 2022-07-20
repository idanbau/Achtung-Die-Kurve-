#include "GeneralObjects/VertexSet.h"
#include "Utilities.h"

const auto VERTEX_NEAR_HEAD = 20;
const auto LINE_TYPE = sf::PrimitiveType::TriangleStrip;
//set lines fo vectors according to number of player
void VertexSet::setLine(size_t numOfPlayers) {
	m_vertices = std::vector<std::vector<std::vector<sf::Vertex>>>
		(numOfPlayers, std::vector<std::vector<sf::Vertex>>(1, std::vector<sf::Vertex>()));
}

void VertexSet::newLine() {//split all lines
	for (auto& line : m_vertices)
		line.emplace_back();
}

void VertexSet::newLine(size_t index) {//split specific snake current lines
	m_vertices[index].emplace_back();
}

//add 2 points to array
void VertexSet::assign(size_t index, const std::pair<sf::Vertex, sf::Vertex>& vertecies) {
	m_vertices[index].back().push_back(vertecies.first);
	m_vertices[index].back().push_back(vertecies.second);
}

void VertexSet::clear() {
	setLine(m_vertices.size());//clear all points
}

void VertexSet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& player : m_vertices)
		for (const auto& line : player)
			if(!line.empty())
			target.draw(&line.front(), line.size(), LINE_TYPE, states);
}

//check collise of snake with another snakes.
bool VertexSet::checkCollise(size_t index, const sf::FloatRect& rect) const {
	for (auto snake = m_vertices.cbegin(); snake < m_vertices.cend(); ++snake){
		for (auto lines = snake->cbegin(); lines < snake->cend(); ++lines) {
			auto minus = (m_vertices.cbegin() + index == snake && lines == snake->cend() - 1) ? VERTEX_NEAR_HEAD : 0;
			for (auto currentLine = lines->cbegin(); lines->size() >= minus && currentLine < lines->cend() - minus; ++currentLine) {
				if (rect.contains(currentLine->position)){
					return true;
				}
			}
		}
	}
	return false;
}

//check points near snakes for bot
std::vector<sf::Vector2f> VertexSet::getVerticesNearPoint(const sf::Vector2f& head) const {
	auto vertices = std::vector<sf::Vector2f>();
	for (const auto& snake : m_vertices){
		for(const auto& line : snake) {
			for(const auto& point : line) {
				if (isContainByRadius(point.position, head, RADIUS)) {
					vertices.push_back(point.position);
				}
			}	
		}
	}
	return vertices;
}
