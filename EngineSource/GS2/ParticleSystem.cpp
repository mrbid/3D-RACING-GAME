/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#include "precom.h"
#include "ParticleSystem.h"
#include "Camera.h"

//Destructor
ParticleSystem::~ParticleSystem()
{
	//Delete Emitters
	for(std::vector<ParticleEmitter*>::iterator iter = m_emitters.begin(); iter != m_emitters.end(); ++iter)
		delete (*iter);

	//Clear Array
	m_emitters.clear();

	//Delete Particle Pool
	delete [] m_pool;
}

//Init Particle System
void ParticleSystem::Init(int particlepoolsize)
{
	//Init Renderer
	RenderSystem().InitParticleRenderer(particlepoolsize);

	//Init Pool
	m_pool = new PointSprite[particlepoolsize];

	//Set size of pool
	m_poolsize = particlepoolsize;
	m_assignedparticles = 0;
}
	
//Render Particle System
void ParticleSystem::Render()
{
	//Go through each particle emitter
	for(std::vector<ParticleEmitter*>::iterator iter = m_emitters.begin(); iter != m_emitters.end(); ++iter)
	{
		//Is this emitter within the camera frustum?
		if(coll::SphereBoundCollision((*iter)->position, &(*iter)->spherebound, CameraSystem().GetFrustumSpherePosition(), &CameraSystem().FrustumSphereBound()) == true)
		{
			//Ready the emitter for being passed to the renderer
			(*iter)->Render();

			//Copy all living points into the pool
			int p = 0;
			for(int i = 0; i < (*iter)->totalparticles; ++i)
			{
				if((*iter)->particles[i].isalive == true)
				{
					memcpy(&m_pool[p], &(*iter)->sprites[i], sizeof(PointSprite));
					p++;
				}
			}

			//Pass pool to the renderer
			RenderSystem().RenderParticles(m_pool, p, (*iter)->texture);
		}
	}
}

//Add new emitter
int ParticleSystem::AddEmitter(EmitterInfo* info)
{
	//Check if there's going to be enough particles left
	if(info->totalparticles + m_assignedparticles >= m_poolsize-1)
		return -1;

	//Create emitter
	ParticleEmitter* emitter = new ParticleEmitter;

	//Setup Emitter
	emitter->acceleration = info->acceleration;
	emitter->coneangle = info->coneangle;
	emitter->direction = info->direction;
	emitter->emissionrate = info->emissionrate;
	emitter->endscale = info->endscale;
	emitter->startscale = info->startscale;
	emitter->endalpha = info->endalpha;
	emitter->startalpha = info->startalpha;
	emitter->position = info->position;
	emitter->livetime = info->livetime;
	emitter->max_initialspeed = info->max_initialspeed;
	emitter->min_initialspeed = info->min_initialspeed;
	emitter->scaleflip = info->scaleflip;
	emitter->alphaflip = info->alphaflip;
	emitter->totalparticles = info->totalparticles;
	D3DXCreateTextureFromFileA(RenderSystem().GetDevice(), info->texture.c_str(), &emitter->texture);
	emitter->particles = new ParticleInfo[emitter->totalparticles];
	emitter->sprites = new PointSprite[emitter->totalparticles];

	//Set a hardcoded sphere bound
	emitter->spherebound.center = vec3::VECTOR_NULL;
	emitter->spherebound.radius = 0.5f;

	//Reset Particles
	for(int i = 0; i < emitter->totalparticles; ++i)
		emitter->ResetParticle(i);

	//Add emitter
	int cid = 0;

	if(m_deleteflags.size() != 0)
	{
		//If there was a slot flagged as deleted, use that.
		cid = *m_deleteflags.begin();
		m_deleteflags.erase(m_deleteflags.begin());
		std::vector<ParticleEmitter*>::iterator iter = m_emitters.begin() + cid;
		delete (*iter);
		m_emitters.erase(iter);
		m_emitters.insert(iter, emitter);
	}
	else
	{
		//If not, add a new slot
		cid = m_emitters.size();
		m_emitters.push_back(emitter);
	}

	return cid;
}

//Destructor
ParticleEmitter::~ParticleEmitter()
{
	if(particles != NULL)
		delete [] particles;

	if(sprites != NULL)
		delete [] sprites;
}

//Resets a particle
void ParticleEmitter::ResetParticle(int i)
{
	//Reset Kinematic Simulation & emission regulator
	particles[i].initial_time = GetTime();
	emissionregulator = GetTime();

	//Set new origin
	particles[i].initial_position = position;

	//Create a new initial velocity
	vec3::Vector3 newdir = vec3::RotateX(direction, i_qRandFloat(0, coneangle));
	newdir = vec3::RotateY(newdir, i_qRandFloat(0, coneangle));
	particles[i].initial_velocity = newdir * i_qRandFloat(min_initialspeed, max_initialspeed);

	//Reset pre-calculations
	particles[i].expiretime = particles[i].initial_time + livetime;
	particles[i].recipexpiretime = 1.f / (particles[i].expiretime - particles[i].initial_time);

	//Set to alive
	particles[i].isalive = true;
}

//Update Emitter
void ParticleEmitter::Update(float dt)
{
	//Update each particle in emitter
	for(int i = 0; i < totalparticles; ++i)
	{
		//Is particle alive?
		if(particles[i].isalive == false)
		{
			//Check if it's time to emit a particle
			if(GetTime() > emissionregulator)
			{
				ResetParticle(i);
				emissionregulator = GetTime() + emissionrate;
			}

			//Continue
			continue;
		}

		//Check if particle has expired
		if(GetTime() > particles[i].expiretime)
			particles[i].isalive = false;
	}
}


//Get Emitter Ready for Rendering
void ParticleEmitter::Render()
{
	//Update each particle in emitter
	for(int i = 0; i < totalparticles; ++i)
	{
		//Is particle alive?
		if(particles[i].isalive == false)
			continue;

		//Update Position
		const double time = GetTime();
		const double timediff = time - particles[i].initial_time;
		sprites[i].SetPosition(particles[i].initial_position + particles[i].initial_velocity * timediff + 0.5f * (timediff*timediff) * acceleration);
		
		//Update Scale
		if(scaleflip == false)
			sprites[i].m_scale = endscale + (startscale * math::clamp((1.0-((time-particles[i].initial_time) * particles[i].recipexpiretime))));
		else
			sprites[i].m_scale = endscale + (startscale * math::clamp(((time-particles[i].initial_time) * particles[i].recipexpiretime)));

		//Update Alpha
		if(alphaflip == false)
			sprites[i].SetColour(clr::mColour4(1.f, 1.f, 1.f, endalpha + (startalpha * math::clamp((1.0-((time-particles[i].initial_time) * particles[i].recipexpiretime))))));
		else
			sprites[i].SetColour(clr::mColour4(1.f, 1.f, 1.f, endalpha + (startalpha * math::clamp(((time-particles[i].initial_time) * particles[i].recipexpiretime)))));
	}
}




