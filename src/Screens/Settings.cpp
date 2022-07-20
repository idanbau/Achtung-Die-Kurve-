#include "Screens\Settings.h"
#include "Utilities.h"


const auto TYPE_TITLE = "Type";
const auto COLOR_TITLE = "Color";
const auto NAME_TITLE = "Name";
const auto LEFT_KEY_TITLE = "Left";
const auto RIGHT_KEY_TITLE = "Right";

const auto MIN_SNAKES = 2;

const auto WAS_EVENT = true;
const auto WAS_NO_EVENT = false;

const auto ROW_BUFFER = 50.f; // buffer between setting of snake
const auto WIDTH_BUFFER = 20.f; // buffer between button

const auto MENU = "Menu";
const auto PLAY = "Play";
const auto SOUND_ON = "Sound ON";
const auto SOUND_OFF = "Sound OFF";

const auto& BASE_COLOR = sf::Color::Cyan;
const auto& CHOOSEN_COLOR = sf::Color::Blue;

const auto BUTTON_X_POSITIONS = std::array<float, size_t(settings_factory_button_type::button_count)>{50.f, 120.f, 330.f, 570.f, 700.f};
const auto START_HEIGHT = 250.f;
const auto TITLE_HEIGHT = 210.f;
const auto BUTTON_HEIGHT = 40.f;

const auto CHAR_PLAYER = "P";
const auto CHAR_BOT = "B";
const auto CHAR_CANCEL = "C";
const auto& COLOR_CANCEL = sf::Color::Black;
const auto& COLOR_PLAYER = sf::Color::Red;
const auto& COLOR_BOT = sf::Color::Green;


const auto MAX_NAME_LEN = 10;

const auto ENTER = 13;
const auto ESCAPE = 27;
const auto BACKSPACE = 8;

static auto NUM_OF_SNAKES_FACTORY = 8;
static auto NUM_OF_FACTORY_BUTTONS = int(size_t(settings_factory_button_type::button_count) * NUM_OF_SNAKES_FACTORY);
static auto NUM_OF_BUTTONS = NUM_OF_FACTORY_BUTTONS + 3;
static auto BUTTON_MUTE_LOCATION = NUM_OF_FACTORY_BUTTONS;
static auto BUTTON_BACK_LOCATION = NUM_OF_FACTORY_BUTTONS + 1;
static auto BUTTON_PLAY_LOCATION = NUM_OF_FACTORY_BUTTONS + 2;
//------------------------------------------------------------------ Settings::SankeFactory -------------------------------------------------------------------

Settings::SnakeFactory::SnakeFactory(Settings& settings, size_t index) : m_settings(settings), m_type(CANCEL),
m_buttons({
	// type button
	Button<std::function<void()>>{ [this]() { changeType(); } ,
		{ BUTTON_X_POSITIONS[size_t(settings_factory_button_type::type)], index * ROW_BUFFER + START_HEIGHT },	// location
		CHAR_CANCEL, font_type::font2, { 50.f, BUTTON_HEIGHT }, COLOR_CANCEL },

		// color button
		Button<std::function<void()>>{ [this]() {changeColor(); } ,
			{ BUTTON_X_POSITIONS[size_t(settings_factory_button_type::color)], index * ROW_BUFFER + START_HEIGHT },	// location
		"", font_type::font2, { 50.f, BUTTON_HEIGHT }, CHOOSEN_COLOR },

		// name button
		Button<std::function<void()>>{ [this]() {setName(); } ,
			{ BUTTON_X_POSITIONS[size_t(settings_factory_button_type::name)], index * ROW_BUFFER + START_HEIGHT },	// location
		"", font_type::font2, { 300.f, BUTTON_HEIGHT }, { BASE_COLOR, BASE_COLOR,  CHOOSEN_COLOR} },

		// leftKey button
		Button<std::function<void()>>{ [this]() {changeLeftKey(); } ,
			{ BUTTON_X_POSITIONS[size_t(settings_factory_button_type::left_key)], index * ROW_BUFFER + START_HEIGHT },	// location
		"", font_type::font2, { 110.f, BUTTON_HEIGHT }, { BASE_COLOR, BASE_COLOR,  CHOOSEN_COLOR} },

		// rightKey button
		Button<std::function<void()>>{ [this]() {changeRightKey(); } ,
			{ BUTTON_X_POSITIONS[size_t(settings_factory_button_type::right_key)], index * ROW_BUFFER + START_HEIGHT },	// location
		"", font_type::font2, { 110.f, BUTTON_HEIGHT }, { BASE_COLOR, BASE_COLOR,  CHOOSEN_COLOR} }

	}) {};


