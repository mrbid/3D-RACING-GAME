//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cGameScreenCarBasic.cpp
// Description: 
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#include "precom.h"
#include "cGameScreenCarBasic.hpp"
#include "../cScreenManager.hpp"
#include "MilliTimer.h"
#include "GameWorld.h"

namespace flex
{
	namespace components
	{
		cGameScreenCarBasic::cGameScreenCarBasic( void ) : m_TextureBackgroundScaleX(6.4f), m_TextureBackgroundScaleY(6.4f), m_TextureBackgroundScaleZ(1.0f), currentSelection(1), m_TrackScaleX(2.0f), m_TrackScaleY(2.0f), m_TrackScaleZ(1.0f)
		{
			m_TextureBackground = SMG->AddQuad("Data\\Textures\\ScreenBackground.png", 1280, 720);
			//trackMap = new std::map<std::string, int>;

			m_TextureTrack1 = SMG->AddQuad("Data\\Textures\\Cars\\AudiS3.png", 500, 500);
			m_TextureTrack2 = SMG->AddQuad("Data\\Textures\\Cars\\Clio.png",  500, 500);
			m_TextureTrack3 = SMG->AddQuad("Data\\Textures\\Cars\\Focus_blue.png", 500, 500);
			m_TextureTrack4 = SMG->AddQuad("Data\\Textures\\Cars\\Gallardo_green.png", 500, 500);
			m_TextureTrack5 = SMG->AddQuad("Data\\Textures\\Cars\\GolfGTI.png", 500, 500);
			m_TextureTrack6 = SMG->AddQuad("Data\\Textures\\Cars\\hotrod.png", 500, 500);
			m_TextureTrack7 = SMG->AddQuad("Data\\Textures\\Cars\\murc.png", 500, 500);
			m_TextureTrack8 = SMG->AddQuad("Data\\Textures\\Cars\\rx8.png", 500, 500);
			m_TextureTrack9 = SMG->AddQuad("Data\\Textures\\Cars\\smart_batman.png", 500, 500);
			m_TextureTrack10 = SMG->AddQuad("Data\\Textures\\Cars\\viper_black.png", 500, 500);
			m_TextureTrack11 = SMG->AddQuad("Data\\Textures\\Cars\\x-6_black.png", 500, 500);
			m_TextureTrack12 = SMG->AddQuad("Data\\Textures\\Cars\\350z_blue.png", 500, 500);

			m_TexturePadlock = SMG->AddQuad("Data\\Textures\\Buttons\\padlock.png", 722, 665);

			m_TextureLeft  = SMG->AddQuad("Data\\Textures\\Buttons\\Left.png",  200, 100);
			m_TextureRight = SMG->AddQuad("Data\\Textures\\Buttons\\Right.png", 200, 100);

			m_TimeLast  = GetTime();
		}

		cGameScreenCarBasic::~cGameScreenCarBasic( void )
		{
		}

		void cGameScreenCarBasic::Render( void )
		{
			RenderBackground();
			RenderTracks();
		}

		void cGameScreenCarBasic::Update( const float& dt )
		{

		}

		void cGameScreenCarBasic::Messages(sInputState* wButtons)
		{
			if(m_TimeLast + 250 < GetTime())
			{
				if(wButtons->m_THUMBLEFTX >  0.5 || wButtons->m_ArrowKeys.m_ButtonLeft == true)
				{
					if(currentSelection > 0 && currentSelection <= 11)
					{
						currentSelection--;
						m_TimeLast = GetTime();
					}
				}
				if(wButtons->m_THUMBLEFTX < -0.5 || wButtons->m_ArrowKeys.m_ButtonRight == true)
				{
					if(currentSelection >= 0 && currentSelection < 11)
					{
						currentSelection++;
						m_TimeLast = GetTime();
					}
				}
				if(wButtons->m_ButtonA == true || wButtons->m_Start == true)
				{
					if(currentSelection >= 0 && currentSelection <= 10)
					{
						SMG->SetCar( currentSelection );
						SMG->PopScreen();
					}
				}
			}
		}

		void cGameScreenCarBasic::Refresh( void )
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

		void cGameScreenCarBasic::RenderBackground( void )
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

