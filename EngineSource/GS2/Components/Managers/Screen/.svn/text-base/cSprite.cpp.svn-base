//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cSprite.cpp
// Description: 
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#include "precom.h"
#include "cSprite.hpp"

namespace flex
{
	namespace components
	{
		cSprite::cSprite( IDirect3DDevice9* D3dDevice ): m_D3dDevice(D3dDevice), m_Texture(NULL), m_Sprite(NULL), m_FileName(""), m_Width(0), m_Height(0), m_FramesTotal(0), m_FramesWidth(0), m_FramesHeight(0), m_PixelsWidth(0), m_PixelHeight(0)
		{
		}

		cSprite::~cSprite(void)
		{
			Delete();
		}

		void cSprite::Delete( void )
		{
			SAFE_RELEASE(m_Texture);
			SAFE_RELEASE(m_Sprite);
		}

		void cSprite::LoadTexture( const std::string &filename, const int &width, const int &height )
		{
			D3DXIMAGE_INFO d3dxImageInfo;

			D3DXCreateTextureFromFileEx( m_D3dDevice,
				filename.c_str(),
				width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
				height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
				1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
				D3DPOOL_DEFAULT,
				D3DFMT_UNKNOWN,
				D3DPOOL_DEFAULT,
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,1.0f),
				&d3dxImageInfo,
				NULL,
				&m_Texture );

			m_Width  = width;
			m_Height = height;

			D3DXCreateSprite( m_D3dDevice, &m_Sprite );
		}

		void cSprite::Render(float posx, float posy, float posz, int FrameNumber)
		{
			assert( FrameNumber <= m_FramesTotal && "Frame is less than Total Frames");
			if(m_FramesTotal == 0)
			{
				// Build a source RECT which will copy only a small portion of the texture.
				RECT srcRect;
				srcRect.top    = 0;
				srcRect.left   = 0;
				srcRect.bottom = m_Height;
				srcRect.right  = m_Width;

				D3DXVECTOR3 vCenter( 0.0f, 0.0f, 0.0f );
				D3DXVECTOR3 vPosition( posx, posy, posz );

				m_Sprite->Begin( D3DXSPRITE_ALPHABLEND );

				m_Sprite->Draw( m_Texture,
					&srcRect,
					&vCenter,
					&vPosition,
					D3DCOLOR_COLORVALUE(1.0f,1.0f,1.0f,1.0f) );

				m_Sprite->End();
			}
			else
			{
				// Build a source RECT which will copy only a small portion of the texture.
				RECT srcRect;
				srcRect.top    = (( FrameNumber / (m_FramesHeight-1)) * m_PixelHeight);
				srcRect.left   = (( FrameNumber % m_FramesWidth ) * m_PixelsWidth);
				srcRect.bottom = srcRect.top  + m_PixelHeight;
				srcRect.right  = srcRect.left + m_PixelsWidth;

				D3DXVECTOR3 vCenter( 0.0f, 0.0f, 0.0f );
				D3DXVECTOR3 vPosition( posx, posy, posz );

				m_Sprite->Begin( D3DXSPRITE_ALPHABLEND );

				m_Sprite->Draw( m_Texture,
					&srcRect,
					&vCenter,
					&vPosition,
					D3DCOLOR_COLORVALUE(1.0f,1.0f,1.0f,1.0f) );

				m_Sprite->End();
			}
		}
	} // Namespace Components
} // Namespace Flex
