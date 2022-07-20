#pragma once
#include <SFML/Graphics.hpp>
#include <array>
// Singelton


enum class textures_type : size_t
{
	boundaries, boundariesAll, clear, immortal, reverseAll, speedDown, speedDownAll, speedUp, speedUpAll,
	thick, thickAll, thin, thinAll, background, SettingsLogo, pressSpace, frame, TexturesCount
};

class TextureHandle {
public:
	static TextureHandle& use();
	const sf::Texture& getTexture(textures_type type) const;
	const sf::Texture& getPrintScreen() const;
	void setPrintScreen(sf::RenderWindow& window);
private:
	TextureHandle();
	TextureHandle(const TextureHandle&) = default;
	TextureHandle& operator=(const TextureHandle&) = default;
	void loadTextures();
	std::array <sf::Texture, (size_t)textures_type::TexturesCount> m_textures;
	sf::Texture m_printScreen;
};