Settings::SnakeFactory::SnakeFactory(Settings& settings, size_t index, size_t type, const sf::Color& color, const std::string& name, const sf::Keyboard::Key& leftKey, const sf::Keyboard::Key& rightKey)
	: m_settings(settings), m_type(type),
	m_buttons(std::array<Button<std::function<void()>>, size_t(settings_factory_button_type::button_count)>{
	// type button
	Button<std::function<void()>>{ [this]() { clickUnlegulPlace(); },
		{ BUTTON_X_POSITIONS[size_t(settings_factory_button_type::type)], index * ROW_BUFFER + START_HEIGHT },	// location
		type == PLAYER ? CHAR_PLAYER : CHAR_BOT, font_type::font2, { 50.f, BUTTON_HEIGHT }, type == PLAYER ? COLOR_PLAYER : COLOR_BOT},

		// color button
		Button<std::function<void()>>{ [this]() {changeColor(); },
			{ BUTTON_X_POSITIONS[size_t(settings_factory_button_type::color)], index * ROW_BUFFER + START_HEIGHT },	// location
		"", font_type::font2, { 50.f, BUTTON_HEIGHT }, color },

		// name button
		Button<std::function<void()>>{ [this]() {setName(); },
			{ BUTTON_X_POSITIONS[size_t(settings_factory_button_type::name)], index * ROW_BUFFER + START_HEIGHT },	// location
		name, font_type::font2, { 300.f, BUTTON_HEIGHT }, { BASE_COLOR, BASE_COLOR,  CHOOSEN_COLOR } },

		// leftKey button
		Button<std::function<void()>>{ [this]() {changeLeftKey(); },
			{ BUTTON_X_POSITIONS[size_t(settings_factory_button_type::left_key)], index * ROW_BUFFER + START_HEIGHT },	// location
		getKeyString(leftKey), font_type::font2, { 110.f, BUTTON_HEIGHT }, { BASE_COLOR, BASE_COLOR,  CHOOSEN_COLOR } },

		// rightKey button
		Button<std::function<void()>>{ [this]() {changeRightKey(); },
			{ BUTTON_X_POSITIONS[size_t(settings_factory_button_type::right_key)], index * ROW_BUFFER + START_HEIGHT },	// location
		getKeyString(rightKey), font_type::font2, { 110.f, BUTTON_HEIGHT }, { BASE_COLOR, BASE_COLOR,  CHOOSEN_COLOR } }

})
{}

// will need it when delete from vector
void Settings::SnakeFactory::setPosition(size_t index) {
	for (size_t i = 0; i < m_buttons.size(); ++i) {
		m_buttons[i].setPosition(sf::Vector2f(BUTTON_X_POSITIONS[i], index * ROW_BUFFER + START_HEIGHT));
	}
}

void Settings::SnakeFactory::draw(sf::RenderWindow& window) const {
	for (size_t i = 0; i < m_buttons.size(); ++i) {
		if ((m_type == BOT && i >= size_t(settings_factory_button_type::left_key)) || (m_type == CANCEL && i >= size_t(settings_factory_button_type::color))) {
			break;
		}
		window.draw(m_buttons[i]);
	}
}

