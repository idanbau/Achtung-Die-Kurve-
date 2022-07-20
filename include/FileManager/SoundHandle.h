#pragma once
#include <SFML/Audio.hpp>
#include <array>
// Singelton

enum class sound_type : size_t
{
	hover, clickUnLegul, clickButton, sankeCrush, WinSound, TakeGift, TakeGiftAll, TakeClearGift ,SoundCount
};

class SoundHandle {
public:
	static SoundHandle& use();
	void playSound(sound_type sound);
	void pausePlay();
	bool getPauseStatus() const;
	void playBackGroundMusic();
	void playEndMusic();

private:
	SoundHandle();
	SoundHandle(const SoundHandle&) = default;
	SoundHandle& operator=(const SoundHandle&) = default;
	void loadSounds();
	bool m_mute = false;
	std::array <sf::Sound, (size_t)sound_type::SoundCount> m_musics;
	std::array <sf::SoundBuffer, (size_t)sound_type::SoundCount> m_soundBuffers;
	sf::Music m_backGroundMusic;
};
