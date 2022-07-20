#include "GameObjects/StaticObjects/Gift.h"
#include "Utilities.h"

const auto SCALE = sf::Vector2f{ 0.5f, 0.5f };

Gift::Gift(textures_type type, const sf::Vector2f& point): m_gift(TextureHandle::use().getTexture(textures_type(size_t(type))))
{
	m_gift.scale(SCALE);
	setOriginCenter(m_gift);
	m_gift.setPosition(point);
}
//draw gift
void Gift::draw(sf::RenderWindow& window) const{
	window.draw(m_gift);
}
	
//check if gift was taken or not
bool Gift::isTaken() const {
	return m_taken;
}

// collise with some gift
void Gift::collise(CollisionHandling& collisionHandling, size_t snakeIndex) {
	m_taken = true;
	collisionHandle(collisionHandling, snakeIndex);	// call virtual specific gift and than obj CollisionHandling will handle this gift
}

// for check collise
sf::FloatRect Gift::getGlobalBounds() const {
	return m_gift.getGlobalBounds();
}
