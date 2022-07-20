#pragma once
#include "GameObjects\GameObject.h"
#include <optional>
#include "GameObjects/StaticObjects/Gift.h"
#include "GeneralObjects/State.h"
#include "Utilities.h"

enum class state_type : size_t
{
	fast, invertMove, immortal, removeBoundaries, slow, squareMove, thick, thin, stateCount
};

const auto ANGLE = 3.f;
const auto SPEED_REFLECTION = 10;
const auto SPEED = 120.f;


class Snake : public GameObject
{
public:
	Snake(const sf::Color& color, const std::string& name);
	virtual ~Snake() = default;
	void draw(sf::RenderWindow&) const override;
	void move(const sf::Time& deltaTime);
	void setPosition(const sf::Vector2f& pos);
	std::optional<std::pair<sf::Vertex, sf::Vertex>> addVertices(bool draw);
	size_t getScore() const;
	void addScore();
	void resetSetting();
	const sf::CircleShape& getHead() const;
	const sf::Color& getColor() const;
	bool alive() const;
	void kill();
	const std::string& getName() const;
	void setState(state_type type);
	void setName(const std::string &name);
	void setColor(const sf::Color &color);
	bool getState(state_type type) const;
protected:
	sf::CircleShape m_head;					// the head of snake
	virtual void changeDirection(const sf::Time& deltaTime) = 0;
	void rotate(const float& angle, const sf::Time& Deltatime);
private:
	std::array <State, (size_t)state_type::stateCount> m_states;
	sf::Color m_color;				// color for snake line
	size_t m_score = 0;				// score
	sf::Vector2f m_lastPos;			// last poistion of snake (because have times that lo draw vertices)
	bool m_alive = true;			// flag if is alive
	std::string m_name;				// name of snake player
	int m_headReflection = MIN_REFLECTION;		// for when reflection (state of baoundries)
	int m_speedReflection = SPEED_REFLECTION;	// for when reflection (state of baoundries)

	void handleStates(const sf::Time& deltaTime);
	void resetStates();
};