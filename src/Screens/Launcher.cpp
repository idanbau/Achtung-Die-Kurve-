#include "Screens/Launcher.h"


const auto BUTTON_SIZE = sf::Vector2f(300.f, 100.f);
const auto PLAY = "Play";
const auto SETTINGS = "Settings";
const auto EXIT = "Exit";

Launcher::Launcher(sf::RenderWindow& window) :Screen(window),
m_buttons({
	Button{ screen_type::settings, {m_window.getSize().x / 2.f , float(m_window.getSize().y / 2)}, PLAY, font_type::font2, BUTTON_SIZE, { sf::Color::Red, sf::Color::Blue,  sf::Color::White }},
	Button{ screen_type::exit, {m_window.getSize().x / 2.f , m_window.getSize().y / 2 + BUTTON_SIZE.y + BUTTON_BUFFER}, EXIT, font_type::font2, BUTTON_SIZE, { sf::Color::Red, sf::Color::Blue,  sf::Color::White }}
})
{
	m_background.setTexture(&TextureHandle::use().getTexture(textures_type::background));
};

screen_type Launcher::run() {
	
	auto hover = size_t(0);
	m_buttons[hover].setMode(ButtonType::color_type::hover);
	while(m_window.isOpen()){
		draw();
		if(auto event = sf::Event(); m_window.waitEvent(event))
		{
			switch (event.type) {
			case sf::Event::MouseButtonReleased:
			{
				auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				for (const auto& button : m_buttons) {
					if (button.isContain(location)) {
						return button.getT();
					}
				}
				break;
			}
			case sf::Event::MouseMoved:
			{
				auto location = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
				for (size_t i = 0; i < m_buttons.size(); ++i) {
					if (m_buttons[i].isContain(location) && hover != i) {
						m_buttons[hover].setMode(ButtonType::color_type::regular);
						hover = i;
						m_buttons[hover].setMode(ButtonType::color_type::hover);
						break;
					}
				}
				break;
			}
			case sf::Event::KeyReleased:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Key::Up:
					m_buttons[hover].setMode(ButtonType::color_type::regular);
					hover = (hover + LAUNCHER_BUTTONS - 1) % LAUNCHER_BUTTONS;
					m_buttons[hover].setMode(ButtonType::color_type::hover);
					break;
				case sf::Keyboard::Key::Down:
					m_buttons[hover].setMode(ButtonType::color_type::regular);
					hover = (hover + 1) % LAUNCHER_BUTTONS;
					m_buttons[hover].setMode(ButtonType::color_type::hover);
					break;
				case sf::Keyboard::Key::Enter:
					return m_buttons[hover].getT();
				}
				break;
			}
			case sf::Event::Closed:
				m_window.close();
				return screen_type::exit;
			}
		}
		}
	return screen_type::exit;
}

void Launcher::draw() const
{
	m_window.clear();
	m_window.draw(m_background);
	for (const auto& button : m_buttons)
		m_window.draw(button);
	m_window.display();
}
