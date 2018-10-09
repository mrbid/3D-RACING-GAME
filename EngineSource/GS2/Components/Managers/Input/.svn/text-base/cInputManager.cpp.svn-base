//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cInputManager.cpp
// Description: Generic Screen Management System
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#include "precom.h"
#include "cInputManager.hpp"
#include "../../Managers/Screen/cScreenManager.hpp"

namespace flex
{
	namespace components
	{
		cInputManager* cInputManager::m_pInstance = NULL;

		cInputManager::cInputManager(void)
		{
		}

		cInputManager::~cInputManager(void)
		{
		}

		bool cInputManager::Initialise( void )
		{
			m_ActionState = new flex::components::sInputState;
			ZeroMemory( m_ActionState, sizeof( sInputState ) * 1 );
			m_DeadZoneOn = true;
			return true;
		}

		void cInputManager::Update( void )
		{
			ZeroMemory( m_ActionState, sizeof( sInputState ) * 1 );

			UpdateKeyboardInput();
			UpdateXInput();

			//Send Input To Screen Manager
			SMG->Messages(m_ActionState);
		}

		void cInputManager::UpdateWindowsInput( UINT bufferSize, BYTE *buffer )
		{
			RAWINPUT *raw = (RAWINPUT*) buffer;
			if (raw->header.dwType== RIM_TYPEMOUSE)
			{
				// Get values from the mouse member (of type RAWMOUSE)
				long mx = raw->data.mouse.lLastX;
				long my = raw->data.mouse.lLastY;
			}
			if (raw->header.dwType== RIM_TYPEKEYBOARD)
			{
				// Get key value from the keyboard member (of type RAWKEYBOARD)
				USHORT keyCode=raw->data.keyboard.VKey;

				switch(keyCode)
				{
				case 'A':
					m_ActionState->m_ArrowKeys.m_ButtonLeft = true;
					break;
				case 'W':
					m_ActionState->m_ArrowKeys.m_ButtonUp = true;
					break;
				case 'S':
					m_ActionState->m_ArrowKeys.m_ButtonDown = true;
					break;
				case 'D':
					m_ActionState->m_ArrowKeys.m_ButtonRight = true;
					break;
				case 'B':
					m_ActionState->m_ButtonB = true;
					break;
				case VK_LEFT:	
					m_ActionState->m_ArrowKeys.m_ButtonLeft = true;
					break;
				case VK_RIGHT:
					m_ActionState->m_ArrowKeys.m_ButtonRight = true;
					break;
				case VK_UP:
					m_ActionState->m_ArrowKeys.m_ButtonUp = true;
					break;
				case VK_DOWN:
					m_ActionState->m_ArrowKeys.m_ButtonDown = true;
					break;
				case VK_F1:
					m_ActionState->m_DEBUGF1 = true;
					break;
				case VK_F2:
					m_ActionState->m_DEBUGF2 = true;
					break;
				case VK_F3:
					m_ActionState->m_DEBUGF3 = true;
					break;
				case VK_F4:
					m_ActionState->m_DEBUGF4 = true;
					break;
				case VK_F5:
					m_ActionState->m_DEBUGF5 = true;
					break;
				case VK_F6:
					m_ActionState->m_DEBUGF6 = true;
					break;
				case VK_SPACE:
					m_ActionState->m_ButtonA = true;
					break;
				case VK_RETURN:
					m_ActionState->m_Start   = true;
					break;
				case VK_ESCAPE:
					m_ActionState->m_Back    = true;
					break;
				}
			}
			//Send Input To Screen Manager
			SMG->Messages(m_ActionState);
		}

