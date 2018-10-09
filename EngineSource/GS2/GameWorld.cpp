/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#include "precom.h"

#include "GameWorld.h"
#include "MatrixLib.h"
#include "MathLib.h"
#include "ContentManager.h"
#include "Colours.h"
#include "Collision.h"
#include "Sound.h"
#include "hr_time.h"
#include "iRandom.h"
#include "BulletPhysics.h"
#include "ParticleSystem.h"
#include "Random.h"
#include "PerformanceAnalysis.h"

using namespace mat4;
using namespace clr;
using namespace vec3;
using namespace math;

HWND hWnd;
unsigned int fps_reg=0;
unsigned int fps=0;

//Destructor
GameWorld::~GameWorld()
{
	//Delete Controllers
	for(std::vector<BaseController*>::iterator iter = m_controllers.begin(); iter != m_controllers.end(); ++iter)
		delete (*iter);
}

//Set Projection Matrix
void GameWorld::SetProjection()
{
	//Projection
	const float nearplane = 1.0f;
	const float farplane = 60000.0f;
	const float fieldOfView = math::Degree(45.f);
	RenderSystem().SetupProjection(fieldOfView, 1.5f, nearplane, farplane);
	CameraSystem().CreateFrustum(fieldOfView, nearplane, farplane);

	//Enable Lighting
	RenderSystem().SetAmbientLight(100, 100, 100, 0);
	RenderSystem().EnableLight(0, true);

	//Set Render States
	RenderSystem().SetRenderStates();
}

//Init Game World
void GameWorld::Init(HWND hwnd)
{
	//Some Basics
	hWnd = hwnd;
	
	//Init Renderer
	RenderSystem().InitD3D(hwnd);
	RenderSystem().SetRenderStates();

	//Init ContentManager
	ContentManager().Init(RenderSystem().GetDevice());

	//Init Bullet Physics
	BulletPhysics().Init(Vector3(-1000, -1000, -1000), Vector3(1000, 1000, 1000), -23.7f);
}

void GameWorld::Load()
{
	//Init Particle System
	ParticleSystem().Init(10000);

	//Setup Projection
	SetProjection();

	//If Debug Mode Enable Performance Analysis
#ifdef _DEBUG
	PerformanceAnalysis().Init();
#endif

	//Add Controllors
	m_vehiclecontroller = new VehicleController;
	m_trackcontroller   = new TrackController;
	m_cameracontroller  = new CameraController;
	m_racecontroller  = new RaceController;
	m_AIcontroller  = new AIController;
	m_AIcontroller->settrackcontroller(m_vehiclecontroller); //you should do this GameWorld().GetVehicleController()
	//m_MusicController   = new flex::components::cMusicController;
	m_controllers.push_back( m_vehiclecontroller );
	m_controllers.push_back( m_trackcontroller   );
	m_controllers.push_back( m_cameracontroller  );
	m_controllers.push_back( m_racecontroller    );
	m_controllers.push_back( m_AIcontroller      );
	//m_controllers.push_back( m_MusicController  );

	////Create Test Emitter
	//EmitterInfo ei;
	//ei.acceleration = vec3::Vector3(0.f, -0.00001f, 0.f);
	//ei.direction = vec3::Vector3(0.f, 1.f, 0.f);
	//ei.position = vec3::Vector3(0.f, 0.f, 0.f);
	//ei.coneangle = math::Degree(30.0f);
	//ei.emissionrate = 40.f;
	//ei.startscale = 6.1f;
	//ei.endscale = 1.05f;
	//ei.scaleflip = true;
	//ei.startalpha = 1.0f;
	//ei.endalpha = 0.0f;
	//ei.alphaflip = false;
	//ei.livetime = 2000.f;
	//ei.max_initialspeed = 0.03f;
	//ei.min_initialspeed = 0.01f;
	//ei.totalparticles = 800;
	//ei.texture = "textures/smoke.tga";
	//ParticleSystem().AddEmitter(&ei);

	//Setup The SUN!
	LIGHT Light;
	memset(&Light, 0x00, sizeof(Light));
	Light.Type = LIGHTTYPE::LIGHT_DIRECTIONAL;
	Light.Diffuse = mColour4(1.f, 1.f, 1.f, 1.f);
	Light.Direction = vec3::I_Normalize(vec3::Vector3(-1,-1,0));
	Light.Position = vec3::Vector3(0,0,0);
	Light.Range = 300.f;
	Light.Phi = 0.6f;
	Light.Theta = 0.6f;
	Light.Attenuation0 = 1.0f;
	Light.Attenuation1 = 0.0014f;
	Light.Attenuation2 = 0.000007f;
	RenderSystem().SetLight(0, Light);
}