void Settings::SnakeFactory::changeKey(size_t key) {
	m_settings.draw();
	while (m_settings.m_window.isOpen()) {
		if (auto event = sf::Event{}; m_settings.m_window.waitEvent(event)) {
			if (event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Key::Enter:
				case sf::Keyboard::Key::Escape:
				case sf::Keyboard::Key::Space:
					m_settings.setButtonMode(m_settings.m_choosed, ButtonType::color_type::hover);
					m_settings.m_choosed = EMPTY_PLACE;
					return;
				default:
					auto current = getKeyString(event.key.code);
					m_buttons[key].setString(m_settings.SameKey(current) ? "" : current);
					if (m_settings.m_hover == m_settings.m_choosed)
						m_settings.setButtonMode(m_settings.m_choosed, ButtonType::color_type::hover);
					else
						m_settings.setButtonMode(m_settings.m_choosed, ButtonType::color_type::regular);
					m_settings.m_choosed = EMPTY_PLACE;
					return;
				}
			}
			if (m_settings.clickingMouseWhenWrite(event) == WAS_EVENT) {
				return;
			}
		}
	}
}

void Settings::SnakeFactory::changeLeftKey() {
	changeKey(size_t(settings_factory_button_type::left_key));//const 3 left key
}

void Settings::SnakeFactory::changeRightKey() {
	changeKey(size_t(settings_factory_button_type::right_key));//const 4 right key
}

void Settings::SnakeFactory::clickUnlegulPlace(){
	m_settings.setButtonMode(m_settings.m_choosed, ButtonType::color_type::hover);
	m_settings.m_choosed = EMPTY_PLACE;
	SoundHandle::use().playSound(sound_type::clickUnLegul);
}

void Settings::SnakeFactory::changeType() {
	m_type = (m_type + 1) % NUM_OF_TYPES;
	switch (m_type)
	{
	case CANCEL:
		m_settings.m_colorsArray.releaseColor(m_buttons[size_t(settings_factory_button_type::color)].getColor());
		m_buttons[size_t(settings_factory_button_type::type)].setColor(COLOR_CANCEL);
		for (auto& button : m_buttons)
			button.clear();
		m_buttons[size_t(settings_factory_button_type::type)].setString(CHAR_CANCEL);
		break;
	case PLAYER:
		m_buttons[size_t(settings_factory_button_type::type)].setColor(COLOR_PLAYER);
		m_buttons[size_t(settings_factory_button_type::type)].setString(CHAR_PLAYER);
		m_buttons[size_t(settings_factory_button_type::color)].setColor(m_settings.m_colorsArray.useColor());
		break;
	case BOT:
		m_buttons[size_t(settings_factory_button_type::type)].setColor(COLOR_BOT);
		m_buttons[size_t(settings_factory_button_type::type)].setString(CHAR_BOT);
		m_buttons[(size_t)settings_factory_button_type::left_key].clear();
		m_buttons[(size_t)settings_factory_button_type::right_key].clear();
		break;
	default: throw std::out_of_range("Invalid snake type");
	}
	m_settings.setButtonMode(m_settings.m_choosed, ButtonType::color_type::hover);
	m_settings.m_choosed = EMPTY_PLACE;
}

void Settings::SnakeFactory::setName() {
	auto name = m_buttons[size_t(settings_factory_button_type::name)].getString();
	while (m_settings.m_window.isOpen()) {
		m_settings.draw();
		m_settings.m_window.draw(m_buttons[size_t(settings_factory_button_type::name)]);
		if (auto event = sf::Event{}; m_settings.m_window.waitEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed:
				m_settings.m_window.close();
				return;
			case sf::Event::TextEntered:
			{
				if (event.text.unicode < 128)
				{
					switch (event.text.unicode)
					{
					case ENTER:
						m_settings.m_window.waitEvent(event);	// eat the event new line
						[[fallthrough]]; // fallthrough for no warning
					case ESCAPE:
						m_settings.setButtonMode(m_settings.m_choosed, ButtonType::color_type::hover);
						m_settings.m_choosed = EMPTY_PLACE;
						return;
					case BACKSPACE:
						if (!name.isEmpty()) {
							name.erase(name.getSize() - 1, 1);
							m_buttons[size_t(settings_factory_button_type::name)].setString(name);
						}
						break;
					default:
						if (name.getSize() < MAX_NAME_LEN) {
							name += event.text.unicode; 
							m_buttons[size_t(settings_factory_button_type::name)].setString(name);
						}
						break;
					}
				}
				break;
			}
			}
			if (m_settings.clickingMouseWhenWrite(event) == WAS_EVENT) {
				return;
			}
		}
	}
}

