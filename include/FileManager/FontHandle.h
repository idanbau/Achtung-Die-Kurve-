#pragma once
#include <SFML/Graphics.hpp>
#include <array>
// Singelton


enum class font_type : size_t
{
	font1, font2, FontsCount
};


class FontHandle {
public:
	static FontHandle& use();
	const sf::Font& getFont(font_type type) const;
private:
	void loadFonts();
	FontHandle();
	FontHandle(const FontHandle&) = default;
	FontHandle& operator=(const FontHandle&) = default;
	std::array<sf::Font, (size_t)font_type::FontsCount> m_fonts;
};