#pragma once
#include "Screen.h"
#include <array>
#include "GeneralObjects/Button.h"
const auto LAUNCHER_BUTTONS = 2;

class Launcher : public Screen
{
public:
	Launcher(sf::RenderWindow& window);
	~Launcher() = default;
	screen_type run() override;
private:
	std::array<Button<screen_type>, LAUNCHER_BUTTONS> m_buttons;
	void draw() const override;
};