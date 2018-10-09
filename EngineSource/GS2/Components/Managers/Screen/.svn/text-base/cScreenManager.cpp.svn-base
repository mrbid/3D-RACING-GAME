//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cScreenManager.cpp
// Description: Generic Screen Management System
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#include "precom.h"
#include "cScreenManager.hpp"
#include "../../../Components/Managers/Screen/GameScreen/IGameScreen.hpp"
#include "../../../Components/Managers/Screen/GameScreen/cGameScreenSplash.hpp"
#include "../../../Components/Managers/Screen/GameScreen/cGameScreenLoading.hpp"
#include "../../../Components/Managers/Screen/GameScreen/cGameScreenHud.hpp"
#include "../../../Components/Managers/Screen/GameScreen/cGameScreenController.hpp"
#include "../../../Components/Managers/Screen/GameScreen/cGameScreenTrack.hpp"
#include "../../../Components/Managers/Screen/GameScreen/cGameScreenCar.hpp"
#include "../../../Components/Managers/Screen/GameScreen/cGameScreenCarBasic.hpp"
#include "../../../GameWorld.h"

namespace flex
{
	namespace components
	{
		cScreenManager* cScreenManager::m_pInstance = NULL;

		cScreenManager::cScreenManager(void) : m_ScreenDepth(0), m_CacheScreens(true), m_resetprojection(false), m_RenderHud(true)
		{
			std::cout << "S: cScreenManager - Created" << std::endl;
		}

		cScreenManager::~cScreenManager(void)
		{
		}

		bool cScreenManager::Initialise( void )
		{
			cGameScreenLoading* Screen0 = new cGameScreenLoading();
			m_LoadingId = SMG->AddScreen( Screen0 );
			return true;
		}

		bool cScreenManager::Load( void )
		{
			//Controller
			cGameScreenController* Screen2 = new cGameScreenController();
			SMG->PushScreen( SMG->AddScreen( Screen2 ) );
			//loading
			SMG->PushScreen( m_LoadingId );
			//car
			//cGameScreenCar* Screen5 = new cGameScreenCar();
			cGameScreenCarBasic* Screen5 = new cGameScreenCarBasic();
			SMG->PushScreen( SMG->AddScreen( Screen5 ) );
			//track
			cGameScreenTrack* Screen4 = new cGameScreenTrack();
			SMG->PushScreen( SMG->AddScreen( Screen4 ) );
			//Splash
			cGameScreenSplash* Screen1 = new cGameScreenSplash();
			SMG->PushScreen( SMG->AddScreen( Screen1 ) );
			//Hud
			cGameScreenHud* Screen3 = new cGameScreenHud();
			SMG->SetHudId( SMG->AddScreen( Screen3 ) );
			SMG->SetRenderHud(true);
			

			//SMG->PushScreen( m_LoadingId );

			//test
			//SMG->PushScreen( m_HudId );

			std::cout << "S: cScreenManager - Initialised" << std::endl;
			return true;
		}

		int cScreenManager::AddScreen( IGameScreen* Screen)
		{
			if(Screen != NULL)
			{
				m_Screens.push_back(Screen);
				std::cout << "S: cScreenManager - " << typeid(Screen).name() << " was added to Screens Vector At: " << m_Screens.size() - 1 << std::endl;
				return m_Screens.size() - 1;
			}	
		}

		void cScreenManager::PushScreen( int ID )
		{
			m_ScreenFlowOrder.push_back(ID);
			//Pause World Model Ticking
		}

		void cScreenManager::PopScreen( void )
		{
			m_ScreenFlowOrder.pop_back();
			if(m_ScreenFlowOrder.empty())
			{
				//Start World Model Ticking
			}
			else
			{
				m_Screens[(unsigned int)m_ScreenFlowOrder.back()]->Refresh();
			}
		}

		void cScreenManager::Messages( sInputState* wButtons )
		{
			if(m_ScreenFlowOrder.empty())
			{
				GameWorld().Messages(wButtons);
				//Send Input Messages To World Model
			}
			else
			{
				m_Screens[(unsigned int)m_ScreenFlowOrder.back()]->Messages(wButtons);
			}
		}

		void cScreenManager::Update( const float& dt )
		{
			if(m_ScreenFlowOrder.empty())
			{
				GameWorld().Update(dt);
				//Update Call World Model Update
				if(m_RenderHud)
				{
					m_Screens[(unsigned int)m_HudId]->Update(dt);
				}
			}
			else
			{
				m_Screens[(unsigned int)m_ScreenFlowOrder.back()]->Update( dt );
			}
		}