		void cGameScreenCarBasic::RenderTracks( void )
		{
			if(currentSelection == 0)
			{
				RenderTrackSample( m_TextureTrack1,   0.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack2,  -4.0f, 0.0f, 13.4f);
			}
			else if(currentSelection == 1)
			{
				RenderTrackSample( m_TextureTrack1,  4.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack2,  0.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack3, -4.0f, 0.0f, 13.4f);

				RenderArrow(m_TextureLeft, -5.0f, 3.0f, 13.4f);
				RenderArrow(m_TextureRight, 5.0f, 3.0f, 13.4f);
			}
			else if(currentSelection == 2)
			{
				RenderTrackSample( m_TextureTrack2,  4.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack3,  0.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack4, -4.0f, 0.0f, 13.4f);

				RenderArrow(m_TextureLeft, -5.0f, 3.0f, 13.4f);
				RenderArrow(m_TextureRight, 5.0f, 3.0f, 13.4f);

			}
			else if(currentSelection == 3)
			{
				RenderTrackSample( m_TextureTrack3,  4.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack4,  0.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack5, -4.0f, 0.0f, 13.4f);

				RenderArrow(m_TextureLeft, -5.0f, 3.0f, 13.4f);
				RenderArrow(m_TextureRight, 5.0f, 3.0f, 13.4f);
			}
			else if(currentSelection == 4)
			{
				RenderTrackSample( m_TextureTrack4,  4.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack5,  0.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack6, -4.0f, 0.0f, 13.4f);

				RenderArrow(m_TextureLeft, -5.0f, 3.0f, 13.4f);
				RenderArrow(m_TextureRight, 5.0f, 3.0f, 13.4f);
			}
			else if(currentSelection == 5)
			{
				RenderTrackSample( m_TextureTrack5,  4.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack6,  0.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack7, -4.0f, 0.0f, 13.4f);

				RenderArrow(m_TextureLeft, -5.0f, 3.0f, 13.4f);
				RenderArrow(m_TextureRight, 5.0f, 3.0f, 13.4f);
			}
			else if(currentSelection == 6)
			{
				RenderTrackSample( m_TextureTrack6,  4.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack7,  0.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack8, -4.0f, 0.0f, 13.4f);

				RenderArrow(m_TextureLeft, -5.0f, 3.0f, 13.4f);
				RenderArrow(m_TextureRight, 5.0f, 3.0f, 13.4f);
			}
			else if(currentSelection == 7)
			{
				RenderTrackSample( m_TextureTrack7,  4.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack8,  0.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack9, -4.0f, 0.0f, 13.4f);

				RenderArrow(m_TextureLeft, -5.0f, 3.0f, 13.4f);
				RenderArrow(m_TextureRight, 5.0f, 3.0f, 13.4f);
			}
			else if(currentSelection == 8)
			{
				RenderTrackSample( m_TextureTrack8,  4.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack9,  0.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack10, -4.0f, 0.0f, 13.4f);

				RenderArrow(m_TextureLeft, -5.0f, 3.0f, 13.4f);
				RenderArrow(m_TextureRight, 5.0f, 3.0f, 13.4f);

			}
			else if(currentSelection == 9)
			{
				RenderTrackSample( m_TextureTrack9,  4.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack10,  0.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack11, -4.0f, 0.0f, 13.4f);

				RenderArrow(m_TextureLeft, -5.0f, 3.0f, 13.4f);
				RenderArrow(m_TextureRight, 5.0f, 3.0f, 13.4f);
			}
			else if(currentSelection == 10)
			{
				RenderTrackSample( m_TextureTrack10,  4.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack11,  0.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack12, -4.0f, 0.0f, 13.4f);

				RenderArrow(m_TextureLeft, -5.0f, 3.0f, 13.4f);
				RenderArrow(m_TextureRight, 5.0f, 3.0f, 13.4f);

				RenderPadLock(m_TexturePadlock, -5.0f, 0.0f, 13.4f);
			}
			else if(currentSelection == 11)
			{
				RenderTrackSample( m_TextureTrack11,  4.0f, 0.0f, 13.4f);
				RenderTrackSample( m_TextureTrack12,  0.0f, 0.0f, 13.4f);

				RenderArrow(m_TextureLeft, -5.0f, 3.0f, 13.4f);
				RenderArrow(m_TextureRight, 5.0f, 3.0f, 13.4f);

				RenderPadLock(m_TexturePadlock, 0.0f, 0.0f, 13.4f);
			}
		}

		void cGameScreenCarBasic::RenderTrackSample( int textureID, float positionX, float positionY, float positionZ )
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

		void cGameScreenCarBasic::RenderArrow( int textureID, float positionX, float positionY, float positionZ )
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

		void cGameScreenCarBasic::RenderPadLock( int textureID, float positionX, float positionY, float positionZ )
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