void Settings::SnakeFactory::changeColor() {
	m_buttons[size_t(settings_factory_button_type::color)].setColor(m_settings.m_colorsArray.releaseColor(m_buttons[size_t(settings_factory_button_type::color)].getColor()).useColor());
	m_settings.setButtonMode(m_settings.m_choosed, ButtonType::color_type::hover);
	m_settings.m_choosed = EMPTY_PLACE;
}


//------------------------------------------------------------------ Settings -------------------------------------------------------------------


Settings::Settings(sf::RenderWindow& window, std::vector<std::unique_ptr<Snake>>& snakes, const Board& board) : Screen(window), m_snakes(snakes), m_board(board),
m_back(Button{
	screen_type::launcher, { WINDOW_SIZE.x / 2.f - 250.f , WINDOW_SIZE.y - 30.f},	// location
	MENU, font_type::font2, { 200.f, 50.f }, { sf::Color::Red, sf::Color::Blue,  sf::Color::Black } }),

	m_play(Button{
		screen_type::back, { WINDOW_SIZE.x / 2.f + 250.f , WINDOW_SIZE.y - 30.f },	// location
		PLAY, font_type::font2, { 200.f, 50.f }, { sf::Color::Red, sf::Color::Blue,  sf::Color::Black } }),

		m_sound(Button{
		nullptr, { WINDOW_SIZE.x / 2.f - 250.f, WINDOW_SIZE.y - 100.f},	// location
		SoundHandle::use().getPauseStatus() ? SOUND_OFF : SOUND_ON , font_type::font2, { 200.f, 50.f }, SoundHandle::use().getPauseStatus() ? sf::Color::Red : sf::Color::Green }),

		m_buttonTitle({
		sf::Text(TYPE_TITLE, FontHandle::use().getFont(font_type::font2), 20),
		sf::Text(COLOR_TITLE, FontHandle::use().getFont(font_type::font2), 20),
		sf::Text(NAME_TITLE, FontHandle::use().getFont(font_type::font2), 20),
		sf::Text(LEFT_KEY_TITLE, FontHandle::use().getFont(font_type::font2), 20),
		sf::Text(RIGHT_KEY_TITLE, FontHandle::use().getFont(font_type::font2), 20)
			})
{
	m_logo.scale(0.75f, 0.75f);
	m_logo.setPosition(WINDOW_SIZE.x - m_logo.getGlobalBounds().width, (WINDOW_SIZE.y - m_logo.getGlobalBounds().height) / 2.f);
	for (size_t i = 0; i < m_buttonTitle.size(); ++i) {
		setOriginCenter(m_buttonTitle[i]);
		m_buttonTitle[i].setPosition(BUTTON_X_POSITIONS[i], TITLE_HEIGHT);
	}
};