//Update Game World
void GameWorld::Update(float dt)
{
	//Tick Controllers
	for(std::vector<BaseController*>::iterator iter = m_controllers.begin(); iter != m_controllers.end(); ++iter)
		(*iter)->Update(dt);

	//Update ParticleSystem
	//ParticleSystem().Update(dt);

	// !!! PARTICLE TEST !!!!
	//ParticleSystem().UpdateEmitterPosition(0, vec3::Vector3(m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetPosition() + (m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetDirection() * 5.5f)));
}

//Render Game World
void GameWorld::Render()
{
	//Keep random generator randomly seeded
	rnd_AddList();

	//Show Frame Rate
	if(GetTimeUINT() > fps_reg)
	{
		char fr[128];
		const vec3::Vector3 ypr = mat4::GetYawPitchRoll(&m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetCarInfo()->GetChassisMatrix());
		sprintf(fr, "Burnin' Rubber - FPS: %i - SPEED: %.2f X: %.2f Y: %.2f Z: %.2f - %.2f, %.2f, %.2f", 
			fps, 
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetSpeedKPH(),
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetPosition().x,
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetPosition().y,
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetPosition().z,
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetDirection().x,
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetDirection().y,
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetDirection().z);
		SetWindowText(hWnd, fr);
		fps_reg = GetTimeUINT() + 1000;
		fps = 0;
	}
	fps++;

	//Performance Analysis
	#ifdef _DEBUG
		PerformanceAnalysis().AddLog();
	#endif

	//Tick Bullet Physics
	BulletPhysics().Update(0.f);

	//Tick Controllers
	for(std::vector<BaseController*>::iterator iter = m_controllers.begin(); iter != m_controllers.end(); ++iter)
		(*iter)->Render();

	/* Render SceneNode Graph */
	SceneGraph().ChainRender();

	/* Render Particle System */
	ParticleSystem().Render();
}

