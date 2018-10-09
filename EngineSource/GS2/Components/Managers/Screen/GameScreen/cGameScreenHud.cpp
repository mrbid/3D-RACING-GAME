//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cGameScreenHud.cpp
// Description: 
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#include "precom.h"
#include "cGameScreenHud.hpp"
#include "../cScreenManager.hpp"
#include "MilliTimer.h"
#include "GameWorld.h"

namespace flex
{
	namespace components
	{
		cGameScreenHud::cGameScreenHud( void ) : Texture2ScaleX(1.0f), Texture2ScaleY(1.0f), Texture2ScaleZ(1.0f), NeedleRotation(0.0f)
		{
			m_TextureIDSpeedo = SMG->AddQuad("Data\\Textures\\Hud\\Speedo.png", 234, 234);
			m_TextureIDNeedle = SMG->AddQuad("Data\\Textures\\Hud\\Needle.png",  58, 178);

			m_TimeLast  = GetTime();
		}

		cGameScreenHud::~cGameScreenHud( void )
		{
		}

		void cGameScreenHud::Render( void )
		{


			RenderSpeedo();
			RenderNeedle();
		}

		void cGameScreenHud::Update( const float& dt )
		{
			//get game speed
			int testspeed = fabs(GameWorld().GetVehicleController()->GetVehicle(0)->GetSpeedKPH() * 0.2f);
			NeedleRotation = SPEEDOOFFSET + (-testspeed * SPEEDOSCALEFACTOR);
		}

		void cGameScreenHud::Messages(sInputState* wButtons)
		{

		}

		void cGameScreenHud::Refresh( void )
		{
			m_TimeLast = GetTime();
		}

		void cGameScreenHud::RenderSpeedo( void )
		{
			D3DXMATRIX matTrans;
			D3DXMATRIX matRot;
			D3DXMATRIX matWorld;

			D3DXMatrixTranslation( &matTrans, 5.42f, -2.62f, 13.5f );
			//D3DXMatrixTranslation( &matTrans, 0.0f, 0.0f, 1.1f );
			float  g_fSpinX = 0.0f;
			float  g_fSpinY = 0.0f;
			D3DXMatrixRotationYawPitchRoll( &matRot, 
				D3DXToRadian(g_fSpinX), 
				D3DXToRadian(g_fSpinY), 
				0.0f );
			matWorld = matRot * matTrans;
			SMG->RenderQuad(m_TextureIDSpeedo, matWorld);
		}

		void cGameScreenHud::RenderNeedle( void )
		{
			D3DXMATRIX matTemp2;

			D3DXMATRIX matTrans2;
			D3DXMATRIX matRot2;
			D3DXMATRIX matScale2;
			D3DXMATRIX matWorld2;
			D3DXMatrixScaling(&matScale2, Texture2ScaleX, Texture2ScaleY, Texture2ScaleZ);

			D3DXMatrixTranslation( &matTrans2, 5.42f, -2.62f, 13.4f );
			float  g_fSpinX2 = 0.0f;
			float  g_fSpinY2 = 0.0f;
			D3DXMatrixRotationYawPitchRoll( &matRot2, 
				D3DXToRadian(g_fSpinX2), 
				D3DXToRadian(g_fSpinY2), 
				D3DXToRadian(NeedleRotation) );
			matTemp2  = matScale2 * matTrans2;
			matWorld2 = matRot2   * matTemp2;
			SMG->RenderQuad(m_TextureIDNeedle, matWorld2);
		}
	} // Namespace Components
} // Namespace Flex