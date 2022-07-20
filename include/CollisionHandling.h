#pragma once


#include <iostream>
#include <typeinfo>
#include <vector>
#include <memory>

// forward declartion
class Snake;
class Board;
class Clear;
class RemoveBoundaries;
class RemoveBoundariesAll;
class Fast;
class FastAll;
class Immortal;
class Slow;
class SlowAll;
class Thick;
class ThickAll;
class Thin;
class ThinAll;
class Invisible;
class InvisibleAll;
class InvertMove;
class InvertMoveAll;
enum class state_type : size_t;


class CollisionHandling
{
public:
    CollisionHandling(Board& board, std::vector<std::unique_ptr<Snake>>& snake);
    void collisionWith(const Clear& clear);
    void collisionWith(const RemoveBoundaries& removeBoundaries, size_t snakeIndex);
    void collisionWith(const RemoveBoundariesAll& removeBoundaries);
    void collisionWith(const Fast& fast, size_t snakeIndex);
    void collisionWith(const FastAll& fastAll);
    void collisionWith(const Immortal& immotal, size_t snakeIndex);
    void collisionWith(const Slow& slow, size_t snakeIndex);
    void collisionWith(const SlowAll& slowAll);
    void collisionWith(const Thick& thick, size_t snakeIndex);
    void collisionWith(const ThickAll& thickAll);
    void collisionWith(const Thin& thin, size_t snakeIndex);
    void collisionWith(const ThinAll& thinAll);
    void collisionWith(const InvertMove& invertMove, size_t snakeIndex);

private:
    void setState(state_type type);
    Board& m_board;
    std::vector<std::unique_ptr<Snake>>& m_snakes;
};