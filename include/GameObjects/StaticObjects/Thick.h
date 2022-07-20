#pragma once
#include "GameObjects/StaticObjects/Gift.h"


class Thick : public Gift
{
public:
	Thick(const sf::Vector2f& pos = getRandomPosition()) : Gift(textures_type::thick, pos) {};
	~Thick() override = default;
	void collisionHandle(CollisionHandling& collisionHandling, size_t index) override {
		collisionHandling.collisionWith(*this, index);
	}
};