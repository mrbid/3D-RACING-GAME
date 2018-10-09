//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cGamesScreenSplash.hpp
// Description: Generic Screen Management System
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#ifndef __FLEX_COMPONENTS_CGAMESCREENSPLASH_HPP__
#define __FLEX_COMPONENTS_CGAMESCREENSPLASH_HPP__

#include "precom.h"
#include "IGameScreen.hpp"
#include "../../Input/InputAction.hpp"

namespace flex
{
	namespace components
	{
		class cGameScreenSplash : public IGameScreen
		{
		public:
			cGameScreenSplash(void);
			~cGameScreenSplash(void);
			void Render(void);
			void Update( const float& dt );
			void Messages(sInputState* wButtons);
			void Refresh( void );

			int m_TextureID1;

			float Texture1ScaleX;
			float Texture1ScaleY;
			float Texture1ScaleZ;

			float m_TimeLast;
			float ButtonStartZoom;
			int   m_TextureID2;

			float Texture2ScaleX;
			float Texture2ScaleY;
			float Texture2ScaleZ;

			bool Shrink;
		};

	} // Namespace Components
} // Namespace Flex

#endif
