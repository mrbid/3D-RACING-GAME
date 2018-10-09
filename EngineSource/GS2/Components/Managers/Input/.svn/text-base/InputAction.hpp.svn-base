//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: InputAction.hpp
// Description: 
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 12 - 11 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#ifndef __FLEX_COMPONENTS_MANAGERS_INPUT_HPP__
#define __FLEX_COMPONENTS_MANAGERS_INPUT_HPP__

#include "precom.h"

namespace flex
{
	namespace components
	{
		enum EDPadState
		{
			eDirection,
			eDirectionN,
			eDirectionNE,
			eDirectionE,
			eDirectionSE,
			eDirectionS,
			eDirectionSW,
			eDirectionW,
			eDirectionNW
		};

		struct ArrowKeys
		{
			bool m_ButtonLeft;
			bool m_ButtonRight;
			bool m_ButtonUp;
			bool m_ButtonDown;
		};

		struct sInputState 
		{
			bool            m_Controller;


			bool            m_Start;
			bool            m_Back;

			bool            m_BUMPERLEFT;
			bool            m_BUMPERRIGHT;

			bool            m_ButtonA;
			bool            m_ButtonB;
			bool            m_ButtonX;
			bool            m_ButtonY;

			float           m_TRIGGERLEFT;
			float           m_TRIGGERRIGHT;
			float           m_THUMBLEFTX;
			float           m_THUMBLEFTY;
			float           m_THUMBRIGHTX;
			float           m_THUMBRIGHTY;

			ArrowKeys       m_ArrowKeys;

			EDPadState      m_DPad;

			bool            m_DEBUGF1;
			bool            m_DEBUGF2;
			bool            m_DEBUGF3;
			bool            m_DEBUGF4;
			bool            m_DEBUGF5;
			bool            m_DEBUGF6;
		};
	} // Namespace Components
} // Namespace Flex

#endif