screen_type Settings::run() {
	m_snakesFactory.clear();
	if (m_status == NEW_GAME) {
		NUM_OF_SNAKES_FACTORY = 8;
		NUM_OF_FACTORY_BUTTONS = int(size_t(settings_factory_button_type::button_count) * NUM_OF_SNAKES_FACTORY);
		NUM_OF_BUTTONS = NUM_OF_FACTORY_BUTTONS + 3;
		BUTTON_MUTE_LOCATION = NUM_OF_FACTORY_BUTTONS;
		BUTTON_BACK_LOCATION = NUM_OF_FACTORY_BUTTONS + 1;
		BUTTON_PLAY_LOCATION = NUM_OF_FACTORY_BUTTONS + 2;
		m_colorsArray.clear();
		for (size_t i = 0; i < NUM_OF_SNAKES_FACTORY; ++i) {
			newSnake();
		}
	}
	else {
		NUM_OF_SNAKES_FACTORY = int (m_snakes.size());
		NUM_OF_FACTORY_BUTTONS = int(size_t(settings_factory_button_type::button_count) * NUM_OF_SNAKES_FACTORY);
		NUM_OF_BUTTONS = NUM_OF_FACTORY_BUTTONS + 3;
		BUTTON_MUTE_LOCATION = NUM_OF_FACTORY_BUTTONS;
		BUTTON_BACK_LOCATION = NUM_OF_FACTORY_BUTTONS + 1;
		BUTTON_PLAY_LOCATION = NUM_OF_FACTORY_BUTTONS + 2;
		bildSnakeFactoryFromSnakes();
	}

	m_choosed = EMPTY_PLACE;
	m_hover = FIRST_BUTTON;
	setButtonMode(m_hover, ButtonType::color_type::hover);
	while (m_window.isOpen()) {
		draw();
		if (auto event = sf::Event{}; m_window.waitEvent(event)) {
			if (m_choosed == EMPTY_PLACE) {

				switch (event.type)
				{
				case sf::Event::Closed:
					m_window.close();
					break;
				case sf::Event::MouseMoved:
				{
					auto location = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
					for (int i = FIRST_BUTTON; i < NUM_OF_BUTTONS; ++i) {
						if (isContainButton(i, location)) {
							if (m_hover != i) {
								setButtonMode(m_hover, ButtonType::color_type::regular);
								m_hover = i;
								setButtonMode(m_hover, ButtonType::color_type::hover);
								break;
							}
							else {
								break;
							}
						}
					}
					break;
				}
				case sf::Event::MouseButtonReleased:
				{
					auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
					for (int i = FIRST_BUTTON; i < NUM_OF_BUTTONS; ++i) {
						if (isContainButton(i, location)) {
							setButtonMode(m_hover, ButtonType::color_type::regular);
							m_choosed = m_hover = i;
							setButtonMode(m_choosed, ButtonType::color_type::choosed);
							break;
						}
					}

					break;
				}
				case sf::Event::KeyReleased:
				{
					switch (event.key.code)
					{

					case sf::Keyboard::Key::Up:
						setButtonMode(m_hover, ButtonType::color_type::regular);
						if (isFactoryButton(m_hover)) {
							m_hover -= size_t(settings_factory_button_type::button_count);
							if (m_hover < 0) {
								m_hover = BUTTON_PLAY_LOCATION;
							}
							else {
								moveHoverLeftByType();
							}
						}
						else {
							--m_hover;
							if (isFactoryButton(m_hover)) {
								moveHoverLeftByType();
							}
						}
						setButtonMode(m_hover, ButtonType::color_type::hover);
						break;

					case sf::Keyboard::Key::Down:
						setButtonMode(m_hover, ButtonType::color_type::regular);
						if (isFactoryButton(m_hover)) {
							if (getVectorLocation(m_hover) <= NUM_OF_SNAKES_FACTORY - 2) {
								m_hover += size_t(settings_factory_button_type::button_count);
								moveHoverLeftByType();
							}
							else {
								m_hover = BUTTON_MUTE_LOCATION;
							}
						}
						else {
							m_hover = (m_hover + 1) % NUM_OF_BUTTONS;
						}
						setButtonMode(m_hover, ButtonType::color_type::hover);
						break;

					case sf::Keyboard::Key::Left:
						setButtonMode(m_hover, ButtonType::color_type::regular);
						m_hover = (m_hover + NUM_OF_BUTTONS - 1) % NUM_OF_BUTTONS;
						if (isFactoryButton(m_hover)) {
							if (m_snakesFactory[getVectorLocation(m_hover)]->m_type == BOT && getButtonLocation(m_hover) == settings_factory_button_type::right_key) {
								m_hover -= 2;
							}
							else if (m_snakesFactory[getVectorLocation(m_hover)]->m_type == CANCEL && getButtonLocation(m_hover) == settings_factory_button_type::right_key) {
								m_hover -= 4;
							}
						}
						setButtonMode(m_hover, ButtonType::color_type::hover);
						break;

					case sf::Keyboard::Key::Right:
						setButtonMode(m_hover, ButtonType::color_type::regular);
						m_hover = (m_hover + 1) % NUM_OF_BUTTONS;
						if (isFactoryButton(m_hover)) {
							if (m_snakesFactory[getVectorLocation(m_hover)]->m_type == BOT && getButtonLocation(m_hover) == settings_factory_button_type::left_key) {
								m_hover += 2;
							}
							else if (m_snakesFactory[getVectorLocation(m_hover)]->m_type == CANCEL && getButtonLocation(m_hover) == settings_factory_button_type::color) {
								m_hover += 4;
							}
						}
						setButtonMode(m_hover, ButtonType::color_type::hover);
						break;

					case sf::Keyboard::Key::Enter:
						m_choosed = m_hover;
						setButtonMode(m_choosed, ButtonType::color_type::choosed);
						break;
					}
				}
				}
			}
			if (m_choosed != EMPTY_PLACE) {	// check again if change send the event
				if (m_choosed == BUTTON_MUTE_LOCATION) {
					executeMute();
				}
				else if (m_choosed == BUTTON_BACK_LOCATION) {
					resetButtonDefault(m_choosed);
					m_status = NEW_GAME;
					m_snakes.clear();
					m_snakesFactory.clear();
					return m_back.getT();
				}
				else if (m_choosed == BUTTON_PLAY_LOCATION) {
					if (executePlay()) {
						resetButtonDefault(m_choosed);
						return m_play.getT();
					}
				}
				else {
					m_snakesFactory[getVectorLocation(m_choosed)]->m_buttons[getButtonLocation(m_choosed)].getT()();
				}
			}
		}
	}
	return screen_type::back;
}

