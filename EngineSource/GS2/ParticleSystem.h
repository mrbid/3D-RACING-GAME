/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "precom.h"

#include "D3DRenderer.h"
#include "Vector3.h"
#include "Physics.h"
#include "MilliTimer.h"
#include "Collision.h"
#include "Camera.h"
#include "iRandom.h"


//Particle Info Struct
struct ParticleInfo
{
	//Initial Kinematic Variables
	vec3::Vector3 initial_velocity;
	double initial_time;

	//Variables to pre-calculate for efficiency
	double expiretime;
	double recipexpiretime;

	//Inital Position of Particle
	vec3::Vector3 initial_position;

	//Is Alive?
	bool isalive;
};

//Particle Emitter Info
struct EmitterInfo
{
	std::string texture;
	int totalparticles;
	float coneangle;
	float min_initialspeed;
	float max_initialspeed;
	double livetime;
	float emissionrate;
	float startscale;
	float endscale;
	bool scaleflip;
	float startalpha;
	float endalpha;
	bool alphaflip;
	vec3::Vector3 direction;
	vec3::Vector3 position;
	vec3::Vector3 acceleration;
};

//Particle Emitter Struct
struct ParticleEmitter
{
	//Destructor
	~ParticleEmitter();

	//Resets a particle
	void ResetParticle(int i);

	//Update Emitter
	void Update(float dt);

	//Get Emitter Ready for Rendering
	void Render();

	//Total Particle Count
	int totalparticles;

	//Holds Conceptual Information
	ParticleInfo* particles;

	//Holds Real Information to be passed to Renderer
	PointSprite* sprites;

	//Acceleration of Particles that leave Emitter
	vec3::Vector3 acceleration;

	//Particle Live Time
	double livetime;

	//Particle Scale
	float startscale, endscale, scaleflip;

	//Particle Alpha
	float startalpha, endalpha, alphaflip;

	//Particle Texture
	LPDIRECT3DTEXTURE9 texture;

	//Emission Rate
	float emissionrate;

	//Max and Min Initial Speed
	float min_initialspeed, max_initialspeed;

	//Emitter Direction
	vec3::Vector3 direction;

	//Emitter position
	vec3::Vector3 position;

	//Emitter Cone Angle
	float coneangle;

	//Sphere boundary of emitter
	coll::Sphere spherebound;

	//Emission Regulator
	double emissionregulator;

};

//Particle System Class
class ParticleSystem
{
public:

	//Singleton Instance
	static ParticleSystem& Inst()
	{
		static ParticleSystem singleton;
		return singleton;
	}

	//Destructor
	~ParticleSystem();

	//Init Particle System
	void Init(int particlepoolsize);

	//Update Particle System
	void Update(float dt);
	
	//Render Particle System
	void Render();

	//Update Emitter Position
	void UpdateEmitterPosition(const int id, vec3::Vector3 position);

	//Add new emitter
	int AddEmitter(EmitterInfo* info);

	//Remove Emitter
	void RemoveEmitter(const int id);

private:

	ParticleSystem(){} //Constructor
	ParticleSystem(const ParticleSystem&); //Prevent Copy
	ParticleSystem& operator=(const ParticleSystem&); //Prevent Assignment
	
	//Array of Emitters
	std::vector<ParticleEmitter*> m_emitters;
	std::vector<int> m_deleteflags;

	//Particle Pool
	PointSprite* m_pool;
	int m_poolsize;

	//Total Assigned Particles
	int m_assignedparticles;

};

MP_INLINE void ParticleSystem::Update(float dt)
{
	for(std::vector<ParticleEmitter*>::iterator iter = m_emitters.begin(); iter != m_emitters.end(); ++iter)
	{
		(*iter)->Update(dt);
	}
}

MP_INLINE void ParticleSystem::UpdateEmitterPosition(const int id, vec3::Vector3 position)
{
	m_emitters[id]->position = position;
}

MP_INLINE void ParticleSystem::RemoveEmitter(const int id)
{
	m_deleteflags.push_back(id);
}

//Return Instance to ParticleSystem Singleton
MP_INLINE ParticleSystem& ParticleSystem(){return ParticleSystem::Inst();}

#endif







