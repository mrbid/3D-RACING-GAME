//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cGameScreenLoading.cpp
// Description: 
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#include "precom.h"
#include "cGameScreenLoading.hpp"
#include "../cScreenManager.hpp"
#include "MilliTimer.h"
#include "GameWorld.h"
#include "Vector3.h"

namespace flex
{
	namespace components
	{
		cGameScreenLoading::cGameScreenLoading( void ) : Texture1ScaleX(6.4f), Texture1ScaleY(6.4f), Texture1ScaleZ(1.0f), LoadingPercentage(0.0f), PopScreenCheck(false)
		{
			m_TextureID1 = SMG->AddQuad("Data\\Textures\\Loading.png", 1280, 720);
			m_TextureIDProgressbarBack = SMG->AddQuad("Data\\Textures\\ProgressBarBack.png", 100, 14);
			m_TextureIDProgressbarLoad = SMG->AddQuad("Data\\Textures\\ProgressBarLoad.png", 100, 14);
			m_TimeLast  = GetTime();
		}

		cGameScreenLoading::~cGameScreenLoading( void )
		{
		}

		void cGameScreenLoading::Render( void )
		{
			D3DXMATRIX matTemp;

			D3DXMATRIX matTrans;
			D3DXMATRIX matRot;
			D3DXMATRIX matScale;
			D3DXMATRIX matWorld;

			D3DXMatrixScaling(&matScale, Texture1ScaleX, Texture1ScaleY, Texture1ScaleZ);

			D3DXMatrixTranslation( &matTrans, 0.0f, 0.0f, 13.5f );
			float  g_fSpinX = 0.0f;
			float  g_fSpinY = 0.0f;
			D3DXMatrixRotationYawPitchRoll( &matRot, 
				D3DXToRadian(g_fSpinX), 
				D3DXToRadian(g_fSpinY), 
				0.0f );
			matTemp  = matScale * matTrans;
			matWorld = matRot   * matTemp;

			SMG->RenderQuad(m_TextureID1, matWorld);

			RenderProgressBar();
		}

		void cGameScreenLoading::Update( const float& dt )
		{
			//if(PopScreenCheck == true)
			//{
			//	SMG->PopScreen();
			//}
			if(LoadingPercentage >= 99)
			{
				SMG->PopScreen();
			}
		}

		void cGameScreenLoading::Messages(sInputState* wButtons)
		{

		}

		void cGameScreenLoading::Refresh( void )
		{
			Render();
			LoadTrack( trackId );
			LoadCar( carId );
			m_TimeLast = GetTime();
		}

		void cGameScreenLoading::LoadTrack( const int& id )
		{
				//Stunt
				if(id == 0)
				{
					GameWorld().GetTrackController()->LoadTrack("stunt");
					//RenderSystem().GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
				}

				//Shib
				if(id == 1)
				{
					GameWorld().GetTrackController()->LoadTrack("shib");
					//RenderSystem().GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
				}
		}

