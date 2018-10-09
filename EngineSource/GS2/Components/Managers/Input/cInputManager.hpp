//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cInputManager.hpp
// Description: 
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#ifndef __FLEX_COMPONENTS_MANAGERS_INPUT_CINPUTMANAGER_HPP__
#define __FLEX_COMPONENTS_MANAGERS_INPUT_CINPUTMANAGER_HPP__

#include "precom.h"
#include "InputAction.hpp"
#include "../../../Common/Defines.hpp"

namespace flex
{
	namespace components
	{
		struct CONTROLER_STATE
		{
			XINPUT_STATE state;
			bool bConnected;
		};

		class cInputManager
		{
		public:
			static cInputManager& Instance()
			{
				assert( m_pInstance );
				return *m_pInstance;
			}
			static cInputManager* InstancePtr()
			{
				return m_pInstance;
			}
			static void Create()
			{
				if (!m_pInstance)
					m_pInstance = new cInputManager;
			}
			static void Delete()
			{
				delete m_pInstance;
				m_pInstance = 0;
			}

		private:
			cInputManager(void);
			cInputManager(cInputManager const&); // copy ctor hidden
			//cInputManager& operator=(cInputManager const&); // assign op. hidden
			~cInputManager(void);

		protected:
			static cInputManager* m_pInstance;

		public:
			bool Initialise( void );
			void Update    ( void );

		public:
			void UpdateWindowsInput ( UINT bufferSize, BYTE *buffer );
			void UpdateKeyboardInput( void );
			void UpdateXInput       ( void );

		private:
			CONTROLER_STATE                 m_Controllers[MAX_CONTROLLERS];
			WCHAR                           m_szMessage[4][1024];
			flex::components::sInputState*  m_ActionState;
			bool                            m_DeadZoneOn;


		};
	} // Namespace Components
} // Namespace Flex

#define IMG flex::components::cInputManager::InstancePtr()

#endif

