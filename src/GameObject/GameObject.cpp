#include "GameObjects/GameObject.h"
#include "Screens/Screen.h"			// for window size

const auto OFFSET = 100.f;
const auto IN_BOARDERS = 200;
//get random positions to use when new snake;
sf::Vector2f GameObject::getRandomPosition(){
	return { (std::rand() % (WINDOW_SIZE.x - TOOLBAR_SIZE.x - IN_BOARDERS)) + OFFSET, (std::rand() % (WINDOW_SIZE.y - IN_BOARDERS)) + OFFSET };
}
