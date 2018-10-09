//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cGameScreenLoading.hpp
// Description: Generic Screen Management System
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#ifndef __FLEX_COMPONENTS_CGAMESCREENLOADING_HPP__
#define __FLEX_COMPONENTS_CGAMESCREENLOADING_HPP__

#include "precom.h"
#include "IGameScreen.hpp"
#include "../../Input/InputAction.hpp"

namespace flex
{
	namespace components
	{
		class cGameScreenLoading : public IGameScreen
		{
		public:
			cGameScreenLoading(void);
			~cGameScreenLoading(void);
			void Render(void);
			void Update( const float& dt );
			void Messages(sInputState* wButtons);
			void Refresh( void );

			void SetTrackId( const int& id ) { trackId = id; }
			void SetCarId( const int& id ) { carId = id; }

			void LoadTrack( const int& id );
			void LoadCar( const int& id );


			void RenderProgressBar( void );
			void SetProgressBar( const int& percentage );

			void SetPopScreen( const bool& popscreen ) { PopScreenCheck = popscreen; }

			int carId;
			int trackId;

			float LoadingPercentage;

			bool PopScreenCheck;

			int m_TextureID1;

			float Texture1ScaleX;
			float Texture1ScaleY;
			float Texture1ScaleZ;

			int m_TextureIDProgressbarBack;
			int m_TextureIDProgressbarLoad;

			float m_TimeLast;
		};

	} // Namespace Components
} // Namespace Flex

#endif
