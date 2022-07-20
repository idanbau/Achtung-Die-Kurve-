#pragma once
#include "GameObjects/StaticObjects/Gift.h"


class ThickAll : public Gift
{
public:
	ThickAll(const sf::Vector2f& pos = getRandomPosition()) : Gift(textures_type::thickAll, pos) {};
	~ThickAll() override = default;
	void collisionHandle(CollisionHandling& collisionHandling, size_t) override {
		collisionHandling.collisionWith(*this);
	}
};