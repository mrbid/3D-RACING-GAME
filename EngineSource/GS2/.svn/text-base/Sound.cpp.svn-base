/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#include "precom.h"
#include "Sound.h"
using namespace vec3;

//Constructor
Sound::Sound()
{
	pDevice = alcOpenDevice(NULL);
	pContext = alcCreateContext(pDevice, NULL);
	alcMakeContextCurrent(pContext);
}

//Destructor
Sound::~Sound()
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(pContext);
	alcCloseDevice(pDevice);
}

//Create sound from buffer
pSOUND Sound::CreateSound(char* buff, int size, int frequency)
{
	int cid = 0;

	//Add new sound to m_sounds array
	if(m_deleteflags.size() != 0)
	{
		//If there was a slot flagged as deleted, use that.
		cid = *m_deleteflags.begin();
        m_deleteflags.erase(m_deleteflags.begin());
	}
	else
	{
		//If not, add a new slot
		cid = m_sounds.size();
		SoundData dat;
		m_sounds.push_back(dat);
	}

	//Generate source and buffer
	alGenSources(1, &m_sounds[cid].source);
	alGenBuffers(1, &m_sounds[cid].buffer);

	//Write the sound data to the buffer
	alBufferData(m_sounds[cid].buffer, AL_FORMAT_MONO16, buff, size, frequency);

	//Attach Source to Buffer
	alSourcei(m_sounds[cid].source, AL_BUFFER, m_sounds[cid].buffer);
	
	//Return Sound ID
	return cid;
}

//Create sound from buffer
pSOUND Sound::LoadPCM(char* file)
{
	int cid = 0;

	//Add new sound to m_sounds array
	if(m_deleteflags.size() != 0)
	{
		//If there was a slot flagged as deleted, use that.
		cid = *m_deleteflags.begin();
        m_deleteflags.erase(m_deleteflags.begin());
	}
	else
	{
		//If not, add a new slot
		cid = m_sounds.size();
		SoundData dat;
		m_sounds.push_back(dat);
	}

	//PCM info
	long pcmsize;
	char* pcmdata;

	//Load PCM
	FILE* f = fopen(file, "r");
	if(f != NULL)
	{
		fseek(f, 0, SEEK_END);
		pcmsize = ftell(f);
		pcmdata = new char[pcmsize];

		fseek(f, 0, SEEK_SET);
		fread(pcmdata, pcmsize, 1, f);
		fclose(f);
	}

	//Generate source and buffer
	alGenSources(1, &m_sounds[cid].source);
	alGenBuffers(1, &m_sounds[cid].buffer);

	//Write the sound data to the buffer
	alBufferData(m_sounds[cid].buffer, AL_FORMAT_STEREO16, pcmdata, pcmsize, 44100);

	//Attach Source to Buffer
	alSourcei(m_sounds[cid].source, AL_BUFFER, m_sounds[cid].buffer);

	//Return Sound ID
	return cid;
}

//Update sound buffer
void Sound::UpdateSound(pSOUND id, char* buff, int size, int frequency)
{
	//Delete old buffer
	alDeleteBuffers(1, &m_sounds[id].buffer);

	//Write the new buffer
	alBufferData(m_sounds[id].buffer, AL_FORMAT_MONO16, buff, size, frequency);
}

//Deletes a sound
void Sound::DeleteSound(pSOUND id)
{
	m_deleteflags.push_back(id);
	alDeleteSources(1, &m_sounds[id].source);
	alDeleteBuffers(1, &m_sounds[id].buffer);
}

//Set source position
void Sound::SetSoundPosition(pSOUND id, Vector3 position)
{
	ALfloat af[3];
	af[0] = position.x;
	af[1] = position.y;
	af[2] = position.z;

	alSourcefv(m_sounds[id].source, AL_POSITION, af);
}

//Set source direction
void Sound::SetSoundDirection(pSOUND id, Vector3 direction)
{
	ALfloat af[3];
	af[0] = direction.x;
	af[1] = direction.y;
	af[2] = direction.z;

	alSourcefv(m_sounds[id].source, AL_DIRECTION, af);
}

//Set source velocity
void Sound::SetSoundVelocity(pSOUND id, Vector3 velocity)
{
	ALfloat af[3];
	af[0] = velocity.x;
	af[1] = velocity.y;
	af[2] = velocity.z;

	alSourcefv(m_sounds[id].source, AL_VELOCITY, af);
}

//Set Listener Position
void Sound::SetListenerPosition(Vector3 position)
{
	ALfloat af[3];
	af[0] = position.x;
	af[1] = position.y;
	af[2] = position.z;

	alListenerfv(AL_POSITION, af);
}

//Set Listener Velocity
void Sound::SetListenerVelocity(Vector3 velocity)
{
	ALfloat af[3];
	af[0] = velocity.x;
	af[1] = velocity.y;
	af[2] = velocity.z;

	alListenerfv(AL_VELOCITY, af);
}

//Set Listener Orientation
void Sound::SetListenerOrientation(Vector3 orientation)
{
	ALfloat af[3];
	af[0] = orientation.x;
	af[1] = orientation.y;
	af[2] = orientation.z;

	alListenerfv(AL_ORIENTATION, af);
}










