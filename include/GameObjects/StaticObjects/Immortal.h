#pragma once
#include "GameObjects/StaticObjects/Gift.h"


class Immortal : public Gift
{
public:
	Immortal(const sf::Vector2f& pos = getRandomPosition()) : Gift(textures_type::immortal, pos) {};
	~Immortal() override = default;
	void collisionHandle(CollisionHandling& collisionHandling, size_t index) override {
		collisionHandling.collisionWith(*this, index);
	}
};