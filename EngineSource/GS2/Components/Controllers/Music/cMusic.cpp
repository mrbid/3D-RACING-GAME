//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cMusic.cpp
// Description: 
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#include "precom.h"
#include "cMusic.hpp"

namespace flex
{
	namespace components
	{
		cMusic::cMusic(void) : m_FileName(""), m_Length(0)
		{
		}

		cMusic::~cMusic(void)
		{
			Delete();
		}

		void cMusic::Delete( void )
		{
		}

		void cMusic::LoadFile( const std::string &filename, const int &Length )
		{
		}

	} // Namespace Components
} // Namespace Flex
