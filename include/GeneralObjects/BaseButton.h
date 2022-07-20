#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include "FileManager.hpp"

const auto BUTTON_BUFFER = 20;
const auto COLORS = 3;
typedef std::array<sf::Color, COLORS> colors;



struct ButtonType {
	enum class color_type : size_t
	{
		regular, hover, choosed
	};
	ButtonType(const colors& color) : m_colors(color) {};
	ButtonType(const sf::Color& regular, const sf::Color& hover, const sf::Color& choosed) {
		m_colors = { regular, hover, choosed };
	}
	colors m_colors;
};

class BaseButton : public sf::Drawable
{
public:
	BaseButton(const sf::Vector2f& pos, const std::string& text, font_type font, const sf::Vector2f& buttonSize, const ButtonType& color);
	virtual ~BaseButton() = 0;
	void setPosition(const sf::Vector2f& pos);
	void setColor(const sf::Color& col);
	void setString(const std::string& string);
	void clear();
	const sf::Color& getColor() const;
	const sf::String& getString() const;
	bool isContain(const sf::Vector2f& location) const;
	void setMode(ButtonType::color_type color);
	bool empty() const;

private:
	sf::Text m_text;
	sf::RectangleShape m_button;
	ButtonType m_buttonColors;
	bool m_textCenter;
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
};