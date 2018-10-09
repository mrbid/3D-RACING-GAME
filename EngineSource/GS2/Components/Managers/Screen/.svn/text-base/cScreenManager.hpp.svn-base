//////////////////////////////////////////////////
// Flex Framework
//////////////////////////////////////////////////
// File: cScreenManager.hpp
// Description: Generic Screen Management System
// Original Author: Sam Hughes - http://www.thesamhughes.com
// Date: 29 - 10 - 2010
// Revisions: 1 Original
//////////////////////////////////////////////////

#ifndef __FLEX_COMPONENTS_MANAGERS_SCREEN_CSCREENMANAGER_HPP__
#define __FLEX_COMPONENTS_MANAGERS_SCREEN_CSCREENMANAGER_HPP__

#include "precom.h"
#include "../Input/InputAction.hpp"
#include "cSprite.hpp"
#include "cQuad.hpp"
#include "../../../D3DRenderer.h"

namespace flex
{
	namespace components
	{
		class IGameScreen;

		class cScreenManager
		{
		public:
			static cScreenManager& Instance()
			{
				assert( m_pInstance );
				return *m_pInstance;
			}
			static cScreenManager* InstancePtr()
			{
				return m_pInstance;
			}
			static void Create()
			{
				if (!m_pInstance)
					m_pInstance = new cScreenManager;
			}
			static void Delete()
			{
				delete m_pInstance;
				m_pInstance = 0;
			}

			bool Initialise( void );
			bool Load( void );

			int AddScreen( IGameScreen* Screen );

			void SetHudId( const int& HudId ) { m_HudId = HudId; }
			void SetRenderHud( const bool& RenderHud ) { m_RenderHud = RenderHud; }

			void PushScreen ( int ID );
			void PopScreen  (  void  );

			void Messages( sInputState* wButtons );
			void Update( const float& dt );
			void Render();
			void RenderLoadScreen();
			void SetProgressbar( const int& percentage );
			void SetPopLoadingScreen( const bool& popscreen );

			void SetTrack( const int& id );
			void SetCar( const int& id );

			int  AddSprite( const std::string &filename, const int &width, const int &height );
			void RenderSprite(int SpriteID, float C1X, float C1Y, float C1Z, float C2X, float C2Y, float C2Z);

			int AddQuad( const std::string &filename, const int &width, const int &height );
			void RenderQuad(const int &QuadID,  const D3DXMATRIX &Matrix );

			void SetMatrices( void );

			bool					  m_resetprojection;

		private:
			std::vector<flex::components::IGameScreen*> m_Screens;
			int                       m_ScreenDepth;
			std::vector<int>          m_ScreenFlowOrder;

			std::vector<cSprite*>     m_Sprites;
			std::vector<cQuad*>       m_Quads;

			D3DXMATRIX                m_GameProjectionMatrix;

			bool                      m_CacheScreens;

			D3DXMATRIX m_MatView;

			bool m_RenderHud;
			int m_HudId;
			int m_LoadingId;
		
		private:
			cScreenManager(void);
			cScreenManager(cScreenManager const&); // copy ctor hidden
			//cScreenManager& operator=(cScreenManager const&); // assign op. hidden
			~cScreenManager(void);

		protected:
			static cScreenManager* m_pInstance;
		};
	} // Namespace Components
} // Namespace Flex

#define SMG flex::components::cScreenManager::InstancePtr()

#endif