		void cInputManager::UpdateKeyboardInput( void )
		{
			if(GetAsyncKeyState(VkKeyScan('a'))&0x8000)
				m_ActionState->m_ArrowKeys.m_ButtonLeft = true;
			if(GetAsyncKeyState(VkKeyScan('w'))&0x8000)
				m_ActionState->m_ArrowKeys.m_ButtonUp = true;
			if(GetAsyncKeyState(VkKeyScan('s'))&0x8000)
				m_ActionState->m_ArrowKeys.m_ButtonDown = true;
			if(GetAsyncKeyState(VkKeyScan('d'))&0x8000)
				m_ActionState->m_ArrowKeys.m_ButtonRight = true;
			if(GetAsyncKeyState(VkKeyScan('b'))&0x8000)
				m_ActionState->m_ButtonB = true;
			if(GetAsyncKeyState(VkKeyScan('x'))&0x8000)
				m_ActionState->m_ButtonX = true;
			if(GetAsyncKeyState(VkKeyScan('y'))&0x8000)
				m_ActionState->m_ButtonY = true;
			if(GetAsyncKeyState(VK_LEFT)&0x8000)
				m_ActionState->m_ArrowKeys.m_ButtonLeft = true;
			if(GetAsyncKeyState(VK_RIGHT)&0x8000)
				m_ActionState->m_ArrowKeys.m_ButtonRight = true;
			if(GetAsyncKeyState(VK_UP)&0x8000)
				m_ActionState->m_ArrowKeys.m_ButtonUp = true;
			if(GetAsyncKeyState(VK_DOWN)&0x8000)
				m_ActionState->m_ArrowKeys.m_ButtonDown = true;
			if(GetAsyncKeyState(VK_F1)&0x8000)
				m_ActionState->m_DEBUGF1 = true;
			if(GetAsyncKeyState(VK_F2)&0x8000)
				m_ActionState->m_DEBUGF2 = true;
			if(GetAsyncKeyState(VK_F3)&0x8000)
				m_ActionState->m_DEBUGF3 = true;
			if(GetAsyncKeyState(VK_F4)&0x8000)
				m_ActionState->m_DEBUGF4 = true;
			if(GetAsyncKeyState(VK_F5)&0x8000)
				m_ActionState->m_DEBUGF5 = true;
			if(GetAsyncKeyState(VK_F6)&0x8000)
				m_ActionState->m_DEBUGF6 = true;
			if(GetAsyncKeyState(VK_SPACE)&0x8000)
				m_ActionState->m_ButtonA = true;
			if(GetAsyncKeyState(VK_RETURN)&0x8000)
				m_ActionState->m_Start   = true;
			if(GetAsyncKeyState(VK_ESCAPE)&0x8000)
				m_ActionState->m_Back    = true;
		}


