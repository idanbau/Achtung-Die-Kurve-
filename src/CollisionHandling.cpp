#include "CollisionHandling.h"

#include "Board.h"
#include "GameObjects.hpp"
#include "FileManager/SoundHandle.h"

CollisionHandling::CollisionHandling(Board& board, std::vector<std::unique_ptr<Snake>>& snake) : m_board(board), m_snakes(snake) {};

// handle collision with specific gifts

void CollisionHandling::collisionWith(const Clear&) {
	m_board.clearLines();
	SoundHandle::use().playSound(sound_type::TakeClearGift);
}

void CollisionHandling::collisionWith(const RemoveBoundaries&, size_t index) {
	m_snakes[index]->setState(state_type::removeBoundaries);
	SoundHandle::use().playSound(sound_type::TakeGift);
}

void CollisionHandling::collisionWith(const RemoveBoundariesAll&) {
	m_board.removeBoundaries();
	SoundHandle::use().playSound(sound_type::TakeGiftAll);
}

void CollisionHandling::collisionWith(const Fast&, size_t snakeIndex){
	m_snakes[snakeIndex]->setState(state_type::fast);
	SoundHandle::use().playSound(sound_type::TakeGift);
}

void CollisionHandling::collisionWith(const FastAll&){
	setState(state_type::fast);
	SoundHandle::use().playSound(sound_type::TakeGiftAll);
}

void CollisionHandling::collisionWith(const Immortal&, size_t snakeIndex) {
	m_snakes[snakeIndex]->setState(state_type::immortal);
	SoundHandle::use().playSound(sound_type::TakeGift);
}

void CollisionHandling::collisionWith(const Slow&, size_t snakeIndex){
	m_snakes[snakeIndex]->setState(state_type::slow);
	SoundHandle::use().playSound(sound_type::TakeGift);
}

void CollisionHandling::collisionWith(const SlowAll&){
	setState(state_type::slow);
	SoundHandle::use().playSound(sound_type::TakeGiftAll);
}

void CollisionHandling::collisionWith(const Thick&, size_t snakeIndex){
	m_snakes[snakeIndex]->setState(state_type::thick);
	SoundHandle::use().playSound(sound_type::TakeGift);
}

void CollisionHandling::collisionWith(const ThickAll&){
	setState(state_type::thick);
	SoundHandle::use().playSound(sound_type::TakeGiftAll);
}

void CollisionHandling::collisionWith(const Thin&, size_t snakeIndex){
	m_snakes[snakeIndex]->setState(state_type::thin);
	SoundHandle::use().playSound(sound_type::TakeGift);
}

void CollisionHandling::collisionWith(const ThinAll&){
	setState(state_type::thin);
	SoundHandle::use().playSound(sound_type::TakeGift);
}

//set specific snake snakes gift feature
void CollisionHandling::collisionWith(const InvertMove&, size_t snakeIndex){
	m_snakes[snakeIndex]->setState(state_type::invertMove);
	SoundHandle::use().playSound(sound_type::TakeGiftAll);
}

//set all snakes gift feature
void CollisionHandling::setState(state_type type) {
	for (auto& snake : m_snakes) {
		snake->setState(type);
	}
}