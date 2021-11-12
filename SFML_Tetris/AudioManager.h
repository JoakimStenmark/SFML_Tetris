#pragma once
#include <string>
#include <vector>
#include <SFML/Audio.hpp>

class AudioManager
{
public:
	AudioManager();

	enum class audioClips
	{
		drop,
		move,
		hold,
		rotate,
		clear,
		fourClear
	};
	void Play(audioClips clip);

private:
	sf::SoundBuffer* GetSoundBuffer(audioClips clip);
	sf::SoundBuffer dropSound;
	sf::SoundBuffer moveSound;
	sf::SoundBuffer holdSound;
	sf::SoundBuffer rotateSound;
	sf::SoundBuffer clearSound;
	sf::SoundBuffer fourClearSound;

	const size_t voiceCount = 16;
	std::vector<sf::Sound> audioSources;
	sf::Sound* GetIdleAudioSource();
	
};