		void cInputManager::UpdateXInput( void )
		{
			DWORD dwResult;
			for( DWORD i = 0; i < MAX_CONTROLLERS; i++ )
			{
				// Simply get the state of the controller from XInput.
				dwResult = XInputGetState( i, &m_Controllers[i].state );

				if( dwResult == ERROR_SUCCESS )
					m_Controllers[i].bConnected = true;
				else
					m_Controllers[i].bConnected = false;
			}

			for( DWORD i = 0; i < MAX_CONTROLLERS; i++ )
			{
				if( m_Controllers[i].bConnected )
				{
					WORD wButtons = m_Controllers[i].state.Gamepad.wButtons;
					m_ActionState->m_Controller = true;
					if( m_DeadZoneOn )
					{
						// Zero value if thumbsticks are within the dead zone 
						if( ( m_Controllers[i].state.Gamepad.sThumbLX < INPUT_DEADZONE &&
							m_Controllers[i].state.Gamepad.sThumbLX > -INPUT_DEADZONE ) &&
							( m_Controllers[i].state.Gamepad.sThumbLY < INPUT_DEADZONE &&
							m_Controllers[i].state.Gamepad.sThumbLY > -INPUT_DEADZONE ) )
						{
							m_Controllers[i].state.Gamepad.sThumbLX = 0;
							m_Controllers[i].state.Gamepad.sThumbLY = 0;
						}
						else
						{
							if(m_Controllers[i].state.Gamepad.sThumbLX > 0)
							{
								m_ActionState->m_THUMBLEFTX   = (float)((m_Controllers[i].state.Gamepad.sThumbLX / 32768.0f ) - 0.24) * 1.33;
							}
							else
							{
								m_ActionState->m_THUMBLEFTX   = (float)((m_Controllers[i].state.Gamepad.sThumbLX / 32768.0f ) + 0.24) * 1.33;
							}
							if(m_Controllers[i].state.Gamepad.sThumbLY > 0)
							{
								m_ActionState->m_THUMBLEFTY   = (float)((m_Controllers[i].state.Gamepad.sThumbLY / 32768.0f ) - 0.24) * 1.33;
							}
							else
							{
								m_ActionState->m_THUMBLEFTY   = (float)((m_Controllers[i].state.Gamepad.sThumbLY / 32768.0f ) + 0.24) * 1.33;
							}
						}

						if( ( m_Controllers[i].state.Gamepad.sThumbRX < INPUT_DEADZONE &&
							m_Controllers[i].state.Gamepad.sThumbRX > -INPUT_DEADZONE ) &&
							( m_Controllers[i].state.Gamepad.sThumbRY < INPUT_DEADZONE &&
							m_Controllers[i].state.Gamepad.sThumbRY > -INPUT_DEADZONE ) )
						{
							m_Controllers[i].state.Gamepad.sThumbRX = 0;
							m_Controllers[i].state.Gamepad.sThumbRY = 0;
						}
						else
						{
							if(m_Controllers[i].state.Gamepad.sThumbRX > 0)
							{
								m_ActionState->m_THUMBRIGHTX  = (float)((m_Controllers[i].state.Gamepad.sThumbRX / 32768.0f ) - 0.24) * 1.33;
							}
							else
							{
								m_ActionState->m_THUMBRIGHTX  = (float)((m_Controllers[i].state.Gamepad.sThumbRX / 32768.0f ) + 0.24) * 1.33;
							}
							if(m_Controllers[i].state.Gamepad.sThumbRY > 0)
							{
								m_ActionState->m_THUMBRIGHTY  = (float)((m_Controllers[i].state.Gamepad.sThumbRY / 32768.0f ) - 0.24) * 1.33;
							}
							else
							{
								m_ActionState->m_THUMBRIGHTY  = (float)((m_Controllers[i].state.Gamepad.sThumbRY / 32768.0f ) + 0.24) * 1.33;
							}
						}
					}
					else
					{
						m_ActionState->m_THUMBLEFTX   = (float)(m_Controllers[i].state.Gamepad.sThumbLX / 32768.0f );
						m_ActionState->m_THUMBLEFTY   = (float)(m_Controllers[i].state.Gamepad.sThumbLY / 32768.0f );
						m_ActionState->m_THUMBRIGHTX  = (float)(m_Controllers[i].state.Gamepad.sThumbRX / 32768.0f );
						m_ActionState->m_THUMBRIGHTY  = (float)(m_Controllers[i].state.Gamepad.sThumbRY / 32768.0f );
					}

					m_ActionState->m_TRIGGERLEFT  = (float)(m_Controllers[i].state.Gamepad.bLeftTrigger  /255.0f);
					m_ActionState->m_TRIGGERRIGHT = (float)(m_Controllers[i].state.Gamepad.bRightTrigger /255.0f);

					switch(wButtons)
					{
					case XINPUT_GAMEPAD_A:
						{
							m_ActionState->m_ButtonA = true;
							break;
						}
					case XINPUT_GAMEPAD_B:
						{
							m_ActionState->m_ButtonB = true;
							break;
						}
					case XINPUT_GAMEPAD_X:
						{
							m_ActionState->m_ButtonX = true;
							break;
						}
					case XINPUT_GAMEPAD_Y:
						{
							m_ActionState->m_ButtonY = true;
							break;
						}
					case XINPUT_GAMEPAD_LEFT_SHOULDER:
						{
							m_ActionState->m_BUMPERLEFT = true;
							break;
						}
					case XINPUT_GAMEPAD_RIGHT_SHOULDER:
						{
							m_ActionState->m_BUMPERRIGHT = true;
							break;
						}
					case XINPUT_GAMEPAD_DPAD_UP:
						{
							m_ActionState->m_DPad = eDirectionN;
							break;
						}
					case XINPUT_GAMEPAD_DPAD_DOWN:
						{
							m_ActionState->m_DPad = eDirectionS;
							break;
						}
					case XINPUT_GAMEPAD_DPAD_LEFT:
						{
							m_ActionState->m_DPad = eDirectionW;
							break;
						}
					case XINPUT_GAMEPAD_DPAD_RIGHT:
						{
							m_ActionState->m_DPad = eDirectionE;
							break;
						}
					case XINPUT_GAMEPAD_START:
						{
							m_ActionState->m_Start = true;
							break;
						}
					case XINPUT_GAMEPAD_BACK:
						{
							m_ActionState->m_Back = true;
							break;
						}
					}
				}
			}
		}
	} // Namespace Components
} // Namespace Flex