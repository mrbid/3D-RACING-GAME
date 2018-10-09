/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef SOUND_H
#define SOUND_H

#pragma comment(lib, "OpenAL32.lib")

#include "precom.h"
#include "Vector3.h"

#define pSOUND int

//Sound Structure
struct SoundData
{
	SoundData()
	{
		alDeleteSources(1, &source);
		alDeleteBuffers(1, &buffer);
	}

	ALuint buffer;
	ALuint source;
};

//Sound Class
class Sound
{
public:

	static Sound& Inst()
	{
		static Sound singleton;
		return singleton;
	}
	~Sound(); //Destructor

	//Load a 2 Channel 44100kz 16bit PCM
	pSOUND LoadPCM(char* file);

	//Create sound from buffer
	pSOUND CreateSound(char* buff, int size, int frequency);

	//Deletes a sound from the buffer
	void DeleteSound(pSOUND id);

	//Replaces the buffer in a sound
	void UpdateSound(pSOUND id, char* buff, int size, int frequency);

	//Set's a sounds position, direction and velocity
	void SetSoundPosition(pSOUND id, vec3::Vector3 position);
	void SetSoundDirection(pSOUND id, vec3::Vector3 direction);
	void SetSoundVelocity(pSOUND id, vec3::Vector3 velocity);

	//Set's the listeners (ear) position, should be at the camera pos
	void SetListenerPosition(vec3::Vector3 position);
	void SetListenerVelocity(vec3::Vector3 velocity);
	void SetListenerOrientation(vec3::Vector3 orientation);

	//Play, stop, pause, rewind sounds.
	void PlaySound(pSOUND id);
	void StopSound(pSOUND id);
	void RewindSound(pSOUND id);
	void PauseSound(pSOUND id);
	void SetLooping(pSOUND id, const bool state);
	bool IsPlaying(pSOUND id);
	int GetSeek(pSOUND id);
	void SetSeek(pSOUND id, int pos);
	float GetSeekSeconds(pSOUND id);
	void SetSeekSeconds(pSOUND id, float pos);

private:

	Sound(); //Constructor
	Sound(const Sound&); //Prevent Copy
	Sound& operator=(const Sound&); //Prevent Assignment

	std::vector<SoundData> m_sounds;
	std::vector<int> m_deleteflags;
	ALCdevice* pDevice;
	ALCcontext* pContext;

};

MP_INLINE void Sound::PlaySound(pSOUND id)
{
	alSourcePlay(m_sounds[id].source);
}

MP_INLINE void Sound::StopSound(pSOUND id)
{
	alSourceStop(m_sounds[id].source);
}

MP_INLINE void Sound::RewindSound(pSOUND id)
{
	alSourceRewind(m_sounds[id].source);
}

MP_INLINE void Sound::PauseSound(pSOUND id)
{
	alSourcePause(m_sounds[id].source);
}

MP_INLINE void Sound::SetLooping(pSOUND id, const bool state)
{
	alSourcei(m_sounds[id].source, AL_LOOPING, state);
}

MP_INLINE bool Sound::IsPlaying(pSOUND id)
{
	int state;
	alGetSourcei(m_sounds[id].source, AL_SOURCE_STATE, &state);

	if(state == AL_STOPPED)
		return false;
	else
		return true;
}

MP_INLINE int Sound::GetSeek(pSOUND id)
{
	int pos;
	alGetSourcei(m_sounds[id].source, AL_SAMPLE_OFFSET, &pos);
	return pos;
}

MP_INLINE void Sound::SetSeek(pSOUND id, int pos)
{
	alSourcei(m_sounds[id].source, AL_SAMPLE_OFFSET, pos);
}

MP_INLINE float Sound::GetSeekSeconds(pSOUND id)
{
	float pos;
	alGetSourcef(m_sounds[id].source, AL_SEC_OFFSET, &pos);
	return pos;
}

MP_INLINE void Sound::SetSeekSeconds(pSOUND id, float pos)
{
	alSourcef(m_sounds[id].source, AL_SEC_OFFSET, pos);
}

//Return Instance to Sound Singleton
MP_INLINE Sound& SoundSystem(){return Sound::Inst();}

#endif