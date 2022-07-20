#include "GeneralObjects/State.h"
//set snake state for a specific time
void State::setState(const sf::Time& time) {
	m_state = true;
	m_stateTime = time;
}

//less time for a snake
void State::operator-=(const sf::Time& deltaTime) {
	m_stateTime -= deltaTime;
	if (m_stateTime <= sf::seconds(0)) {
		m_state = false;
	}
}