//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------

#ifndef __DEFINES_HPP__
#define __DEFINES_HPP__

#include "precom.h"

//Game Running With Full Debug Outputs
//#define DEBUG


//Safe Release / Delete Macros
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

//Controller
#define MAX_CONTROLLERS 4  // XInput handles up to 4 controllers 
#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.
//#define INPUT_DEADZONE  ( 0.10f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.

//Camera Speeds
#define CameraMoveSpeed     1.0f
#define CameraRotationSpeed 0.01f

#define TestScreenWidth    1280
#define TestScreenHeight   720

#ifdef _WIN32 // _WIN32 is defined by all Windows 32 and 64 bit compilers, but not by others.
#define FLEX_INLINE __inline
#define FLEX_FINLINE __forceinline
#else
#define FLEX_INLINE inline
//#define FLEX_FINLINE 
#endif

#endif