		void cGameScreenLoading::LoadCar( const int& id )
		{
			if(id == 0)//AudiS3
			{
				if(trackId == 0)
				{
					GameWorld().GetVehicleController()->AddVehicle("audi", "textures/audimap.jpg", vec3::Vector3(40.f, 30.2f, 0.f), vec3::Vector3(-0.52f,0,0.85f));
				}
				if(trackId == 1)
				{
					GameWorld().GetVehicleController()->AddVehicle("audi", "textures/audimap.jpg", vec3::Vector3(-2335.f, -26.2f, -1335.f), vec3::Vector3(-0.52f,0,0.85f));
					GameWorld().GetAIController()->AddAIVechicles();
				}
			}
			else if(id == 1)//Clio
			{
				if(trackId == 0)
				{
					GameWorld().GetVehicleController()->AddVehicle("clio", "textures/clioblue.jpg", vec3::Vector3(40.f, 30.2f, 0.f), vec3::Vector3(-0.52f,0,0.85f));
				}
				if(trackId == 1)
				{
					GameWorld().GetVehicleController()->AddVehicle("clio", "textures/clioblue.jpg", vec3::Vector3(-2335.f, -26.2f, -1335.f), vec3::Vector3(-0.52f,0,0.85f));
					GameWorld().GetAIController()->AddAIVechicles();
				}
			}
			else if(id == 2)//Focus_blue
			{
				if(trackId == 0)
				{
					GameWorld().GetVehicleController()->AddVehicle("focus", "textures/focusblue.jpg", vec3::Vector3(40.f, 30.2f, 0.f), vec3::Vector3(-0.52f,0,0.85f));
				}
				if(trackId == 1)
				{
					GameWorld().GetVehicleController()->AddVehicle("focus", "textures/focusblue.jpg", vec3::Vector3(-2335.f, -26.2f, -1335.f), vec3::Vector3(-0.52f,0,0.85f));
					GameWorld().GetAIController()->AddAIVechicles();
				}
			}
			else if(id == 3)//Gallardo_green
			{
				if(trackId == 0)
				{
					GameWorld().GetVehicleController()->AddVehicle("gallardo", "textures/gallardoorange.jpg", vec3::Vector3(40.f, 30.2f, 0.f), vec3::Vector3(-0.52f,0,0.85f));
				}
				if(trackId == 1)
				{
					GameWorld().GetVehicleController()->AddVehicle("gallardo", "textures/gallardoorange.jpg", vec3::Vector3(-2335.f, -26.2f, -1335.f), vec3::Vector3(-0.52f,0,0.85f));
					GameWorld().GetAIController()->AddAIVechicles();
				}
			}
			else if(id == 4)//GolfGTI
			{
				if(trackId == 0)
				{
					GameWorld().GetVehicleController()->AddVehicle("gti", "textures/golfgti.jpg", vec3::Vector3(40.f, 30.2f, 0.f), vec3::Vector3(-0.52f,0,0.85f));
				}
				if(trackId == 1)
				{
					GameWorld().GetVehicleController()->AddVehicle("gti", "textures/golfgti.jpg", vec3::Vector3(-2335.f, -26.2f, -1335.f), vec3::Vector3(-0.52f,0,0.85f));
					GameWorld().GetAIController()->AddAIVechicles();
				}
			}
			else if(id == 5)//hotrod
			{
				if(trackId == 0)
				{
					GameWorld().GetVehicleController()->AddVehicle("hotrod", "textures/hotrodmap.jpg", vec3::Vector3(40.f, 30.2f, 0.f), vec3::Vector3(-0.52f,0,0.85f));
				}
				if(trackId == 1)
				{
					GameWorld().GetVehicleController()->AddVehicle("hotrod", "textures/hotrodmap.jpg", vec3::Vector3(-2335.f, -26.2f, -1335.f), vec3::Vector3(-0.52f,0,0.85f));
					GameWorld().GetAIController()->AddAIVechicles();
				}
			}
			else if(id == 6)//murc
			{
				if(trackId == 0)
				{
					GameWorld().GetVehicleController()->AddVehicle("murc", "textures/murctex.jpg", vec3::Vector3(40.f, 30.2f, 0.f), vec3::Vector3(-0.52f,0,0.85f));
				}
				if(trackId == 1)
				{
					GameWorld().GetVehicleController()->AddVehicle("murc", "textures/murctex.jpg", vec3::Vector3(-2335.f, -26.2f, -1335.f), vec3::Vector3(-0.52f,0,0.85f));
					GameWorld().GetAIController()->AddAIVechicles();
				}
			}
			else if(id == 7)//rx8
			{
				if(trackId == 0)
				{
					GameWorld().GetVehicleController()->AddVehicle("rx8", "textures/rx8blue.jpg", vec3::Vector3(40.f, 30.2f, 0.f), vec3::Vector3(-0.52f,0,0.85f));
				}
				if(trackId == 1)
				{
					GameWorld().GetVehicleController()->AddVehicle("rx8", "textures/rx8blue.jpg", vec3::Vector3(-2335.f, -26.2f, -1335.f), vec3::Vector3(-0.52f,0,0.85f));
					GameWorld().GetAIController()->AddAIVechicles();
				}
			}
			else if(id == 8)//smart_batman
			{
				if(trackId == 0)
				{
					GameWorld().GetVehicleController()->AddVehicle("smart", "textures/Batman Smart.jpg", vec3::Vector3(40.f, 30.2f, 0.f), vec3::Vector3(-0.52f,0,0.85f));
				}
				if(trackId == 1)
				{
					GameWorld().GetVehicleController()->AddVehicle("smart", "textures/Batman Smart.jpg", vec3::Vector3(-2335.f, -26.2f, -1335.f), vec3::Vector3(-0.52f,0,0.85f));
					GameWorld().GetAIController()->AddAIVechicles();
				}
			}
			else if(id == 9)//viper_black
			{
				if(trackId == 0)
				{
					GameWorld().GetVehicleController()->AddVehicle("viper", "textures/Viper_Black.jpg", vec3::Vector3(40.f, 30.2f, 0.f), vec3::Vector3(-0.52f,0,0.85f));
				}
				if(trackId == 1)
				{
					GameWorld().GetVehicleController()->AddVehicle("viper", "textures/Viper_Black.jpg", vec3::Vector3(-2335.f, -26.2f, -1335.f), vec3::Vector3(-0.52f,0,0.85f));
					GameWorld().GetAIController()->AddAIVechicles();
				}
			}
			else if(id == 10)//x-6_black
			{				
				if(trackId == 0)
				{
					GameWorld().GetVehicleController()->AddVehicle("x6", "textures/X-6_Black.jpg", vec3::Vector3(40.f, 30.2f, 0.f), vec3::Vector3(-0.52f,0,0.85f));
				}
				if(trackId == 1)
				{
					GameWorld().GetVehicleController()->AddVehicle("x6", "textures/X-6_Black.jpg", vec3::Vector3(-2335.f, -26.2f, -1335.f), vec3::Vector3(-0.52f,0,0.85f));
					GameWorld().GetAIController()->AddAIVechicles();
				}
			}
			else if(id == 10)//350z_blue
			{
				if(trackId == 0)
				{
					GameWorld().GetVehicleController()->AddVehicle("350z", "textures/350z_orange.jpg", vec3::Vector3(40.f, 30.2f, 0.f), vec3::Vector3(-0.52f,0,0.85f));
				}
				if(trackId == 1)
				{
					GameWorld().GetVehicleController()->AddVehicle("350z", "textures/350z_orange.jpg", vec3::Vector3(-2335.f, -26.2f, -1335.f), vec3::Vector3(-0.52f,0,0.85f));
					GameWorld().GetAIController()->AddAIVechicles();
				}
			}

			GameWorld().m_cameracontroller->SetTargetVehicle(GameWorld().GetVehicleController()->GetVehicle(0));
		}

