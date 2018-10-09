//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cSprite.hpp
// Description: 
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#ifndef __FLEX_COMPONENTS_CSPRITE_HPP__
#define __FLEX_COMPONENTS_CSPRITE_HPP__

#include "precom.h"
#include "../../../Common/Defines.hpp"

namespace flex
{
	namespace components
	{

		class cSprite
		{
		public:
			cSprite(IDirect3DDevice9* D3dDevice);
			~cSprite(void);
			void Delete( void );

			void LoadTexture( const std::string &filename, const int &width, const int &height );

			void SetAnimation( const int &FramesTotal, const int &FramesWidth, const int &FramesHeight, const int &PixelsWidth, const int &PixelHeight ) { m_FramesTotal = FramesTotal; m_FramesWidth = FramesWidth; m_FramesHeight = FramesHeight; m_PixelsWidth = PixelsWidth; m_PixelHeight = PixelHeight; }

			void Render(float posx, float posy, float posz, int FrameNumber);

			std::string GetFileName(){ return m_FileName; }

		private:
			IDirect3DDevice9*       m_D3dDevice;
			IDirect3DTexture9*      m_Texture;
			ID3DXSprite*            m_Sprite;

			std::string             m_FileName;
			int                     m_Width;
			int                     m_Height;
			int                     m_FramesTotal;
			int                     m_FramesWidth;
			int                     m_FramesHeight;
			int                     m_PixelsWidth;
			int                     m_PixelHeight;
		};
	} // Namespace Components
} // Namespace Flex

#endif


