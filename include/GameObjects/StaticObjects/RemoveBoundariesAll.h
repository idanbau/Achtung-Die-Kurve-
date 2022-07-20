#pragma once
#include "GameObjects/StaticObjects/Gift.h"


class RemoveBoundariesAll : public Gift
{
public:
	RemoveBoundariesAll(const sf::Vector2f& pos = getRandomPosition()) : Gift(textures_type::boundariesAll, pos) {};
	~RemoveBoundariesAll() override = default;
	void collisionHandle(CollisionHandling& collisionHandling, size_t) override {
		collisionHandling.collisionWith(*this);
	}
};