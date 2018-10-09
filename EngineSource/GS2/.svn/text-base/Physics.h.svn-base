/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/

	Need To Add Numerical Solving:
	Verlet
	Runge Kutta (RK4)
	
	PhyUtil
	 - Miles To Meters Per Second
	 - Kilometers to Meters Per Second
	 - Meters Per Second to Miles Per Hour
	 - Meters Per Second to Kilometers Per Hour
	 - Grams to Kilograms
	 
	Classes
	 - Projectile Motion
	 - Particle Motion
	 - KineticMotion
	 - EulerKineticMotion
*/

#ifndef PHYSICS_H
#define PHYSICS_H

#include "precom.h"
#include "MathLib.h"
#include "Vector3.h"


//Physics Utilities
namespace PhyUtil
{
	//Convert Miles per second to Meters Per Second
	MP_INLINE float MilesPerSecond(float milespersecond)
	{
		return milespersecond * 0.00780231989f;
	}
	
	//Convert Kilometers per second to Meters per second
	MP_INLINE float KilometersPerSecond(float kilometerspersecond)
	{
		return kilometerspersecond * 1000.0f;
	}

	//Convert Kilometers per hour to Meters per second
	MP_INLINE float KilometersAnHour(float kilometersperhour)
	{
		return kilometersperhour * 0.277777778f;
	}

	//Convert Miles per hour to Meters per second
	MP_INLINE float MilesAnHour(float milesperhour)
	{
		return milesperhour * 0.44704f;
	}
	
	//Convert Meters Per Second to Miles Per Hour
	MP_INLINE float ToMilesPerHour(float meterspersecond)
	{
		return meterspersecond * 2.2369362920544f;
	}
	
	//Convert Meters Per Second to Kilometers Per Hour
	MP_INLINE float ToKilometersPerHour(float meterspersecond)
	{
		return meterspersecond * 3.6f;
	}
	
	//Convert Grams to Kilograms
	MP_INLINE float Grams(float grams)
	{
		return grams * 0.001f;
	}
	
	//Inverts mass to a scalar
	MP_INLINE float InvMass(float kg)
	{
		return math::rcp(kg);
	}
	
	//Velocity from Speed 3D
	MP_INLINE vec3::Vector3 VelocityFromSpeed3D(float rotx, float roty, float speed)
	{
		return vec3::Vector3(speed * cos(rotx), speed * sin(roty), 0.f);
	}
	
	//Velocity from Speed 2D
	MP_INLINE vec3::Vector3 VelocityFromSpeed2D(float roty, float speed)
	{
		return vec3::Vector3(speed * cos(roty), speed * sin(roty), 0.f);
	}

	//Taylor Numerical Solving
	MP_INLINE vec3::Vector3 TaylorSolv(vec3::Vector3 v, vec3::Vector3 a, float t)
	{
		return v * t + 0.5f * (t*t) * a;
	}

	//Runge Kutta (RK4) Numerical Solving
	MP_INLINE void RK4Solv(vec3::Vector3& ip, vec3::Vector3& iv, vec3::Vector3& ia, float t, float dt)
	{
		const vec3::Vector3 ap = iv;
		const vec3::Vector3 av = iv + ia * t;
		const vec3::Vector3 bp = iv + av * (dt*0.5f);
		const vec3::Vector3 bv = bp + ia * (t+dt);
		const vec3::Vector3 cp = iv + bv * (dt*0.5f);
		const vec3::Vector3 cv = cp + ia * (t+dt);
		const vec3::Vector3 dp = iv + cv * (dt*0.5f);
		const vec3::Vector3 dv = dp + ia * (t+dt);
		ip += (0.16666666666666666666666666666667f * (ap + 2.0f * (bp + cp) + dp)) * dt;
		iv += (0.16666666666666666666666666666667f * (av + 2.0f * (bv + cv) + dv)) * dt;
	}

	//Verlet Numerical Solving
	//
};


//Kinematic Projectile Motion Class
class ProjectileMotion
{
public:
	
	//Init From Custom Velocity
	MP_INLINE void Init(vec3::Vector3 pos, vec3::Vector3 accel, vec3::Vector3 vel, float time)
	{
		initial_time = time, initial_position = pos, acceleration = accel, initial_velocity = vel;
	}
	
	//Update
	MP_INLINE void Update(float time)
	{
		const float timediff = time - initial_time;
		current_velocity = initial_velocity + acceleration * timediff;
		current_position = initial_position + initial_velocity * timediff + 0.5f * (timediff*timediff) * acceleration;
	}
	
	//Get's current position
	MP_INLINE vec3::Vector3& GetPosition(){return current_position;}
	
	//Get's current direction
	MP_INLINE vec3::Vector3 GetDirection(){return vec3::I_Normalize(current_velocity);}
	
private:
	vec3::Vector3 current_position, current_velocity;
	vec3::Vector3 acceleration, initial_position, initial_velocity;
	float initial_time;
};


//Kinematic Particle Motion Class
class ParticleMotion
{
public:
	
