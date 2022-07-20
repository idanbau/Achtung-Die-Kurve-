#include "Screens/GoesStages.h"
#include "Utilities.h"

const auto SPEED_REFLECTION = 5;

GoesStages::GoesStages(sf::RenderWindow& window) : Screen(window) {
	setOriginCenter(m_pressAnyKey);
	m_pressAnyKey.setPosition(sf::Vector2f{ (float)WIDTH_BOARD ,(float)WINDOW_SIZE.y } / 2.f);
}

screen_type GoesStages::run() {
	auto reflection = MAX_REFLECTION;
	auto speed = -SPEED_REFLECTION;
	while (m_window.isOpen()) {

		draw();

		if (auto event = sf::Event(); m_window.pollEvent(event)){
			switch (event.type) {
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Key::Space:
				case sf::Keyboard::Key::Enter:
					return screen_type::back;
				}
				break;
			case sf::Event::Closed:
				m_window.close();
				return screen_type::exit;
			}
		}
		m_pressAnyKey.setColor({ MAX_COLOR, MAX_COLOR, MAX_COLOR, setReflection(reflection, speed) });
	}
	return screen_type::back;
}

void GoesStages::draw() const
{
	m_window.clear();
	m_window.draw(m_screenShoot);
	m_window.draw(m_pressAnyKey);
	m_window.display();
}
