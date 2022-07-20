#pragma once
#include "Screen.h"
#include "GeneralObjects/ColorContainer.h"
#include "GameObjects/MovingObjects/Player.h"
#include "Board.h"
#include "FileManager/FontHandle.h"
#include <array>
#include "GeneralObjects/Button.h"
#include <string>
#include <functional>

const auto PLAYER = 1;	// for mode in SnakeFactory
const auto BOT = 2;		// for mode in SnakeFactory
const auto CANCEL = 0;		// for mode in SnakeFactory
const auto NUM_OF_TYPES = 3;
const auto NEW_GAME = false;
const auto EDIT = true;

const auto EMPTY_PLACE = -1;
const auto FIRST_BUTTON = 0;


enum settings_factory_button_type : size_t
{
	type, color, name, left_key, right_key, button_count
};

class Settings : public Screen
{
public:
	Settings(sf::RenderWindow& window, std::vector<std::unique_ptr<Snake>>& snakes, const Board& board);
	screen_type run() override;
	Settings& setStatus(bool status);
	bool getStatus() const;

private:
	Button<screen_type> m_back;
	Button<screen_type> m_play;
	Button<nullptr_t> m_sound;
	sf::Sprite m_logo = sf::Sprite(TextureHandle::use().getTexture(textures_type::SettingsLogo));
	const Board& m_board;
	struct SnakeFactory
	{	// snake factory contain 5 buttons (type, color, name, leftkey, rightkey)
		SnakeFactory(Settings& settings, size_t index);
		SnakeFactory(Settings& settings, size_t index, size_t type, const sf::Color& color, const std::string& name, const sf::Keyboard::Key& leftKey, const sf::Keyboard::Key& rightKey);
		void setPosition(size_t index);
		void draw(sf::RenderWindow& window) const;
		void changeType();
		void changeColor();
		void setName();
		void changeKey(size_t key);
		void changeLeftKey();
		void changeRightKey();
		void clickUnlegulPlace();
		std::array<Button<std::function<void()>>, size_t(settings_factory_button_type::button_count)> m_buttons;
		size_t m_type;		// true = player,  false = bot;
		Settings& m_settings;
	};
	void newSnake();		// create newSnake (more SnakeFactory)
	void draw() const override;
	void executeMute();
	bool executePlay();
	void validationFailedResetPlayButton(int locationFailed);		// when press play was vaildation and is failed come this function
	size_t getVectorLocation(size_t location) const;					// get index of SnakeFactory
	size_t getButtonLocation(size_t location) const;					// get index of Button of SnakeFactory
	void setButtonMode(size_t location, ButtonType::color_type type);	
	std::vector<std::unique_ptr<Snake>>& m_snakes;
	std::vector<std::unique_ptr<SnakeFactory>> m_snakesFactory;
	std::array<sf::Text, size_t(settings_factory_button_type::button_count)> m_buttonTitle;
	bool isFactoryButton(size_t location) const;
	bool isLegulButton(size_t location) const;
	bool isContainButton(size_t location, const sf::Vector2f& mousePos) const;
	void moveHoverLeftByType();
	bool SameKey(const std::string& string) const;
	bool clickingMouseWhenWrite(sf::Event& event);
	void bildSnakeFactoryFromSnakes();
	void resetButtonDefault(size_t loaction);
	int m_hover = FIRST_BUTTON;
	int m_choosed = EMPTY_PLACE;
	bool m_status = NEW_GAME;
	ColorContainer m_colorsArray;
};