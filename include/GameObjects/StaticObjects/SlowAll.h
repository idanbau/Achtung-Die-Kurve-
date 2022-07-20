#pragma once
#include "GameObjects/StaticObjects/Gift.h"


class SlowAll : public Gift
{
public:
	SlowAll(const sf::Vector2f& pos = getRandomPosition()) : Gift(textures_type::speedDownAll, pos) {};
	~SlowAll() override = default;
	void collisionHandle(CollisionHandling& collisionHandling, size_t) override {
		collisionHandling.collisionWith(*this);
	}
};