		void cGameScreenLoading::RenderProgressBar( void )
		{
			D3DXMATRIX matTemp;

			D3DXMATRIX matTrans;
			D3DXMATRIX matRot;
			D3DXMATRIX matScale;
			D3DXMATRIX matWorld;

			D3DXMatrixScaling(&matScale, 6.4f, 1.0f, 1.0f);

			D3DXMatrixTranslation( &matTrans, 0.0f, -3.45f, 13.4f );
			float  g_fSpinX = 0.0f;
			float  g_fSpinY = 0.0f;
			D3DXMatrixRotationYawPitchRoll( &matRot, 
				D3DXToRadian(g_fSpinX), 
				D3DXToRadian(g_fSpinY), 
				0.0f );
			matTemp  = matScale * matTrans;
			matWorld = matRot   * matTemp;

			SMG->RenderQuad(m_TextureIDProgressbarBack, matWorld);

			D3DXMATRIX matTemp2;

			D3DXMATRIX matTrans2;
			D3DXMATRIX matRot2;
			D3DXMATRIX matScale2;
			D3DXMATRIX matWorld2;

			D3DXMatrixScaling(&matScale2, 0.064f * LoadingPercentage, 1.0f, 1.0f);

			D3DXMatrixTranslation( &matTrans2, -6.4f + (0.064f * LoadingPercentage), -3.45f, 13.3f );
			float  g_fSpinX2 = 0.0f;
			float  g_fSpinY2 = 0.0f;
			D3DXMatrixRotationYawPitchRoll( &matRot2, 
				D3DXToRadian(g_fSpinX2), 
				D3DXToRadian(g_fSpinY2), 
				0.0f );
			matTemp2  = matScale2 * matTrans2;
			matWorld2 = matRot2   * matTemp2;

			SMG->RenderQuad(m_TextureIDProgressbarLoad, matWorld2);
		}

		void cGameScreenLoading::SetProgressBar( const int& percentage )
		{
			if(percentage >= 100 )
			{
				LoadingPercentage = 100;
			}
			else if(percentage <= 0)
			{
				LoadingPercentage = 0;
			}
			else
			{
				LoadingPercentage = percentage;
			}
		}

	} // Namespace Components
} // Namespace Flex