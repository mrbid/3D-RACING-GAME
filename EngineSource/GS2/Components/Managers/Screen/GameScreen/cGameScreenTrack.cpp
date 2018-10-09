//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cGameScreenTrack.cpp
// Description: 
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#include "precom.h"
#include "cGameScreenTrack.hpp"
#include "../cScreenManager.hpp"
#include "MilliTimer.h"
#include "GameWorld.h"

namespace flex
{
	namespace components
	{
		cGameScreenTrack::cGameScreenTrack( void ) : m_TextureBackgroundScaleX(6.4f), m_TextureBackgroundScaleY(6.4f), m_TextureBackgroundScaleZ(1.0f), currentSelection(1), m_TrackScaleX(2.0f), m_TrackScaleY(2.0f), m_TrackScaleZ(1.0f)
		{
			m_TextureBackground = SMG->AddQuad("Data\\Textures\\ScreenBackground.png", 1280, 720);
			//trackMap = new std::map<std::string, int>;

			m_TextureTrack1 = SMG->AddQuad("Data\\Textures\\Tracks\\stunt.png", 500, 500);
			m_TextureTrack2 = SMG->AddQuad("Data\\Textures\\Tracks\\shib.png",  500, 500);
			m_TextureTrack3 = SMG->AddQuad("Data\\Textures\\Tracks\\shib2.png", 500, 500);
			m_TextureTrack4 = SMG->AddQuad("Data\\Textures\\Tracks\\shib3.png", 500, 500);
			m_TextureTrack5 = SMG->AddQuad("Data\\Textures\\Tracks\\shib4.png", 500, 500);
			m_TextureTrack1h = SMG->AddQuad("Data\\Textures\\Tracks\\stunth.png", 500, 500);
			m_TextureTrack2h = SMG->AddQuad("Data\\Textures\\Tracks\\shibh.png",  500, 500);
			m_TextureTrack3h = SMG->AddQuad("Data\\Textures\\Tracks\\shib2h.png", 500, 500);
			m_TextureTrack4h = SMG->AddQuad("Data\\Textures\\Tracks\\shib3h.png", 500, 500);
			m_TextureTrack5h = SMG->AddQuad("Data\\Textures\\Tracks\\shib4h.png", 500, 500);

			m_TexturePadlock = SMG->AddQuad("Data\\Textures\\Buttons\\padlock.png", 722, 665);

			m_TextureLeft  = SMG->AddQuad("Data\\Textures\\Buttons\\Left.png",  200, 100);
			m_TextureRight = SMG->AddQuad("Data\\Textures\\Buttons\\Right.png", 200, 100);

			m_TimeLast  = GetTime();
		}

		cGameScreenTrack::~cGameScreenTrack( void )
		{
		}

		void cGameScreenTrack::Render( void )
		{
			RenderBackground();
			RenderTracks();
		}

		void cGameScreenTrack::Update( const float& dt )
		{

		}

		void cGameScreenTrack::Messages(sInputState* wButtons)
		{
			if(m_TimeLast + 250 < GetTime())
			{
				if(wButtons->m_THUMBLEFTX >  0.5 || wButtons->m_ArrowKeys.m_ButtonLeft == true)
				{
					if(currentSelection > 0 && currentSelection <= 4)
					{
						currentSelection--;
						m_TimeLast = GetTime();
					}
				}
				if(wButtons->m_THUMBLEFTX < -0.5 || wButtons->m_ArrowKeys.m_ButtonRight == true)
				{
					if(currentSelection >= 0 && currentSelection < 4)
					{
						currentSelection++;
						m_TimeLast = GetTime();
					}
				}
				if(wButtons->m_ButtonA == true || wButtons->m_Start == true)
				{
					if(currentSelection == 0)
					{
						SMG->SetTrack( 0 );
						SMG->PopScreen();
					}
					else if(currentSelection == 1)
					{
						SMG->SetTrack( 1 );
						SMG->PopScreen();
					}
				}
			}
		}

		void cGameScreenTrack::Refresh( void )
		{
			//if(trackList != NULL)
			//{
			//	delete trackList;
			//}
			//trackList = new std::vector<std::string>;
			//GameWorld().GetTrackController()->GetAvalibleTracks(trackList);
			//for (int i = 0; i < trackList->size(); i++)
			//{
			//	(*trackMap)[ (*trackList)[i] ] = SMG->AddQuad( "Data\\Textures\\Tracks\\" + (*trackList)[i] + ".png",  500, 500 );
			//	//trackMap->insert( (*trackList)[i], SMG->AddQuad( (*trackList)[i],  500, 500 ) );
			//}
			//(*trackMap)[ "shib" ]  = SMG->AddQuad( "Data\\Textures\\Tracks\\shib.png",  500, 500 );
			//(*trackMap)[ "stunt" ] = SMG->AddQuad( "Data\\Textures\\Tracks\\stunt.png",  500, 500 );
			m_TimeLast = GetTime();
		}

		void cGameScreenTrack::RenderBackground( void )
		{
			D3DXMATRIX matTemp2;

			D3DXMATRIX matTrans2;
			D3DXMATRIX matRot2;
			D3DXMATRIX matScale2;
			D3DXMATRIX matWorld2;
			D3DXMatrixScaling(&matScale2, m_TextureBackgroundScaleX, m_TextureBackgroundScaleY, m_TextureBackgroundScaleZ);

			D3DXMatrixTranslation( &matTrans2, 0.0f, 0.0f, 13.5f );
			float  g_fSpinX2 = 0.0f;
			float  g_fSpinY2 = 0.0f;
			D3DXMatrixRotationYawPitchRoll( &matRot2, 
				D3DXToRadian(g_fSpinX2), 
				D3DXToRadian(g_fSpinY2), 
				0.0f );
			matTemp2  = matScale2 * matTrans2;
			matWorld2 = matRot2   * matTemp2;
			SMG->RenderQuad(m_TextureBackground, matWorld2);
		}

