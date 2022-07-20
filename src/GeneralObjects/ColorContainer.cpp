#include "GeneralObjects/ColorContainer.h"

//use current color
const sf::Color& ColorContainer::useColor(){
	for (size_t i = 0; i < NUM_OF_COLORS; ++i, continueNextColor()) {
		if (!m_colors[m_nextColor].second) { // if is not used
			m_colors[m_nextColor].second= true;
			auto currentColor = m_nextColor;
			continueNextColor();
			return m_colors[currentColor].first;
		}
	}

	throw std::invalid_argument("Missing color");
}

//release current color so we can use it next time
ColorContainer& ColorContainer::releaseColor(const sf::Color& color) {
	for (size_t i = 0; i < m_colors.size(); ++i)
		if (color == m_colors[i].first) {
			m_colors[i].second = false;
			if (m_nextColor == i)
				continueNextColor();
		}

	return *this;
}


void ColorContainer::clear() {
	for(auto& color : m_colors){
		color.second = false;
	}
}

void ColorContainer::continueNextColor() {
	m_nextColor = (m_nextColor + 1) % NUM_OF_COLORS;
}