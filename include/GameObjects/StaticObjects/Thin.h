#pragma once
#include "GameObjects/StaticObjects/Gift.h"


class Thin : public Gift
{
public:
	Thin(const sf::Vector2f& pos = getRandomPosition()) : Gift(textures_type::thin, pos) {};
	~Thin() override = default;
	void collisionHandle(CollisionHandling& collisionHandling, size_t index) override {
		collisionHandling.collisionWith(*this, index);
	}
};