// create new sanke to SnakeFactory
void Settings::newSnake() {
	m_snakesFactory.emplace_back(std::make_unique<SnakeFactory>(*this, m_snakesFactory.size()));
}

void Settings::draw() const {
	m_window.clear();
	m_window.draw(m_background);
	m_window.draw(m_logo);
	for (const auto& title : m_buttonTitle) {
		m_window.draw(title);
	}
	for (const auto& snakeFactory : m_snakesFactory) {
		snakeFactory->draw(m_window);
	}
	m_window.draw(m_back);
	m_window.draw(m_play);
	m_window.draw(m_sound);
	m_window.display();
}

// button mute is pressed
void Settings::executeMute() {
	SoundHandle::use().pausePlay();
	if (SoundHandle::use().getPauseStatus()) {	// mute
		m_sound.setString(SOUND_OFF);
		m_sound.setColor(sf::Color::Red);
	}
	else {
		m_sound.setString(SOUND_ON);
		m_sound.setColor(sf::Color::Green);
	}
	m_choosed = EMPTY_PLACE;
}

// button play is pressed need check balidation and create snakes
bool Settings::executePlay() {
	if (m_status == NEW_GAME) {
		m_snakes.clear();
		auto numOfSankeFactory = 0;
		for (const auto& snakeFactory : m_snakesFactory) {
			if (snakeFactory->m_type != CANCEL)
				++numOfSankeFactory;
		}
		if (numOfSankeFactory < MIN_SNAKES) {
			validationFailedResetPlayButton(0);
			return false;
		}
	}
	// check validation keys
	for (size_t i = FIRST_BUTTON; i < m_snakesFactory.size(); ++i) {
		if (m_snakesFactory[i]->m_type == CANCEL)
			continue;
		auto size = m_snakesFactory[i]->m_type == PLAYER ? size_t(settings_factory_button_type::button_count) :
			size_t(settings_factory_button_type::left_key);
		for (auto j = size_t(settings_factory_button_type::name); j < size; ++j) {
			if (m_snakesFactory[i]->m_buttons[j].empty()) {
				validationFailedResetPlayButton(int(i * size_t(settings_factory_button_type::button_count) + j));
				return false;
			}
		}
	}
	for (size_t i = 0; i < m_snakesFactory.size(); ++i) {
		if (m_status == NEW_GAME) {
			if (m_snakesFactory[i]->m_type == CANCEL)
				continue;
			if (m_snakesFactory[i]->m_type == PLAYER) {
				m_snakes.emplace_back(std::make_unique<Player>(m_snakesFactory[i]->m_buttons[settings_factory_button_type::color].getColor(),
					m_snakesFactory[i]->m_buttons[settings_factory_button_type::name].getString().toAnsiString(),
					getKey(m_snakesFactory[i]->m_buttons[settings_factory_button_type::left_key].getString().toAnsiString()),
					getKey(m_snakesFactory[i]->m_buttons[settings_factory_button_type::right_key].getString().toAnsiString())
					));
			}
			else {
				m_snakes.emplace_back(std::make_unique<Bot>(m_snakesFactory[i]->m_buttons[settings_factory_button_type::color].getColor(),
					m_snakesFactory[i]->m_buttons[settings_factory_button_type::name].getString().toAnsiString(), m_board));
			}
		}
		else {	// is edit
			m_snakes[i]->setName(m_snakesFactory[i]->m_buttons[settings_factory_button_type::name].getString().toAnsiString());
			m_snakes[i]->setColor(m_snakesFactory[i]->m_buttons[settings_factory_button_type::color].getColor());
			if (auto playerPtr = dynamic_cast<Player*>(m_snakes[i].get()); playerPtr) {
				playerPtr->setLeft(getKey(m_snakesFactory[i]->m_buttons[settings_factory_button_type::left_key].getString().toAnsiString()));
				playerPtr->setRight(getKey(m_snakesFactory[i]->m_buttons[settings_factory_button_type::right_key].getString().toAnsiString()));
			}
		}
	}
	return true;
}

