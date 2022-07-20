#pragma once
#include "GameObjects/StaticObjects/Gift.h"


class FastAll : public Gift {
public:
	FastAll(const sf::Vector2f& pos = getRandomPosition()) : Gift(textures_type::speedUpAll, pos) {};
	~FastAll() override = default;
	void collisionHandle(CollisionHandling& collisionHandling, size_t) override {
		collisionHandling.collisionWith(*this);
	}
};