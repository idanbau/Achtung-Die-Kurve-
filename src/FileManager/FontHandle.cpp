#include "FileManager/FontHandle.h"
#include <string>

FontHandle::FontHandle() {
	loadFonts();
}

void FontHandle::loadFonts() {
	auto fileNames = std::array <std::string, (size_t)font_type::FontsCount>{"Font1.otf", "Font2.otf"};
	for (auto i = std::make_pair(m_fonts.begin(), fileNames.cbegin()); i.first < m_fonts.end(); ++i.first, ++i.second) {
		i.first->loadFromFile(*i.second);
	}
}

FontHandle& FontHandle::use() {
	static FontHandle fontHandleObj;
	return fontHandleObj;
}

const sf::Font& FontHandle::getFont(font_type type) const {
	return m_fonts[size_t(type)];
}