// when press play was vaildation and is failed come this function
void Settings::validationFailedResetPlayButton(int locationFailed) {
	setButtonMode(m_choosed, ButtonType::color_type::regular);
	m_choosed = EMPTY_PLACE;
	m_hover = locationFailed;
	setButtonMode(m_hover, ButtonType::color_type::hover);
	SoundHandle::use().playSound(sound_type::clickUnLegul);
}

// get index of SnakeFactory
size_t Settings::getVectorLocation(size_t location) const {
	return location / size_t(settings_factory_button_type::button_count);
}

// get index of Button of SnakeFactory
size_t Settings::getButtonLocation(size_t location) const {
	return location % size_t(settings_factory_button_type::button_count);
}

// set specific button this mode
void Settings::setButtonMode(size_t location, ButtonType::color_type type) {
	if (location == BUTTON_MUTE_LOCATION) {
		m_sound.setMode(type);
	}
	else if (location == BUTTON_BACK_LOCATION) {
		m_back.setMode(type);
	}
	else if (location == BUTTON_PLAY_LOCATION) {
		m_play.setMode(type);
	}
	else {
		m_snakesFactory[getVectorLocation(location)]->m_buttons[getButtonLocation(location)].setMode(type);
	}
}


// move the hover left when continue with keyboard and come to unlegul button (bacouse CANCEL or BOT type)
void Settings::moveHoverLeftByType() {
	if (m_snakesFactory[getVectorLocation(m_hover)]->m_type != PLAYER) {
		auto timesLeft = m_snakesFactory[getVectorLocation(m_hover)]->m_type == BOT ? size_t(settings_factory_button_type::name)
			: size_t(settings_factory_button_type::type);
		while (true) {
			if (getButtonLocation(m_hover) <= timesLeft) {
				break;
			}
			--m_hover;
		}
	}
}

