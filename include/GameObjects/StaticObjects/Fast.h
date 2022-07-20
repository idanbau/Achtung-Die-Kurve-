#pragma once
#include "GameObjects/StaticObjects/Gift.h"


class Fast : public Gift {
public:
	Fast(const sf::Vector2f& pos = getRandomPosition()) : Gift(textures_type::speedUp, pos) {};
	~Fast() override = default;
	void collisionHandle(CollisionHandling& collisionHandling, size_t index) override {
		collisionHandling.collisionWith(*this, index);
	}
};