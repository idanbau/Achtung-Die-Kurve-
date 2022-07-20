#include "FileManager/SoundHandle.h"

SoundHandle::SoundHandle(){
	loadSounds();
}

void  SoundHandle::loadSounds() {
	auto fileNames = std::array<std::string, (size_t)sound_type::SoundCount> { "MouseHover.wav", "MouseClickUnLegul.wav" ,
	"MouseClickButton.wav", "SnakeCrush.wav", "WinSound.wav" , "TakeGift.wav", "TakeGiftAll.wav", "TakeClearGift.flac"};

	for (auto [soundBuffer, fileName, music] = std::make_tuple(m_soundBuffers.begin(), fileNames.cbegin(), m_musics.begin()); soundBuffer < m_soundBuffers.end();
		++soundBuffer, ++fileName, ++music)
	{
		soundBuffer->loadFromFile(*fileName);
		music->setBuffer(*soundBuffer);
	}
}

SoundHandle& SoundHandle::use() {
	static SoundHandle soundHandleObj;
	return soundHandleObj;
}

void SoundHandle::playSound(sound_type sound) {
	if(!m_mute)
		m_musics[size_t(sound)].play();
}

void SoundHandle::pausePlay(){
	m_mute = !m_mute;
	m_mute ? m_backGroundMusic.pause() : m_backGroundMusic.play();
}

bool SoundHandle::getPauseStatus() const {
	return m_mute;
}

void SoundHandle::playBackGroundMusic() {
	m_backGroundMusic.openFromFile("Background.wav");
	m_backGroundMusic.setLoop(true);
	if (!m_mute)
		m_backGroundMusic.play();
}

void SoundHandle::playEndMusic() {
	m_backGroundMusic.openFromFile("WinSound.wav");
	m_backGroundMusic.setLoop(true);
	if (!m_mute)
		m_backGroundMusic.play();
}