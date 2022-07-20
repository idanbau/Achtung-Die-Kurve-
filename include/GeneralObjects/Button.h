#pragma once
#include "BaseButton.h"


template <class T>
class Button:public BaseButton
{
public:
	Button(const T& t, const sf::Vector2f& pos, const std::string& text, font_type font, const sf::Vector2f& buttonSize, const ButtonType& colors);
	Button(const T& t, const sf::Vector2f& pos, const std::string& text, font_type font, const sf::Vector2f& buttonSize, const sf::Color& color);
	auto& getT() const;
private:
	T m_t;

};

template<class T>
Button<T>::Button(const T& t, const sf::Vector2f& pos, const std::string& text, font_type font, const sf::Vector2f& buttonSize, const ButtonType & colors)
	: m_t(t), BaseButton{ pos, text, font, buttonSize, colors}{}

template<class T>
Button<T>::Button(const T& t, const sf::Vector2f& pos, const std::string& text, font_type font, const sf::Vector2f& buttonSize, const sf::Color &color)
	: m_t(t), BaseButton{ pos, text, font, buttonSize, { color,color,color }} {}

template<class T>
auto& Button<T>::getT() const {
	return m_t;
}