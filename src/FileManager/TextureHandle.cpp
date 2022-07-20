#include "FileManager/TextureHandle.h"
#include "Screens/Screen.h"
#include <iostream>
TextureHandle::TextureHandle() {
	loadTextures();
	m_printScreen.create(WINDOW_SIZE.x, WINDOW_SIZE.y);	// for take a picture screen and save it for any object will take it)
}

void TextureHandle::loadTextures() {
	const auto fileNames = std::array <std::string, (size_t)textures_type::TexturesCount>{ "Boundaries.png","BoundariesAll.png", "Clear.png","Immortal.png",
		"ReverseAll.png","SpeedDown.png","SpeedDownAll.png","SpeedUp.png","SpeedUpAll.png",
		"Thick.png","ThickAll.png","Thin.png","ThinAll.png", "Background.png", "SettingsLogo.png", "PressSpace.png", "Frame.png"
	};
	for (auto i = std::make_pair(m_textures.begin(), fileNames.cbegin()); i.first < m_textures.end(); ++i.first, ++i.second) {
		i.first->loadFromFile(*i.second);
	}
}

TextureHandle& TextureHandle::use() {
	static TextureHandle textureHandleObj;
	return textureHandleObj;
}

const sf::Texture& TextureHandle::getTexture(textures_type type) const { 
	return m_textures[(size_t)type];
}

const sf::Texture& TextureHandle::getPrintScreen() const {
	return m_printScreen;
}

void TextureHandle::setPrintScreen(sf::RenderWindow& window) {
	window.display();
	m_printScreen.loadFromImage(window.capture());
}
