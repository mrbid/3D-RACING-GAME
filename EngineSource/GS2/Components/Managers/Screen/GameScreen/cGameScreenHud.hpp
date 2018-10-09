//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cGameScreenHud.hpp
// Description: Generic Screen Management System
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#ifndef __FLEX_COMPONENTS_CGAMESCREENHUD_HPP__
#define __FLEX_COMPONENTS_CGAMESCREENHUD_HPP__

#include "precom.h"
#include "IGameScreen.hpp"
#include "../../Input/InputAction.hpp"

#define SPEEDOOFFSET 155
#define SPEEDOSCALEFACTOR 1.3

namespace flex
{
	namespace components
	{
		class cGameScreenHud : public IGameScreen
		{
		public:
			cGameScreenHud( void );
			~cGameScreenHud( void );
			void Render( void );
			void Update( const float& dt );
			void Messages( sInputState* wButtons );
			void Refresh( void );

			void RenderSpeedo( void );
			void RenderNeedle( void );

			int m_TextureIDSpeedo;
			int m_TextureIDNeedle;
			int m_TextureIDtest;

			float Texture2ScaleX;
			float Texture2ScaleY;
			float Texture2ScaleZ;

			float NeedleRotation;

			float m_TimeLast;
		};

	} // Namespace Components
} // Namespace Flex

#endif
