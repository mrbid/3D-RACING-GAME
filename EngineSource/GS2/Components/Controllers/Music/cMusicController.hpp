//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cMusicController.hpp
// Description:
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#ifndef __FLEX_COMPONENTS_MANAGERS_SCREEN_CMUSICCONTROLLER_HPP__
#define __FLEX_COMPONENTS_MANAGERS_SCREEN_CMUSICCONTROLLER_HPP__

#include "precom.h"
#include "BaseController.h"
#include "cMusic.hpp"

namespace flex
{
	namespace components
	{
		//commented out to fix build
		class flex::components::cMusic;
		//Music Manager Class
		class cMusicController : public BaseController
		{
		public:

			//Destructor
			~cMusicController();

			//Tick Controller
			void Update(float dt);

			//Render Controller
			void Render();

		private:
			//Array of vehicle entities
			std::vector<flex::components::cMusic*> m_Music;
			//Music Count
			int  m_MusicCount;

			long m_SongStart;

		};
	} // Namespace Components
} // Namespace Flex

#endif