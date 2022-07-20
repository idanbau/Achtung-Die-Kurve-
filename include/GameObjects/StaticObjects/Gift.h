#pragma once
#include "GameObjects/GameObject.h"
#include "FileManager/TextureHandle.h"
#include "CollisionHandling.h"

class CollisionHandling;


enum class gifts_type : size_t
{
	clear, fast, fastAll, invertMove, immortal, removeBoundaries, removeBoundariesAll,
	slow, slowAll, thick, thickAll, thin, thinAll, giftsCount
};
class Gift : public GameObject
{
public:
	Gift(textures_type type, const sf::Vector2f& point = getRandomPosition());
	virtual ~Gift() = default;
	void draw(sf::RenderWindow&) const override;
	void collise(CollisionHandling& collisionHandling, size_t snakeIndex);
	sf::FloatRect getGlobalBounds() const;
	bool isTaken() const;
private:
	virtual void collisionHandle(CollisionHandling& collisionHandling, size_t) = 0;
	sf::Sprite m_gift;		// the picture
	bool m_taken = false;	// flag if taken
};

