#pragma once
#include "GameObjects/StaticObjects/Gift.h"

class Clear : public Gift
{
public:
	Clear(const sf::Vector2f& pos = getRandomPosition()) : Gift(textures_type::clear, pos) {};
	~Clear() override  = default;
	void collisionHandle(CollisionHandling& collisionHandling, size_t) override {
		collisionHandling.collisionWith(*this);
	}
};

