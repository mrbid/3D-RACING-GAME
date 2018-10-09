//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cMusic.hpp
// Description: 
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#ifndef __FLEX_COMPONENTS_CMUSIC_HPP__
#define __FLEX_COMPONENTS_CMUSIC_HPP__

#include "precom.h"

namespace flex
{
	namespace components
	{
		class cMusic
		{
		public:
			cMusic();
			~cMusic(void);
			void Delete( void );

			void LoadFile( const std::string &filename, const int &Length );

			std::string GetFileName(){ return m_FileName; }
			int GetLength(){ m_Length; }

		private:
			std::string             m_FileName;
			int                     m_Length;
		};
	} // Namespace Components
} // Namespace Flex

#endif


