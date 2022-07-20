#include "GeneralObjects/BaseButton.h"
#include "Utilities.h"

const auto HOVERSCALE = sf::Vector2f(1.15f, 1.15f);//set button bigger when in hover

BaseButton::BaseButton(const sf::Vector2f& pos, const std::string& text, font_type font, const sf::Vector2f& buttonSize, const ButtonType& color):
	m_text(text, FontHandle::use().getFont(font)), m_button(buttonSize), m_buttonColors(color)
{
	m_button.setFillColor(m_buttonColors.m_colors[(size_t)ButtonType::color_type::regular]);
	setOriginCenter(m_button);
	setOriginCenter(m_text);
	setPosition(pos);
}

BaseButton::~BaseButton() {}

void BaseButton::setPosition(const sf::Vector2f& pos) {
	m_button.setPosition(pos);
	m_text.setPosition(pos);
}

void BaseButton::setColor(const sf::Color& col) {
	m_buttonColors.m_colors = { col, col, col };
	m_button.setFillColor(col);
}

void BaseButton::setString(const std::string& string) {
	m_text.setString(string);
	setOriginCenter(m_text);
}

//clear button string
void BaseButton::clear() {
	m_text.setString(sf::String());
}

bool BaseButton::empty() const {
	return m_text.getString().isEmpty();
}

const sf::Color& BaseButton::getColor() const {
	return m_buttonColors.m_colors[size_t(ButtonType::color_type::regular)];
}

const sf::String& BaseButton::getString() const {
	return m_text.getString();
}

void BaseButton::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_button);
	target.draw(m_text);
}

//check if a location is contain in the button
bool BaseButton::isContain(const sf::Vector2f& location) const {
	return m_button.getGlobalBounds().contains(location);
}

//change mode for buttons mode
void BaseButton::setMode(ButtonType::color_type color) {
	m_button.setFillColor(m_buttonColors.m_colors[size_t(color)]);
	switch (color)
	{
	case ButtonType::color_type::hover:
		SoundHandle::use().playSound(sound_type::hover);
		m_button.setScale(HOVERSCALE);
		break;
	case ButtonType::color_type::regular:
		m_button.setScale(1.f, 1.f);
		break;
	case ButtonType::color_type::choosed:
		SoundHandle::use().playSound(sound_type::clickButton);
		m_button.setScale(HOVERSCALE);
		break;
	}
}