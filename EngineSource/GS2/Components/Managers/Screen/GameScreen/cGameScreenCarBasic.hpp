//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cGameScreenCarBasic.hpp
// Description: Generic Screen Management System
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#ifndef __FLEX_COMPONENTS_CGAMESCREENCARBASIC_HPP__
#define __FLEX_COMPONENTS_CGAMESCREENCARBASIC_HPP__

#include "precom.h"
#include "IGameScreen.hpp"
#include "../../Input/InputAction.hpp"

#include <map>

#define SPEEDOOFFSET 155
#define SPEEDOSCALEFACTOR 1.3

namespace flex
{
	namespace components
	{
		class cGameScreenCarBasic : public IGameScreen
		{
		public:
			cGameScreenCarBasic( void );
			~cGameScreenCarBasic( void );
			void Render( void );
			void Update( const float& dt );
			void Messages( sInputState* wButtons );
			void Refresh( void );

			void RenderBackground( void );
			void RenderTracks( void );

			void RenderTrackSample( int textureID, float positionX, float positionY, float positionZ );

			void RenderArrow( int textureID, float positionX, float positionY, float positionZ );

			void RenderPadLock( int textureID, float positionX, float positionY, float positionZ );

			//std::vector<std::string>* trackList;

			//std::map<std::string, int>* trackMap;

			int currentSelection;

			int   m_TextureBackground;
			float m_TextureBackgroundScaleX;
			float m_TextureBackgroundScaleY;
			float m_TextureBackgroundScaleZ;


			int m_TextureTrack1;
			int m_TextureTrack2;
			int m_TextureTrack3;
			int m_TextureTrack4;
			int m_TextureTrack5;
			int m_TextureTrack6;
			int m_TextureTrack7;
			int m_TextureTrack8;
			int m_TextureTrack9;
			int m_TextureTrack10;
			int m_TextureTrack11;
			int m_TextureTrack12;

			int m_TextureLeft;
			int m_TextureRight;

			int m_TexturePadlock;

			float m_TrackScaleX;
			float m_TrackScaleY;
			float m_TrackScaleZ;

			float m_TimeLast;
		};

	} // Namespace Components
} // Namespace Flex

#endif