//Input Messages
void GameWorld::Messages(flex::components::sInputState* wButtons)
{
	/* ///////////////////////////////////
		XBOX CONTROLLER
	*/ ///////////////////////////////////
	if(wButtons->m_Controller)
	{
		//Switch Vehicle
		if(GetTime() > m_switchreg)
		{
			if(wButtons->m_ButtonB)
			{
				m_selectedvehicle++;

				if(m_selectedvehicle >= m_vehiclecontroller->GetVehicleCount())
					m_selectedvehicle = 0;

				m_cameracontroller->SetTargetVehicle(m_vehiclecontroller->GetVehicle(m_selectedvehicle));
			}

			m_switchreg = GetTime() + 100;
		}

		//Flip Car
		if(wButtons->m_ButtonX)
		{
			//Get Matrix
			mat4::MATRIX4 mat = m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetCarInfo()->GetChassisMatrix();
			
			//Only flip if car is upside down
			if(mat._22 <= 0.f)
			{
				//Offset Height
				mat._42 += 0.2f;

				//Set Direction
				vec3::Vector3 newdir = Vector3(mat._31, -mat._32, mat._33);
				
				const vec3::Vector3 nup = vec3::Vector3(0,1,0);
				const vec3::Vector3 c = vec3::I_Normalize(vec3::CrossProduct(nup, newdir));
				const vec3::Vector3 rup = vec3::CrossProduct(newdir, c);
				mat._11 = c.x;
				mat._12 = c.y;
				mat._13 = c.z;
				mat._21 = rup.x;
				mat._22 = rup.y;
				mat._23 = rup.z;
				mat._31 = newdir.x;
				mat._32 = newdir.y;
				mat._33 = newdir.z;

				//Set Matrix
				m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetCarInfo()->GetRigidBody()->clearForces();
				m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetCarInfo()->GetRigidBody()->setAngularVelocity(btVector3(0,0,0));
				m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetCarInfo()->GetRigidBody()->setLinearVelocity(btVector3(0,0,0));
				m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetCarInfo()->SetChassisMatrix(&mat);
			}
		}

		//Break & Accelerate
		if(wButtons->m_ButtonA)
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->SetBreakingForce(0.3f);
		else
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->SetBreakingForce((float)wButtons->m_TRIGGERLEFT);

		if(wButtons->m_ButtonX)
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->SetEngineForce((float)-wButtons->m_TRIGGERRIGHT);
		else
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->SetEngineForce((float)wButtons->m_TRIGGERRIGHT);

		//Steering
		if((float)wButtons->m_THUMBLEFTX < 0)
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->SetSteering((float)wButtons->m_THUMBLEFTX);
		else if((float)wButtons->m_THUMBLEFTX > 0)
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->SetSteering((float)wButtons->m_THUMBLEFTX);
		else
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->SetSteering((float)0);
	}
	else
	{
		/* ///////////////////////////////////
			KEYBOARD
		*/ ///////////////////////////////////

		//Car Switch
		if(GetTime() > m_switchreg)
		{
			if(wButtons->m_ButtonB)
			{
				m_selectedvehicle++;

				if(m_selectedvehicle >= m_vehiclecontroller->GetVehicleCount())
					m_selectedvehicle = 0;

				m_cameracontroller->SetTargetVehicle(m_vehiclecontroller->GetVehicle(m_selectedvehicle));
			}

			m_switchreg = GetTime() + 100;
		}

		//Flip Car
		if(wButtons->m_ButtonX)
		{
			//Get Matrix
			mat4::MATRIX4 mat = m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetCarInfo()->GetChassisMatrix();
			
			//Only flip if car is upside down
			if(mat._22 <= 0.f)
			{
				//Offset Height
				mat._42 += 0.2f;

				//Set Direction
				vec3::Vector3 newdir = Vector3(mat._31, -mat._32, mat._33);
				
				const vec3::Vector3 nup = vec3::Vector3(0,1,0);
				const vec3::Vector3 c = vec3::I_Normalize(vec3::CrossProduct(nup, newdir));
				const vec3::Vector3 rup = vec3::CrossProduct(newdir, c);
				mat._11 = c.x;
				mat._12 = c.y;
				mat._13 = c.z;
				mat._21 = rup.x;
				mat._22 = rup.y;
				mat._23 = rup.z;
				mat._31 = newdir.x;
				mat._32 = newdir.y;
				mat._33 = newdir.z;

				//Set Matrix
				m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetCarInfo()->GetRigidBody()->clearForces();
				m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetCarInfo()->GetRigidBody()->setAngularVelocity(btVector3(0,0,0));
				m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetCarInfo()->GetRigidBody()->setLinearVelocity(btVector3(0,0,0));
				m_vehiclecontroller->GetVehicle(m_selectedvehicle)->GetCarInfo()->SetChassisMatrix(&mat);
			}
		}

		//Handbreak
		if(wButtons->m_ButtonA)
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->SetBreakingForce(0.3f);
		else
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->SetBreakingForce(0.0f);


		//Break & Accelerate
		if(wButtons->m_ArrowKeys.m_ButtonUp)
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->SetEngineForce(1.0f);
		else if(wButtons->m_ArrowKeys.m_ButtonDown)
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->SetEngineForce(-1.0f);
		else
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->SetEngineForce(0.0f);

		//Steering
		if(wButtons->m_ArrowKeys.m_ButtonLeft)
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->IncrementSteering(-0.2f);
		else if(wButtons->m_ArrowKeys.m_ButtonRight)
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->IncrementSteering(0.2f);
		else
			m_vehiclecontroller->GetVehicle(m_selectedvehicle)->NeutralizeSteering(0.85f);
	}
}






