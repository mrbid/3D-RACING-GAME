/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#include "precom.h"
#include "GS2.h"
#include "GameWorld.h"
#include "Components/Managers/Input/cInputManager.hpp"
#include "Components/Managers/Screen/cScreenManager.hpp"
#include "MilliTimer.h"

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

//Window
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
const char szClassName[ ] = "Games Development Group Project";
const int window_width = 1280;
const int window_height = 720;
const int window_width_2 = window_width/2;
const int window_height_2 = window_height/2;
HWND hwnd;

//Windows Main Function
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunc)
{
	//Setup Win32 Window
    MSG messages;
    WNDCLASSEX wincl;
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_HREDRAW | CS_VREDRAW;
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIcon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_BIG));
    wincl.hIconSm = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_SMALL));
    wincl.hCursor = LoadCursor(GetModuleHandle(0), IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

	//Did register class fail?
    if(!RegisterClassEx(&wincl))
		return 0;

	//Create Window
    hwnd = CreateWindowEx(
           0,
           szClassName,
           "Games Development Group Project",
           WS_OVERLAPPEDWINDOW,
           (GetSystemMetrics(SM_CXFULLSCREEN) -window_width) / 2,
		   (GetSystemMetrics(SM_CYFULLSCREEN) -window_height) / 2,
           window_width,
           window_height,
           HWND_DESKTOP,
           NULL,
           hThisInstance,
           NULL
		   );

	////Test Keboard
	//RAWINPUTDEVICE Rid[2];

	//// Keyboard
	//Rid[0].usUsagePage = 1;
	//Rid[0].usUsage = 6;
	//Rid[0].dwFlags = 0;
	//Rid[0].hwndTarget=NULL;

	//// Mouse
	//Rid[1].usUsagePage = 1;
	//Rid[1].usUsage = 2;
	//Rid[1].dwFlags = 0;
	//Rid[1].hwndTarget=NULL;

	//if (RegisterRawInputDevices(Rid,2,sizeof(RAWINPUTDEVICE))== FALSE)
	//	std::cout << "Error Registering Raw Input Devices" << std::endl;
	////Test Keboard

	//Show window and disable cursor
    ShowWindow(hwnd, SW_SHOWDEFAULT);
	ShowCursor(false);

	//Set Icon
	//SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_SMALL)));
	//SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_BIG)));
	

	//Initialize GameWorld
	GameWorld().Init(hwnd);
	float Update_Regulator = 0;

	//Initialize Input
	flex::components::cInputManager::Create();
	if(!IMG->Initialise())
		return false;

	//Initialize ScreenManager
	flex::components::cScreenManager::Create();
	if(!SMG->Initialise())
		return false;

	SMG->RenderLoadScreen();
	SMG->Load();

	//Load GameWorld
	GameWorld().Load();

	//Game Loop
    const double TickMs = 1000 / 25;
	const double RecipTickMs = 1.f / TickMs;
	double next_game_tick = GetTime();

	//Message Loop
	bool quit = false;
    while(quit == false)
    {
		if(PeekMessage(&messages, NULL, 0, 0, PM_REMOVE))
		{
			if(messages.message == WM_QUIT){quit = true;}
			TranslateMessage(&messages);
			DispatchMessage(&messages);
		}
		else
		{

			if(messages.message == WM_SIZE && messages.wParam == SIZE_MINIMIZED)
			{
				//Minimized so sleep
				Sleep(1000);
			}
			else
			{
				//Render
				SMG->Render();

				//Update Logic
				double dt = GetTime() - next_game_tick;
				while(dt >= TickMs)
				{
					dt -= TickMs;
					next_game_tick += TickMs;

					SMG->Update(float(((GetTime() + TickMs) - next_game_tick) * RecipTickMs));
				}

				if(GetTime() > Update_Regulator)
				{
					//Update Input
					IMG->Update();

					//Update Regulator
					Update_Regulator = GetTime() + 16;
				}
			}

		}
    }
	IMG->Delete();
	SMG->Delete();
    return messages.wParam;
}


//Windows Callback
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_ACTIVATEAPP:
		{
			if( wParam == TRUE )
			{
				// App is now active, so re-enable XInput
				XInputEnable( true );
			}
			else
			{
				// App is now inactive, so disable XInput to prevent
				// user input from effecting application and to 
				// disable rumble. 
				XInputEnable( false );
			}
			break;
		}
		//case WM_INPUT:
		//{
		//	// this is where we read the device data
		//	// Determine how big the buffer should be
		//	UINT bufferSize;

		//	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &bufferSize, sizeof (RAWINPUTHEADER));

		//	// Create a buffer of the correct size - but see note below
		//	BYTE *buffer=new BYTE[bufferSize];

		//	// Call the function again, this time with the buffer to get the data
		//	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, (LPVOID)buffer, &bufferSize, sizeof (RAWINPUTHEADER));
		//	IMG->UpdateWindowsInput(bufferSize, buffer);
		//}
		//return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE)
			PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
		break;
	}

	return 0;
}
