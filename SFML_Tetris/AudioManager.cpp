#include "AudioManager.h"

AudioManager::AudioManager()
{
	dropSound.loadFromFile("Audio/Tetris_Drop.wav");
	holdSound.loadFromFile("Audio/Tetris_Hold.wav");
	moveSound.loadFromFile("Audio/Tetris_Move.wav");
	rotateSound.loadFromFile("Audio/Tetris_Move.wav");
	clearSound.loadFromFile("Audio/Tetris_RowClear.wav");
	fourClearSound.loadFromFile("Audio/Tetris_FourRowClear.wav");

	audioSources.resize(voiceCount);
}

void AudioManager::Play(AudioManager::audioClips clip)
{

	sf::SoundBuffer* s = GetSoundBuffer(clip);
	sf::Sound* audioSource = GetIdleAudioSource();

	if (s)
	{
		if (audioSource)
		{

			audioSource->setBuffer(*s);
			audioSource->play();
		}
		else
		{
			audioSources.front().setBuffer(*s);
			audioSources.front().play();
		}

	}
}

sf::SoundBuffer* AudioManager::GetSoundBuffer(audioClips clip)
{
	switch (clip)
	{
	case AudioManager::audioClips::drop:
		return &dropSound;
	case AudioManager::audioClips::move:
		return &moveSound;
	case AudioManager::audioClips::hold:
		return &holdSound;
	case AudioManager::audioClips::rotate:
		return &rotateSound;
	case AudioManager::audioClips::clear:
		return &clearSound;
	case AudioManager::audioClips::fourClear:
		return &fourClearSound;
	default:
		break;
	}

	return nullptr;
}

sf::Sound* AudioManager::GetIdleAudioSource()
{
	for (std::vector<sf::Sound>::iterator i = audioSources.begin(); i < audioSources.end(); ++i)
	{
		if (i->getStatus() == sf::SoundSource::Status::Stopped)
		{
			return &(*i);
		}
	}

	return nullptr;
}



