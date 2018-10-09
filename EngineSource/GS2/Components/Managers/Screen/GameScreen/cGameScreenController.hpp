//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cGameScreenController.hpp
// Description: Generic Screen Management System
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#ifndef __FLEX_COMPONENTS_CGAMESCREENCONTROLLER_HPP__
#define __FLEX_COMPONENTS_CGAMESCREENCONTROLLER_HPP__

#include "precom.h"
#include "IGameScreen.hpp"
#include "../../Input/InputAction.hpp"

namespace flex
{
	namespace components
	{
		class cGameScreenController : public IGameScreen
		{
		public:
			cGameScreenController(void);
			~cGameScreenController(void);
			void Render(void);
			void Update( const float& dt );
			void Messages(sInputState* wButtons);
			void Refresh( void );

			float m_TimeLast;

			int m_TextureID1;

			float Texture1ScaleX;
			float Texture1ScaleY;
			float Texture1ScaleZ;
		};

	} // Namespace Components
} // Namespace Flex

#endif
