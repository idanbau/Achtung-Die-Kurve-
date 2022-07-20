#include "Screens\EndScreen.h"

const auto SCORES_COLOR = sf::Color(34, 35, 36);
const auto MAIN_MENU = "Main Menu";
const auto SCORES_TITLE = "Hall Of Fame";
const auto START_HEIGHT = 300.f;
const auto SPACE_BETWEEN_SNAKES = 50.f;

EndScreen::EndScreen(sf::RenderWindow& window, const std::vector<std::unique_ptr<Snake>>& snakes) : Screen(window), m_snakes(snakes),
m_mainMenu(Button{
		screen_type::launcher, { WINDOW_SIZE.x / 2.f , WINDOW_SIZE.y - 60.f },	// location
		MAIN_MENU, font_type::font2, { 200.f, 50.f }, { sf::Color::Red, sf::Color::Blue,  sf::Color::Black } }),
		m_scoresTitle(SCORES_TITLE, FontHandle::use().getFont(font_type::font1), 60U)
{
	m_scoresRect.setFillColor(SCORES_COLOR);//set 
	setOriginCenter(m_scoresTitle);
};
screen_type EndScreen::run() {
	SoundHandle::use().playEndMusic();
	m_scoresTitle.setPosition(sf::Vector2f{ WINDOW_SIZE.x / 2.f , START_HEIGHT - 50.f });
	m_scoresRect.setSize(sf::Vector2f{ 400.f ,m_snakes.size() * SPACE_BETWEEN_SNAKES });
	auto rect = m_scoresRect.getGlobalBounds();

	m_scoresRect.setPosition(sf::Vector2f(((WINDOW_SIZE.x - rect.width + 20.f) / 2.f), START_HEIGHT));
	loadScores();
	m_mainMenu.setMode(ButtonType::color_type::hover);
	while (m_window.isOpen()) {
		draw();
		if (auto event = sf::Event{}; m_window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::EventType::Closed:
			{
				m_window.close();
				break;
			}
			case sf::Event::KeyReleased:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Key::Enter:
				{
					SoundHandle::use().playBackGroundMusic();
					return m_mainMenu.getT();
				}
				}
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				if (m_mainMenu.isContain(location)) {
					SoundHandle::use().playBackGroundMusic();
					return m_mainMenu.getT();
				}
				break;
			}
			}
		}
	}
	return screen_type::exit;
}

void EndScreen::loadScores(){
	m_namesScores = std::vector<std::pair<sf::Text, sf::Text>>(m_snakes.size(), std::make_pair(sf::Text("", FontHandle::use().getFont(font_type::font1)),
		sf::Text("", FontHandle::use().getFont(font_type::font1))));
	for (auto i = std::make_pair(m_snakes.cbegin(), m_namesScores.begin()); i.first < m_snakes.cend(); ++i.first, ++i.second) {
		i.second->first.setFillColor((*i.first)->getColor());
		i.second->second.setFillColor((*i.first)->getColor());
		i.second->first.setString((*i.first)->getName());
		i.second->second.setString(std::to_string((*i.first)->getScore()));
	}
	std::sort(m_namesScores.begin(), m_namesScores.end(),//sort for sorted scores during the game
		[](const std::pair<sf::Text, sf::Text>& lhs, const std::pair<sf::Text, sf::Text>& rhs) {
			return std::stoi(lhs.second.getString().toAnsiString()) > std::stoi(rhs.second.getString().toAnsiString()); });
	for (auto i = 0; i < m_namesScores.size(); ++i) {
		m_namesScores[i].first.setPosition(WINDOW_SIZE.x / 2 - 100.f, START_HEIGHT + SPACE_BETWEEN_SNAKES * i);
		m_namesScores[i].second.setPosition(WINDOW_SIZE.x / 2 + 100.f, START_HEIGHT + SPACE_BETWEEN_SNAKES * i);
	}
}

//draw function for end screen
void EndScreen::draw() const {
	m_window.clear();
	m_window.draw(m_background);
	m_window.draw(m_scoresRect);
	m_window.draw(m_scoresTitle);
	m_window.draw(m_mainMenu);
	for (const auto& name_score : m_namesScores) {
		m_window.draw(name_score.first);
		m_window.draw(name_score.second);
	};
	m_window.display();
}
