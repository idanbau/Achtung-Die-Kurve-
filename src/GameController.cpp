#include "GameController.h"
#include "Screens.hpp"

const auto APP_NAME = "Achtung, die Kurve! By Idan Baumer and David Aria Zeev";
const auto SECONDS_DRAW = sf::seconds(3.5f);					//seconds to draw line
const auto SECONDS_UN_DRAW = sf::seconds(0.4f);					//seconds not to draw
const auto SECONDS_DRAW_ROUND = SECONDS_DRAW + SECONDS_UN_DRAW;	//round for draw/undraw
const auto MIN_SNAKES_LEFT = 2;									//play the game until x snakes left
const auto GOAL = 50;											//goal for the game
const auto FRAMES_LIMIT = 60U;									//maximum game frames
const auto SCREEN_SETTING_INDEX = 2;							//index of screen type
const auto SIZE_SETTING_BUTTON = 120.f;							//size of button setting
const auto NOT_DRAW_BUTTON = false;



GameController::GameController() :
	m_settingButton(Button<std::function<void()>>{ [this]() {changeSettings(); },
		sf::Vector2f{ float(WINDOW_SIZE.x) - float(TOOLBAR_SIZE.x) / 2.f, float(TOOLBAR_SIZE.y) - SIZE_SETTING_BUTTON },	// location
		"Settings", font_type::font2, { SIZE_SETTING_BUTTON, SIZE_SETTING_BUTTON }, sf::Color::Red }),
	m_screens([&]
		{
			std::vector<std::unique_ptr<Screen>> ret;
			ret.reserve(size_t(screen_type::screensCount));
			ret.emplace_back(std::make_unique<Launcher>(Launcher(m_window)));
			ret.emplace_back(std::make_unique<GoesStages>(GoesStages(m_window)));
			ret.emplace_back(std::make_unique<Settings>(Settings(m_window, m_snakes, m_board)));
			ret.emplace_back(std::make_unique<EndScreen>(EndScreen(m_window, m_snakes)));
			return ret;
		}()
	),
	m_window({ WINDOW_SIZE.x, WINDOW_SIZE.y }, APP_NAME)
{
	m_window.setFramerateLimit(FRAMES_LIMIT);
};

// run the game
screen_type GameController::run() {
	SoundHandle::use().playBackGroundMusic();
	while (m_window.isOpen()) {
		goScreen(screen_type::launcher);	// read first screens and than will play()
		play();
		m_screens[size_t(screen_type::endScreen)]->run();
	}
	return screen_type::exit;
}

// function that go screens/state the screen back if need come to another screen or back or exit app
void GameController::goScreen(screen_type screen) {
	while ((int)screen >= 0){
		screen = m_screens[(int)screen]->run();
	}

	if (screen == screen_type::exit)
		m_window.close();
}

void GameController::play() {
	auto timeRun = sf::seconds(0.f);//time for creating objects
	auto isSplitted = false;		//store if need to be split
	auto m_hover = false;
	auto location = sf::Vector2f{};

	m_board.setBoard(m_snakes.size());
	resetPlayers();	//resets players to default
	m_toolbar.resetSetting(GOAL);
	auto collisionHandling = CollisionHandling(m_board, m_snakes);
	
	draw(NOT_DRAW_BUTTON);
	TextureHandle::use().setPrintScreen(m_window);
	goScreen(screen_type::goesStages);
	sf::Clock clock;
	while (m_window.isOpen())
	{
		const auto deltaTime = clock.restart();
		timeRun += deltaTime;
		m_board.clockUpdate(deltaTime);
		draw();
		if (checkNextRound()) {
			for (const auto& snake : m_snakes) {	// check if end game
				if (snake->getScore() >= GOAL)
					return;
			}
			goNextRound();
			clock.restart();
			timeRun = sf::seconds(0.f);
			continue;
		}

		if (auto event = sf::Event(); m_window.pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;

			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Escape) {
					changeSettings();
					clock.restart();
				}
				break;

			case sf::Event::MouseMoved:
				location = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
				if (m_settingButton.isContain(location)) {
					if (!m_hover) {
						m_settingButton.setMode(ButtonType::color_type::hover);
						m_hover = true;
					}
				}
				else {
					if (m_hover) {
						m_settingButton.setMode(ButtonType::color_type::regular);
						m_hover = false;
					}
				}
				break;

			case sf::Event::MouseButtonReleased:
				location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				if (m_settingButton.isContain(location)) {
					m_settingButton.getT()();
					m_settingButton.setMode(ButtonType::color_type::regular);
					clock.restart();
				}
				break;

			}

		}
		for (size_t i = 0; i < m_snakes.size(); ++i) {
			if (m_snakes[i]->alive()) {
				m_snakes[i]->move(deltaTime);
				if (m_board.checkCollise(i, *m_snakes[i], collisionHandling)) {
					m_snakes[i]->kill();
					--m_snakesAlive;
					SoundHandle::use().playSound(sound_type::sankeCrush);
					addAliveScore();
					m_toolbar.update();
				}
				if (auto pairPoints = m_snakes[i]->addVertices(timeRun < SECONDS_DRAW)) {
					m_board.insert(i, *pairPoints);
				}
				else if (!isSplitted && timeRun >= SECONDS_DRAW) {
					isSplitted = true;
				}
				if (isSplitted && timeRun > SECONDS_DRAW_ROUND) {
					isSplitted = false;
					timeRun = sf::seconds(0.f);
					m_board.splitLines();
				}
			}
		}
	}
}

void GameController::draw(bool drawButton) {
	m_window.clear();
	m_toolbar.draw();
	for (const auto& snake : m_snakes) {
		snake->draw(m_window);
	}
	m_board.draw(m_window);
	if (drawButton)
		m_window.draw(m_settingButton);
	m_window.display();
}

// update to next round by reset data and show Press Space To Continue
void GameController::goNextRound() {
	draw(NOT_DRAW_BUTTON);
	TextureHandle::use().setPrintScreen(m_window);
	resetLevel();
	goScreen(screen_type::goesStages);
}
void GameController::changeSettings(){
	auto settingPtr = static_cast<Settings*>(m_screens[SCREEN_SETTING_INDEX].get());
	settingPtr->setStatus(EDIT);
	goScreen(screen_type::settings);
	if (settingPtr->getStatus() == NEW_GAME)
	{
		resetLevel();
		m_toolbar.resetSetting(GOAL);
		return;
	}
	m_toolbar.update();
	draw(NOT_DRAW_BUTTON);
	TextureHandle::use().setPrintScreen(m_window);
	goScreen(screen_type::goesStages);
}

// reset the board and alive the saneks
void GameController::resetLevel() {
	resetPlayers();
	m_board.clear();
}

// reset the sankes and count of snakes alive
void GameController::resetPlayers(){
	for (auto& player : m_snakes) {
		player->resetSetting();
	}
	m_snakesAlive = m_snakes.size();
}

// check if all snake are die and need continue next round
bool GameController::checkNextRound() const {
	return m_snakesAlive < MIN_SNAKES_LEFT;
}

// when snake are dies all snake alive are add scores
void GameController::addAliveScore() {
	for (auto& player : m_snakes) {
		if (player->alive())
			player->addScore();
	}
}