// check if used same keys befor (on other players)
bool Settings::SameKey(const std::string& string) const {
	for (const auto& current : m_snakesFactory)
		if (current->m_type == CANCEL || current->m_type == BOT)
			continue;
		else if (current->m_buttons[left_key].getString().toAnsiString() == string || current->m_buttons[right_key].getString().toAnsiString() == string)
			return true;
	return false;
}

// check if is factory button
bool Settings::isFactoryButton(size_t location) const {
	return location < NUM_OF_FACTORY_BUTTONS;
}

// check if is legul button of m_snakesFactory keys not activate of BOT type and CANCEL
bool Settings::isLegulButton(size_t location) const {
	return (m_snakesFactory[getVectorLocation(location)]->m_type == PLAYER
		|| m_snakesFactory[getVectorLocation(location)]->m_type == BOT && getButtonLocation(location) < size_t(settings_factory_button_type::left_key))
		|| (m_snakesFactory[getVectorLocation(location)]->m_type == CANCEL && getButtonLocation(location) < size_t(settings_factory_button_type::color));
}

// check if mouse position is contain any button
bool Settings::isContainButton(size_t location, const sf::Vector2f& mousePos) const {
	if (location >= NUM_OF_FACTORY_BUTTONS) {
		if (location == BUTTON_MUTE_LOCATION) {
			return m_sound.isContain(mousePos);
		}
		else if (location == BUTTON_BACK_LOCATION) {
			return m_back.isContain(mousePos);
		}
		else if (location == BUTTON_PLAY_LOCATION) {
			return m_play.isContain(mousePos);
		}
	}
	else {
		return (isLegulButton(location) && m_snakesFactory[getVectorLocation(location)]->m_buttons[getButtonLocation(location)].isContain(mousePos));
	}
	return false;
}


// handle specific event MouseButtonPressed (calling this when writing name or keys if want to leave is button this function will do it)
bool Settings::clickingMouseWhenWrite(sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
		for (int i = FIRST_BUTTON; i < NUM_OF_BUTTONS; ++i) {
			if (isContainButton(i, location)) {
				setButtonMode(m_choosed, ButtonType::color_type::regular);
				if (m_choosed == i) {
					m_choosed = EMPTY_PLACE;
					m_window.waitEvent(event);		// eat event sf::MouseButtonReleased
				}
				else {
					m_choosed = m_hover = i;
					setButtonMode(m_choosed, ButtonType::color_type::choosed);
				}
				return WAS_EVENT;
			}
		}
	}
	return WAS_NO_EVENT;
}

Settings& Settings::setStatus(bool status){
	m_status = status;
	return *this;
}

bool Settings::getStatus() const
{
	return m_status;
}

void Settings::bildSnakeFactoryFromSnakes() {
	m_snakesFactory.reserve(m_snakes.size());
	for (auto& snake : m_snakes) {
		auto playerPtr = dynamic_cast<Player*>(snake.get());
		auto type = playerPtr != nullptr ? PLAYER : BOT;
		m_snakesFactory.emplace_back(std::make_unique<SnakeFactory>(*this, m_snakesFactory.size(), type, snake->getColor(), snake->getName(),
			playerPtr != nullptr ? playerPtr->getLeft() : sf::Keyboard::Key::A, playerPtr != nullptr ? playerPtr->getRight() : sf::Keyboard::Key::A));
	}
}

void Settings::resetButtonDefault(size_t loaction) {
	setButtonMode(loaction, ButtonType::color_type::regular);
	m_hover = FIRST_BUTTON;
	m_choosed = EMPTY_PLACE;
}
