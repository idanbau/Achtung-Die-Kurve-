#pragma once
#include "GameObjects/StaticObjects/Gift.h"


class ThinAll : public Gift
{
public:
	ThinAll(const sf::Vector2f& pos = getRandomPosition()) : Gift(textures_type::thinAll, pos) {};
	~ThinAll() override = default;
	void collisionHandle(CollisionHandling& collisionHandling, size_t) override {
		collisionHandling.collisionWith(*this);
	}
};