//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cQuad.cpp
// Description: 
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#include "precom.h"
#include "cQuad.hpp"

namespace flex
{
	namespace components
	{
		template <class T>
		std::string ToString(const T & t)
		{
			std::ostringstream oss; // create a stream
			oss << t;              // insert value to stream 
			return oss.str();      // return as a string
		}

		cQuad::cQuad( IDirect3DDevice9* D3dDevice ): m_D3dDevice(D3dDevice), m_Texture(NULL), m_VertexBuffer(NULL), m_FileName("")
		{
			/*m_QuadVertices[0] = Vertex(-6.4f, 3.6f, 0.0f,  0.0f,0.0f);
			m_QuadVertices[1] = Vertex(6.4f, 3.6f, 0.0f,  1.0f,0.0f);
			m_QuadVertices[2] = Vertex(-6.4f,-3.6f, 0.0f,  0.0f,1.0f);
			m_QuadVertices[3] = Vertex(6.4f,-3.6f, 0.0f,  1.0f,1.0f);*/
		}

		cQuad::~cQuad(void)
		{
			Delete();
		}

		void cQuad::Delete( void )
		{
			SAFE_RELEASE(m_Texture);
			SAFE_RELEASE(m_VertexBuffer);
		}

		void cQuad::LoadTexture( const std::string &filename, const int &width, const int &height )
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

			if( height > width )
			{
				m_QuadVertices[0] = Vertex( -1.0f * (float)((float)width/(float)height),  1.0f, 0.0f,  0.0f, 0.0f);
				m_QuadVertices[1] = Vertex(  1.0f * (float)((float)width/(float)height),  1.0f, 0.0f,  1.0f, 0.0f);
				m_QuadVertices[2] = Vertex( -1.0f * (float)((float)width/(float)height), -1.0f, 0.0f,  0.0f, 1.0f);
				m_QuadVertices[3] = Vertex(  1.0f * (float)((float)width/(float)height), -1.0f, 0.0f,  1.0f, 1.0f);
			}
			else if( width > height )
			{
				m_QuadVertices[0] = Vertex( -1.0f,  1.0f * (float)((float)height/(float)width), 0.0f,  0.0f, 0.0f);
				m_QuadVertices[1] = Vertex(  1.0f,  1.0f * (float)((float)height/(float)width), 0.0f,  1.0f, 0.0f);
				m_QuadVertices[2] = Vertex( -1.0f, -1.0f * (float)((float)height/(float)width), 0.0f,  0.0f, 1.0f);
				m_QuadVertices[3] = Vertex(  1.0f, -1.0f * (float)((float)height/(float)width), 0.0f,  1.0f, 1.0f);
			}
			else
			{
				m_QuadVertices[0] = Vertex( -1.0f, 1.0f, 0.0f,  0.0f, 0.0f);
				m_QuadVertices[1] = Vertex(  1.0f, 1.0f, 0.0f,  1.0f, 0.0f);
				m_QuadVertices[2] = Vertex( -1.0f,-1.0f, 0.0f,  0.0f, 1.0f);
				m_QuadVertices[3] = Vertex(  1.0f,-1.0f, 0.0f,  1.0f, 1.0f);
			}

			m_D3dDevice->CreateVertexBuffer( 4*sizeof(Vertex), D3DUSAGE_WRITEONLY, 
				D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, 
				&m_VertexBuffer, NULL );
			void *pVertices = NULL;

			m_VertexBuffer->Lock( 0, sizeof(m_QuadVertices), (void**)&pVertices, 0 );
			memcpy( pVertices, m_QuadVertices, sizeof(m_QuadVertices) );
			m_VertexBuffer->Unlock();
		}

		void cQuad::Render( D3DXMATRIX Matrix )
		{
			m_D3dDevice->SetTransform( D3DTS_WORLD, &Matrix );

			m_D3dDevice->SetTexture( 0, m_Texture );
			m_D3dDevice->SetStreamSource( 0, m_VertexBuffer, 0, sizeof(Vertex) );
			m_D3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
			m_D3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
		}
	} // Namespace Components
} // Namespace Flex
