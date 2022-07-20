#pragma once
#include "GameObjects/StaticObjects/Gift.h"


class InvertMove : public Gift
{
public:
	InvertMove(const sf::Vector2f& pos = getRandomPosition()) : Gift(textures_type::reverseAll, pos) {};
	~InvertMove() override = default;
	void collisionHandle(CollisionHandling& collisionHandling, size_t index) override {
		collisionHandling.collisionWith(*this, index);
	}
};