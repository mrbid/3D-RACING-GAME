//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cScreenManager.hpp
// Description: Generic Screen Management System
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#ifndef __FLEX_COMPONENTS_IGAMESCREEN_HPP__
#define __FLEX_COMPONENTS_IGAMESCREEN_HPP__

#include "precom.h"
#include "../../Input/InputAction.hpp"

namespace flex
{
	namespace components
	{
		class IGameScreen
		{
		public:
			IGameScreen(void);
			~IGameScreen(void);
			virtual void Render(void) = 0;
			virtual void Update( const float& dt ) = 0;
			virtual void Messages(sInputState* wButtons) = 0;
			virtual void Refresh(void) = 0;
		};

	} // Namespace Components
} // Namespace Flex

#endif
