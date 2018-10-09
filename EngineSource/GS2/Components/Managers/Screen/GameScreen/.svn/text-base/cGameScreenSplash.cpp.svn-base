//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cGamesScreenSplash.cpp
// Description: 
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#include "precom.h"
#include "cGameScreenSplash.hpp"
#include "../cScreenManager.hpp"
#include "MilliTimer.h"

namespace flex
{
	namespace components
	{
		cGameScreenSplash::cGameScreenSplash( void ) : Texture1ScaleX(6.4f), Texture1ScaleY(6.4f), Texture1ScaleZ(1.0f), Texture2ScaleX(1.0f), Texture2ScaleY(1.0f), Texture2ScaleZ(1.0f), ButtonStartZoom(1.0f), Shrink(false)
		{
			m_TextureID1 = SMG->AddQuad("Data\\Textures\\Splashscreen.png", 1280, 720);
			m_TextureID2 = SMG->AddQuad("Data\\Textures\\ButtonStart.png", 250, 100);
			m_TimeLast = GetTime();
		}

		cGameScreenSplash::~cGameScreenSplash( void )
		{
		}

		void cGameScreenSplash::Render( void )
		{
			D3DXMATRIX matTemp1;

			D3DXMATRIX matTrans1;
			D3DXMATRIX matRot1;
			D3DXMATRIX matScale1;
			D3DXMATRIX matWorld1;
			

			D3DXMatrixScaling(&matScale1, Texture1ScaleX, Texture1ScaleY, Texture1ScaleZ);

			D3DXMatrixTranslation( &matTrans1, 0.0f, 0.0f, 13.5f );
			float  g_fSpinX1 = 0.0f;
			float  g_fSpinY1 = 0.0f;
			D3DXMatrixRotationYawPitchRoll( &matRot1, 
				D3DXToRadian(g_fSpinX1), 
				D3DXToRadian(g_fSpinY1), 
				0.0f );
			matTemp1  = matScale1 * matTrans1;
			matWorld1 = matRot1   * matTemp1;
			SMG->RenderQuad(m_TextureID1, matWorld1);


			D3DXMATRIX matTemp2;

			D3DXMATRIX matTrans2;
			D3DXMATRIX matRot2;
			D3DXMATRIX matScale2;
			D3DXMATRIX matWorld2;
			D3DXMatrixScaling(&matScale2, Texture2ScaleX + ButtonStartZoom, Texture2ScaleY + ButtonStartZoom, Texture2ScaleZ);

			D3DXMatrixTranslation( &matTrans2, 0.0f, 0.0f, 13.4f );
			float  g_fSpinX2 = 0.0f;
			float  g_fSpinY2 = 0.0f;
			D3DXMatrixRotationYawPitchRoll( &matRot2, 
				D3DXToRadian(g_fSpinX2), 
				D3DXToRadian(g_fSpinY2), 
				0.0f );
			matTemp2  = matScale2 * matTrans2;
			matWorld2 = matRot2   * matTemp2;
			SMG->RenderQuad(m_TextureID2, matWorld2);


		}

		void cGameScreenSplash::Update( const float& dt )
		{
			if(m_TimeLast + 100 < GetTime())
			{
				if(Shrink)
				{
					ButtonStartZoom -= 0.01;
					if(ButtonStartZoom < 1.0f - 0.20f)
					{
						Shrink = false;
					}
				}
				else
				{
					ButtonStartZoom += 0.01;
					if(ButtonStartZoom > 1.0f + 0.20f)
					{
						Shrink = true;
					}
				}
			}
		}

		void cGameScreenSplash::Messages(sInputState* wButtons)
		{
			if(wButtons->m_Start)
			{
				SMG->PopScreen();
			}
			//switch(*wButtons)
			//{
			//case XINPUT_GAMEPAD_A:
			//	{
			//		SMG->PopScreen();
			//		break;
			//	}
			//}
		}

		void cGameScreenSplash::Refresh( void )
		{
			m_TimeLast = GetTime();
		}
	} // Namespace Components
} // Namespace Flex