		void cGameScreenTrack::RenderTracks( void )
		{
			if(currentSelection == 0)
			{
				RenderTrackSample( m_TextureTrack1h,   0.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack2,  -4.0f, 0.0f, 13.4f);
			}
			else if(currentSelection == 1)
			{
				RenderTrackSample( m_TextureTrack1,  4.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack2h,  0.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack3, -4.0f, 0.0f, 13.4f);
				RenderArrow(m_TextureLeft, -5.0f, 3.0f, 13.4f);
				RenderArrow(m_TextureRight, 5.0f, 3.0f, 13.4f);
				RenderPadLock(m_TexturePadlock, -5.0f, 0.0f, 13.4f);
			}
			else if(currentSelection == 2)
			{
				RenderTrackSample( m_TextureTrack2,  4.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack3h,  0.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack4, -4.0f, 0.0f, 13.4f);
				RenderArrow(m_TextureLeft, -5.0f, 3.0f, 13.4f);
				RenderArrow(m_TextureRight, 5.0f, 3.0f, 13.4f);
				RenderPadLock(m_TexturePadlock, -5.0f, 0.0f, 13.4f);
				RenderPadLock(m_TexturePadlock, 0.0f, 0.0f, 13.4f);
			}
			else if(currentSelection == 3)
			{
				RenderTrackSample( m_TextureTrack3,  4.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack4h,  0.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack5, -4.0f, 0.0f, 13.4f);
				RenderArrow(m_TextureLeft, -5.0f, 3.0f, 13.4f);
				RenderArrow(m_TextureRight, 5.0f, 3.0f, 13.4f);
				RenderPadLock(m_TexturePadlock, 5.0f, 0.0f, 13.4f);
				RenderPadLock(m_TexturePadlock, -5.0f, 0.0f, 13.4f);
				RenderPadLock(m_TexturePadlock, 0.0f, 0.0f, 13.4f);
			}
			else if(currentSelection == 4)
			{
				RenderTrackSample( m_TextureTrack4,  4.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack5h,  0.0f, 0.0f, 13.4f);
				RenderArrow(m_TextureRight, -5.0f, 3.0f, 13.4f);
				RenderPadLock(m_TexturePadlock, 5.0f, 0.0f, 13.4f);
				//RenderPadLock(m_TexturePadlock, -5.0f, 0.0f, 13.4f);
				RenderPadLock(m_TexturePadlock, 0.0f, 0.0f, 13.4f);
			}

		}

		void cGameScreenTrack::RenderTrackSample( int textureID, float positionX, float positionY, float positionZ )
		{
			D3DXMATRIX matTemp2;

			D3DXMATRIX matTrans2;
			D3DXMATRIX matRot2;
			D3DXMATRIX matScale2;
			D3DXMATRIX matWorld2;
			D3DXMatrixScaling(&matScale2, m_TrackScaleX, m_TrackScaleY, m_TrackScaleZ);

			D3DXMatrixTranslation( &matTrans2, positionX, positionY, positionZ );
			float  g_fSpinX2 = 0.0f;
			float  g_fSpinY2 = 0.0f;
			D3DXMatrixRotationYawPitchRoll( &matRot2, 
				D3DXToRadian(g_fSpinX2), 
				D3DXToRadian(g_fSpinY2), 
				0.0f );
			matTemp2  = matScale2 * matTrans2;
			matWorld2 = matRot2   * matTemp2;
			SMG->RenderQuad( textureID, matWorld2 );
		}

		void cGameScreenTrack::RenderArrow( int textureID, float positionX, float positionY, float positionZ )
		{
			D3DXMATRIX matTemp2;

			D3DXMATRIX matTrans2;
			D3DXMATRIX matRot2;
			D3DXMATRIX matScale2;
			D3DXMATRIX matWorld2;
			D3DXMatrixScaling(&matScale2, 1.0f, 1.0f, 1.0f);

			D3DXMatrixTranslation( &matTrans2, positionX, positionY, positionZ );
			float  g_fSpinX2 = 0.0f;
			float  g_fSpinY2 = 0.0f;
			D3DXMatrixRotationYawPitchRoll( &matRot2, 
				D3DXToRadian(g_fSpinX2), 
				D3DXToRadian(g_fSpinY2), 
				0.0f );
			matTemp2  = matScale2 * matTrans2;
			matWorld2 = matRot2   * matTemp2;
			SMG->RenderQuad( textureID, matWorld2 );
		}

		void cGameScreenTrack::RenderPadLock( int textureID, float positionX, float positionY, float positionZ )
		{
			D3DXMATRIX matTemp2;

			D3DXMATRIX matTrans2;
			D3DXMATRIX matRot2;
			D3DXMATRIX matScale2;
			D3DXMATRIX matWorld2;
			D3DXMatrixScaling(&matScale2, 1.0f, 1.0f, 1.0f);

			D3DXMatrixTranslation( &matTrans2, positionX, positionY, positionZ );
			float  g_fSpinX2 = 0.0f;
			float  g_fSpinY2 = 0.0f;
			D3DXMatrixRotationYawPitchRoll( &matRot2, 
				D3DXToRadian(g_fSpinX2), 
				D3DXToRadian(g_fSpinY2), 
				0.0f );
			matTemp2  = matScale2 * matTrans2;
			matWorld2 = matRot2   * matTemp2;
			SMG->RenderQuad( textureID, matWorld2 );
		}

	} // Namespace Components
} // Namespace Flex