//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cGameScreenController.cpp
// Description: 
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#include "precom.h"
#include "cGameScreenController.hpp"
#include "../cScreenManager.hpp"
#include "MilliTimer.h"

namespace flex
{
	namespace components
	{
		cGameScreenController::cGameScreenController( void ) : Texture1ScaleX(6.4f), Texture1ScaleY(6.4f), Texture1ScaleZ(1.0f)
		{
			m_TextureID1 = SMG->AddQuad("Data\\Textures\\Controller.png", 1280, 720);
			m_TimeLast = GetTime();
		}

		cGameScreenController::~cGameScreenController( void )
		{
		}

		void cGameScreenController::Render( void )
		{
			//SMG->RenderSprite(m_TextureID1, -1280/2, 720/2, 0, 1280/2, 720/2, 0);
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
		}

		void cGameScreenController::Update( const float& dt )
		{

		}

		void cGameScreenController::Messages(sInputState* wButtons)
		{
			if(m_TimeLast + 100 < GetTime())
			{
				if(wButtons->m_Start)
				{
					SMG->PopScreen();
				}
			}
		}

		void cGameScreenController::Refresh( void )
		{
			m_TimeLast = GetTime();
		}
	} // Namespace Components
} // Namespace Flex