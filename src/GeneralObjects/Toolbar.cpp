#include "GeneralObjects/Toolbar.h"
#include "Screens/Screen.h"
#include "Utilities.h"

const auto GOAL_TITLE = "Goal";
const auto BUFFER_SPACE = 10U;
const auto BUFFER_NEW_LINE = 50U;
const auto TOOLBAR_COLOR = sf::Color(34, 35, 36);


Toolbar::Toolbar(sf::RenderWindow& window, const std::vector<std::unique_ptr<Snake>>& snakes) : m_snakes(snakes), m_window(window),
m_goalText{ GOAL_TITLE, FontHandle::use().getFont(font_type::font1) }
{
	m_background.setFillColor(TOOLBAR_COLOR);
	m_background.setPosition(float(WIDTH_BOARD),0.f);
	
	setOriginCenter(m_goalTitleText);
	m_goalTitleText.setPosition(WIDTH_BOARD + WIDTH_TOOLBAR / 2.f, 20.f);
}
//reset toolbar data
void Toolbar::resetSetting(size_t goal) {
	m_goalText.setString(std::to_string(goal));
	setOriginCenter(m_goalText);
	m_goalText.setPosition(WIDTH_BOARD + WIDTH_TOOLBAR / 2.f, 50.f);
	m_names_scores.clear();
	m_names_scores = std::vector<std::pair<sf::Text, sf::Text>>(m_snakes.size(), std::make_pair(sf::Text("", FontHandle::use().getFont(font_type::font1)),
		sf::Text("", FontHandle::use().getFont(font_type::font1))));
	update();
}
//update toolbar data
void Toolbar::update()
{
	for (auto i = std::make_pair(m_snakes.cbegin(), m_names_scores.begin()); i.first < m_snakes.cend(); ++i.first, ++i.second) {
		i.second->first.setFillColor((*i.first)->getColor());
		i.second->second.setFillColor((*i.first)->getColor());
		i.second->first.setString((*i.first)->getName());
		i.second->second.setString(std::to_string((*i.first)->getScore()));
	}
	//std::sort(m_names_scores.begin(), m_names_scores.end(), comp);
	std::sort(m_names_scores.begin(), m_names_scores.end(),
		[](const std::pair<sf::Text, sf::Text>& lhs, const std::pair<sf::Text, sf::Text>& rhs) {
			return std::stoi(lhs.second.getString().toAnsiString()) > std::stoi(rhs.second.getString().toAnsiString()); });
	for (auto i = 0; i < m_names_scores.size(); ++i)
	{
		m_names_scores[i].first.setPosition(float(WIDTH_BOARD + BUFFER_SPACE), 100.f + 50.f * i);
		m_names_scores[i].second.setPosition(WIDTH_BOARD + 150.f, 100.f + 50.f * i);
	}
}
//draw toolbar
void Toolbar::draw() const {
	m_window.draw(m_background);
	for (const auto& name_score : m_names_scores)
	{
		m_window.draw(name_score.first);
		m_window.draw(name_score.second);
	}
	m_window.draw(m_goalTitleText);
	m_window.draw(m_goalText);
}


