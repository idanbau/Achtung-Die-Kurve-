#pragma once
#include <SFML/Graphics.hpp>

const auto STATE_TIME = 5.f;
struct State
{
	void setState(const sf::Time& time = sf::seconds(STATE_TIME));
	void operator-=(const sf::Time& deltaTime);
	bool m_state = false;
	sf::Time m_stateTime = sf::seconds(0.f);
};