	//Init From Custom Velocity
	MP_INLINE void Init(vec3::Vector3 pos, vec3::Vector3 accel, vec3::Vector3 vel, float time)
	{
		initial_time = time, initial_position = pos, acceleration = accel, initial_velocity = vel;
	}
	
	//Update
	MP_INLINE void Update(float time)
	{
		const float timediff = time - initial_time;
		current_position = initial_position + initial_velocity * timediff + 0.5f * (timediff*timediff) * acceleration;
	}
	
	//Get's current position
	MP_INLINE vec3::Vector3& GetPosition(){return current_position;}
	
private:
	vec3::Vector3 current_position;
	vec3::Vector3 acceleration, initial_position, initial_velocity;
	float initial_time;
};


//Euler Projectile Motion Class
class EulerProjectileMotion
{
public:
	
	//Init From Custom Velocity
	MP_INLINE void Init(vec3::Vector3 pos, vec3::Vector3 accel, vec3::Vector3 vel, float time)
	{
		last_time = time, position = pos, acceleration = accel, velocity = vel;
	}
	
	//Update
	MP_INLINE void Update(float time)
	{
		const float timediff = time - last_time;
		position += velocity * timediff;
		velocity += acceleration * timediff;
		last_time = time;
	}
	
	//Get's current position
	MP_INLINE vec3::Vector3& GetPosition(){return position;}
	
	//Get's current direction
	MP_INLINE vec3::Vector3 GetDirection(){return vec3::FastNormalize(velocity);}
	
private:
	vec3::Vector3 position, velocity, acceleration;
	float last_time;
};


//Kinetic Motion Class (Taylor Series)
class KineticMotion
{
public:

	//Init From Custom Velocity
	MP_INLINE void Init(vec3::Vector3 pos, vec3::Vector3 vel, float masskg, float maxspeedmps, float time)
	{
		last_time = time, position = pos, mass = masskg, velocity = vel, maxspeed = maxspeedmps;
	}
	
	//Update
	inline void Update(float time)
	{
		const float timediff = time - last_time;
		const vec3::Vector3 acceleration = forces * mass;
		//position += velocity * timediff + 0.5f * (timediff*timediff) * acceleration;
		position += PhyUtil::TaylorSolv(velocity, acceleration, timediff);
		velocity += acceleration * timediff;
		
		//Clamp max velocity
		if(vec3::I_Modulus(velocity) > maxspeed)
			velocity = vec3::I_Normalize(velocity) * maxspeed;
		
		last_time = time;
	}
	
	MP_INLINE void AddForce(const vec3::Vector3& force){forces += force;} //Add a force
	MP_INLINE void ClearForces(){forces = vec3::VECTOR_NULL;} //Clears all forces
	MP_INLINE vec3::Vector3 GetForce() const{return forces;} //Returns accelleration
	MP_INLINE vec3::Vector3& GetPosition(){return position;} //Get's current position
	MP_INLINE vec3::Vector3 GetDirection(){return vec3::I_Normalize(velocity);} //Get's current direction
	MP_INLINE float& GetMaxSpeed(){return maxspeed;} //Get's Max Speed
	MP_INLINE float GetCurrentSpeed(){return vec3::I_Modulus(velocity);}
	MP_INLINE float GetMass() const{return mass;} //Get's Mass
	MP_INLINE void SetMass(float masskg){mass = PhyUtil::InvMass(masskg);} //Set's Mass
	
private:
	vec3::Vector3 position, velocity, forces;
	float mass, maxspeed;
	float last_time;
};


//Euler Kinetic Motion Class
class EulerKineticMotion
{
public:
	
	//Init From Custom Velocity
	MP_INLINE void Init(vec3::Vector3 pos, vec3::Vector3 vel, float masskg, float maxspeedmps, float time)
	{
		last_time = time, position = pos, mass = masskg, velocity = vel, maxspeed = maxspeedmps;
	}
	
	//Update
	inline void Update(float time)
	{
		const float timediff = time - last_time;
		position += velocity * timediff;
		velocity += (forces * mass) * timediff;
		
		//Clamp max velocity
		if(vec3::Modulus(velocity) > maxspeed)
			velocity = vec3::FastNormalize(velocity) * maxspeed;
		
		last_time = time;
	}
	
	MP_INLINE void AddForce(const vec3::Vector3& force){forces += force;} //Add a force
	MP_INLINE void ClearForces(){forces = vec3::VECTOR_NULL;} //Clears all forces
	MP_INLINE vec3::Vector3 GetForce() const{return forces;} //Returns accelleration
	MP_INLINE vec3::Vector3& GetPosition(){return position;} //Get's current position
	MP_INLINE vec3::Vector3 GetDirection(){return vec3::FastNormalize(velocity);} //Get's current direction
	MP_INLINE float& GetMaxSpeed(){return maxspeed;} //Get's Max Speed
	MP_INLINE float GetCurrentSpeed(){return vec3::I_Modulus(velocity);}
	MP_INLINE float GetMass() const{return mass;} //Get's Mass
	MP_INLINE void SetMass(float masskg){mass = PhyUtil::InvMass(masskg);} //Set's Mass
	
private:
	vec3::Vector3 position, velocity, forces;
	float mass, maxspeed;
	float last_time;
};

#endif

