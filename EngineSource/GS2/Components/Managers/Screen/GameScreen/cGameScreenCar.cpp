//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cGameScreenCar.cpp
// Description: 
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#include "precom.h"
#include "cGameScreenCar.hpp"
#include "../cScreenManager.hpp"
#include "MilliTimer.h"
#include "GameWorld.h"

namespace flex
{
	namespace components
	{
		cGameScreenCar::cGameScreenCar( void ) : m_TextureBackgroundScaleX(1.0f), m_TextureBackgroundScaleY(1.0f), m_TextureBackgroundScaleZ(1.0f)
		{
			m_TextureBackground = SMG->AddQuad("Data\\Textures\\ScreenBackground.png", 1280, 720);
			//m_TextureIDNeedle = SMG->AddQuad("Data\\Textures\\Hud\\Needle.png",  58, 178);

			m_TextureCar_1_1 = SMG->AddQuad("Data\\Textures\\Cars\\AudiS3.png", 500, 500);

			m_TextureCar_2_1 = SMG->AddQuad("Data\\Textures\\Cars\\Clio.png", 500, 500);

			m_TextureCar_3_1 = SMG->AddQuad("Data\\Textures\\Cars\\Focus_blue.png", 500, 500);
			m_TextureCar_3_2 = SMG->AddQuad("Data\\Textures\\Cars\\Focus_white.png", 500, 500);

			m_TextureCar_4_1 = SMG->AddQuad("Data\\Textures\\Cars\\Gallardo_green.png", 500, 500);
			m_TextureCar_4_2 = SMG->AddQuad("Data\\Textures\\Cars\\Gallardo_grey.png", 500, 500);
			m_TextureCar_4_3 = SMG->AddQuad("Data\\Textures\\Cars\\Gallardo_orange.png", 500, 500);
			m_TextureCar_4_4 = SMG->AddQuad("Data\\Textures\\Cars\\Gallardo_purple.png", 500, 500);
			m_TextureCar_4_5 = SMG->AddQuad("Data\\Textures\\Cars\\Gallardo_white.png", 500, 500);
			m_TextureCar_4_6 = SMG->AddQuad("Data\\Textures\\Cars\\Gallardo_yellow.png", 500, 500);

			m_TextureCar_5_1 = SMG->AddQuad("Data\\Textures\\Cars\\GolfGTI.png", 500, 500);

			m_TextureCar_6_1 = SMG->AddQuad("Data\\Textures\\Cars\\hotrod.png", 500, 500);

			m_TextureCar_7_1 = SMG->AddQuad("Data\\Textures\\Cars\\murc.png", 500, 500);

			m_TextureCar_8_1 = SMG->AddQuad("Data\\Textures\\Cars\\rx8.png", 500, 500);

			m_TextureCar_9_1 = SMG->AddQuad("Data\\Textures\\Cars\\smart_batman.png", 500, 500);
			m_TextureCar_9_2 = SMG->AddQuad("Data\\Textures\\Cars\\smart_greg.png", 500, 500);
			m_TextureCar_9_3 = SMG->AddQuad("Data\\Textures\\Cars\\smart_hulk.png", 500, 500);
			m_TextureCar_9_4 = SMG->AddQuad("Data\\Textures\\Cars\\smart_ironman.png", 500, 500);
			m_TextureCar_9_5 = SMG->AddQuad("Data\\Textures\\Cars\\smart_jackbauer.png", 500, 500);
			m_TextureCar_9_6 = SMG->AddQuad("Data\\Textures\\Cars\\smart_spiderman.png", 500, 500);
			m_TextureCar_9_7 = SMG->AddQuad("Data\\Textures\\Cars\\smart_superman.png", 500, 500);
			m_TextureCar_9_8 = SMG->AddQuad("Data\\Textures\\Cars\\smart_wolverine.png", 500, 500);

			m_TextureCar_10_1 = SMG->AddQuad("Data\\Textures\\Cars\\viper_black.png", 500, 500);
			m_TextureCar_10_2 = SMG->AddQuad("Data\\Textures\\Cars\\viper_blue.png", 500, 500);
			m_TextureCar_10_3 = SMG->AddQuad("Data\\Textures\\Cars\\viper_green.png", 500, 500);
			m_TextureCar_10_4 = SMG->AddQuad("Data\\Textures\\Cars\\viper_red.png", 500, 500);
			m_TextureCar_10_5 = SMG->AddQuad("Data\\Textures\\Cars\\viper_white.png", 500, 500);
			m_TextureCar_10_6 = SMG->AddQuad("Data\\Textures\\Cars\\viper_yellow.png", 500, 500);

			m_TextureCar_11_1 = SMG->AddQuad("Data\\Textures\\Cars\\x-6_black.png", 500, 500);
			m_TextureCar_11_2 = SMG->AddQuad("Data\\Textures\\Cars\\x-6_blue.png", 500, 500);
			m_TextureCar_11_3 = SMG->AddQuad("Data\\Textures\\Cars\\x-6_green.png", 500, 500);
			m_TextureCar_11_4 = SMG->AddQuad("Data\\Textures\\Cars\\x-6_red.png", 500, 500);
			m_TextureCar_11_5 = SMG->AddQuad("Data\\Textures\\Cars\\x-6_white.png", 500, 500);

			m_TextureCar_12_1 = SMG->AddQuad("Data\\Textures\\Cars\\350z_blue.png", 500, 500);
			m_TextureCar_12_2 = SMG->AddQuad("Data\\Textures\\Cars\\350z_green.png", 500, 500);
			m_TextureCar_12_3 = SMG->AddQuad("Data\\Textures\\Cars\\350z_orange.png", 500, 500);
			m_TextureCar_12_4 = SMG->AddQuad("Data\\Textures\\Cars\\350z_purple.png", 500, 500);
			m_TextureCar_12_5 = SMG->AddQuad("Data\\Textures\\Cars\\350z_red.png", 500, 500);
			m_TextureCar_12_6 = SMG->AddQuad("Data\\Textures\\Cars\\350z_white.png", 500, 500);
			m_TextureCar_12_7 = SMG->AddQuad("Data\\Textures\\Cars\\350z_yellow.png", 500, 500);
			
			m_TimeLast  = GetTime();
		}

