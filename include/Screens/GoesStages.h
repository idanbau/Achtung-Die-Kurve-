#pragma once
#include "Screen.h"
class GoesStages : public Screen
{
public:
	GoesStages(sf::RenderWindow& window);
	screen_type run() override;
private:
	sf::Sprite m_pressAnyKey = sf::Sprite{ TextureHandle::use().getTexture(textures_type::pressSpace) };	// sprite of reflction "press space to cotinue"
	sf::Sprite m_screenShoot = sf::Sprite{ TextureHandle::use().getPrintScreen() };						// the screenShoot picture for see what was befor
	void draw() const override;
};