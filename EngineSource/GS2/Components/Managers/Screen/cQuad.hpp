//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cQuad.hpp
// Description: 
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#ifndef __FLEX_COMPONENTS_CQUAD_HPP__
#define __FLEX_COMPONENTS_CQUAD_HPP__

#include "precom.h"
#include "../../../Common/Defines.hpp"

namespace flex
{
	namespace components
	{
		#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZ | D3DFVF_TEX1 )

		struct Vertex
		{
			Vertex()
			{

			}
			Vertex(float px, float py, float pz, float ptu, float ptv) : x(px), y(py), z(pz), tu(ptu), tv(ptv)
			{
			}
			float x, y, z;
			float tu, tv;
		};

		//Vertex g_quadVertices[] =
		//{
		//	{-1.0f, 1.0f, 0.0f,  0.0f,0.0f },
		//	{ 1.0f, 1.0f, 0.0f,  1.0f,0.0f },
		//	{-1.0f,-1.0f, 0.0f,  0.0f,1.0f },
		//	{ 1.0f,-1.0f, 0.0f,  1.0f,1.0f }
		//};

		class cQuad
		{
		public:
			cQuad(IDirect3DDevice9* D3dDevice);
			~cQuad(void);
			void Delete( void );

			void LoadTexture( const std::string &filename, const int &width, const int &height );

			void Render( D3DXMATRIX Matrix );

			std::string GetFileName(){ return m_FileName; }

		private:
			IDirect3DDevice9*       m_D3dDevice;
			IDirect3DTexture9*      m_Texture;
			IDirect3DVertexBuffer9* m_VertexBuffer;

			Vertex                  m_QuadVertices[4];

			std::string             m_FileName;
		};
	} // Namespace Components
} // Namespace Flex

#endif