		void cScreenManager::Render()
		{
			if(m_ScreenFlowOrder.empty())
			{

				if(m_resetprojection == true)
				{
					GameWorld().SetProjection();
					m_resetprojection = false;
				}
				RenderSystem().ClearRender();
				RenderSystem().BeginRender();

				GameWorld().Render();

				if(m_RenderHud)
				{
					SetMatrices();
					// Disable the z buffer
					RenderSystem().GetDevice()->SetRenderState( D3DRS_ZENABLE, FALSE );
					RenderSystem().GetDevice()->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
					m_Screens[(unsigned int)m_HudId]->Render();
					m_resetprojection = true;
					// Disable the z buffer
					RenderSystem().GetDevice()->SetRenderState( D3DRS_ZENABLE, TRUE );
					RenderSystem().GetDevice()->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
				}
				RenderSystem().EndRender();
				RenderSystem().ShowRender();
			}
			else
			{
				assert(m_ScreenFlowOrder.size()-m_ScreenDepth >= 0 && "Problem In cScreenManager::Render");

				if(m_resetprojection == false)
					m_resetprojection = true;

				if(m_ScreenDepth == 0)
				{
					//RenderSystem().SetFillModeWireframe();
					//RenderSystem().SetAmbientLight(180, 180, 180, 0);
					SetMatrices();
					RenderSystem().ClearRender();
					RenderSystem().BeginRender();
					m_Screens[(unsigned int)m_ScreenFlowOrder.back()]->Render();
					RenderSystem().EndRender();
					RenderSystem().ShowRender();
				}
				else
				{
					SetMatrices();
					// Clear the back buffer to black
					RenderSystem().ClearRender();

					// Note: all drawing must occur between the BeginScene and EndScene calls
					if (SUCCEEDED(RenderSystem().GetDevice()->BeginScene()))
					{		
						for(unsigned int i = 0; i < m_ScreenDepth; i++)
						{
							m_Screens[(unsigned int)m_ScreenFlowOrder[(m_ScreenFlowOrder.size()-m_ScreenDepth) + i]]->Render();
						}
						RenderSystem().GetDevice()->EndScene();
						RenderSystem().ShowRender();
					}
				}
			}
		}

		void cScreenManager::RenderLoadScreen()
		{
			RenderSystem().ClearRender();
			RenderSystem().BeginRender();
			SetMatrices();
			m_Screens[(unsigned int)m_LoadingId]->Render();
			m_resetprojection = true;
			RenderSystem().EndRender();
			RenderSystem().ShowRender();
			//RenderSystem().GetDevice()->GetTransform( D3DTS_VIEW, &m_MatView );
		}

		void cScreenManager::SetProgressbar( const int& percentage )
		{
			((cGameScreenLoading*)m_Screens[(unsigned int)m_LoadingId])->SetProgressBar( percentage );
		}

		int cScreenManager::AddSprite( const std::string &filename, const int &width, const int &height )
		{
			for(int i = 0; i < m_Sprites.size(); i++)
			{
				if(m_Sprites[i]->GetFileName() == filename)
				{
					return i;
				}
			}
			cSprite* Sprite = new cSprite(RenderSystem().GetDevice());
			m_Sprites.push_back(Sprite);
			Sprite->LoadTexture(filename, width, height);

			return m_Sprites.size()-1;
		}

		int cScreenManager::AddQuad( const std::string &filename, const int &width, const int &height )
		{
			for(int i = 0; i < m_Quads.size(); i++)
			{
				if(m_Quads[i]->GetFileName() == filename)
				{
					return i;
				}
			}
			cQuad* Quad = new cQuad( RenderSystem().GetDevice() );
			m_Quads.push_back(Quad);
			Quad->LoadTexture(filename, width, height);

			return m_Quads.size()-1;
		}

		void cScreenManager::RenderSprite( int SpriteID, float C1X, float C1Y, float C1Z, float C2X, float C2Y, float C2Z )
		{
			//m_Sprites[SpriteID]->Render(D3DXVECTOR3(C1X, C1Y, C1Z), D3DXVECTOR3(C2X, C2Y, C2Z));
		}

		void cScreenManager::RenderQuad(const int &QuadID,  const D3DXMATRIX &Matrix )
		{
			m_Quads[QuadID]->Render(Matrix);
		}

		void cScreenManager::SetMatrices( void )
		{
			D3DXMATRIX matViewSave;
			D3DXMatrixIdentity(&matViewSave);
			//RenderSystem().GetDevice()->GetTransform( D3DTS_VIEW, &matViewSave );
			//RenderSystem().GetDevice()->SetTransform( D3DTS_VIEW, &m_MatView );

			D3DXMATRIX matProj;
			D3DXMatrixPerspectiveFovLH( &matProj, D3DXToRadian( 30.0f ), 1280.0f / 720.0f, 0.1f, 100.0f );
			RenderSystem().GetDevice()->SetTransform( D3DTS_PROJECTION, &matProj );

			RenderSystem().GetDevice()->SetRenderState( D3DRS_LIGHTING, FALSE );
			RenderSystem().GetDevice()->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

			RenderSystem().GetDevice()->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
			RenderSystem().GetDevice()->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

			RenderSystem().GetDevice()->SetTransform( D3DTS_VIEW, &matViewSave );
		}

		void cScreenManager::SetPopLoadingScreen( const bool& popscreen )
		{
			((cGameScreenLoading*)m_Screens[(unsigned int)m_LoadingId])->SetPopScreen( popscreen );
		}

		void cScreenManager::SetTrack( const int& id )
		{
			((cGameScreenLoading*)m_Screens[(unsigned int)m_LoadingId])->SetTrackId(id);
		}

		void cScreenManager::SetCar( const int& id )
		{
			((cGameScreenLoading*)m_Screens[(unsigned int)m_LoadingId])->SetCarId(id);
		}

	} // Namespace Components
} // Namespace Flex