		cGameScreenCar::~cGameScreenCar( void )
		{
		}

		void cGameScreenCar::Render( void )
		{
			RenderBackground();

			//RenderSpeedo();
			//RenderNeedle();
		}

		void cGameScreenCar::Update( const float& dt )
		{

		}

		void cGameScreenCar::Messages(sInputState* wButtons)
		{
			if(m_TimeLast + 250 < GetTime())
			{
				if(wButtons->m_THUMBLEFTX >  0.5 || wButtons->m_ArrowKeys.m_ButtonLeft == true)
				{
					if(currentSelectionX > 0 && currentSelectionX <= 4)
					{
						currentSelectionX--;
						m_TimeLast = GetTime();
					}
				}
				if(wButtons->m_THUMBLEFTX < -0.5 || wButtons->m_ArrowKeys.m_ButtonRight == true)
				{
					if(currentSelectionX >= 0 && currentSelectionX < 4)
					{
						currentSelectionX++;
						m_TimeLast = GetTime();
					}
				}
				if(wButtons->m_THUMBLEFTY >  0.5 || wButtons->m_ArrowKeys.m_ButtonUp == true)
				{
					if(currentSelectionY > 0 && currentSelectionY <= 4)
					{
						currentSelectionY--;
						m_TimeLast = GetTime();
					}
				}
				if(wButtons->m_THUMBLEFTY < -0.5 || wButtons->m_ArrowKeys.m_ButtonDown == true)
				{
					if(currentSelectionY >= 0 && currentSelectionY < 4)
					{
						currentSelectionY++;
						m_TimeLast = GetTime();
					}
				}
				if(wButtons->m_ButtonA == true || wButtons->m_Start == true)
				{
					//if(currentSelection == 0)
					//{
					//	SMG->SetTrack( 0 );
					//	SMG->PopScreen();
					//}
					//else if(currentSelection == 1)
					//{
					//	SMG->SetTrack( 0 );
					//	SMG->PopScreen();
					//}
				}
			}
		}

		void cGameScreenCar::Refresh( void )
		{
			m_TimeLast = GetTime();
		}

		void cGameScreenCar::RenderBackground( void )
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

		void cGameScreenCar::RenderSpeedo( void )
		{
			//D3DXMATRIX matTrans;
			//D3DXMATRIX matRot;
			//D3DXMATRIX matWorld;

			//D3DXMatrixTranslation( &matTrans, 5.42f, -2.62f, 13.5f );
			////D3DXMatrixTranslation( &matTrans, 0.0f, 0.0f, 1.1f );
			//float  g_fSpinX = 0.0f;
			//float  g_fSpinY = 0.0f;
			//D3DXMatrixRotationYawPitchRoll( &matRot, 
			//	D3DXToRadian(g_fSpinX), 
			//	D3DXToRadian(g_fSpinY), 
			//	0.0f );
			//matWorld = matRot * matTrans;
			//SMG->RenderQuad(m_TextureIDSpeedo, matWorld);
		}

		void cGameScreenCar::RenderNeedle( void )
		{
			//D3DXMATRIX matTemp2;

			//D3DXMATRIX matTrans2;
			//D3DXMATRIX matRot2;
			//D3DXMATRIX matScale2;
			//D3DXMATRIX matWorld2;
			//D3DXMatrixScaling(&matScale2, Texture2ScaleX, Texture2ScaleY, Texture2ScaleZ);

			//D3DXMatrixTranslation( &matTrans2, 5.42f, -2.62f, 13.4f );
			//float  g_fSpinX2 = 0.0f;
			//float  g_fSpinY2 = 0.0f;
			//D3DXMatrixRotationYawPitchRoll( &matRot2, 
			//	D3DXToRadian(g_fSpinX2), 
			//	D3DXToRadian(g_fSpinY2), 
			//	D3DXToRadian(NeedleRotation) );
			//matTemp2  = matScale2 * matTrans2;
			//matWorld2 = matRot2   * matTemp2;
			//SMG->RenderQuad(m_TextureIDNeedle, matWorld2);
		}
	} // Namespace Components
} // Namespace Flex