/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/


#include "precom.h"
#include "CellularAutomata.h"
#include "Colours.h"
using namespace clr;


//Generate Cellular Automata 2C
void Cellular2D2C::Generate(Rule2C rule, int m_rfl)
{
	//If RFL then generate a random first line
	if(m_rfl == 1)
	{
		for(int i = 0; i < m_grid_w; i++)
		{
			m_grid[i][0] = qRandBool();
		}
	}
	
	//No RFL, so just place one black pixel in the middle
	if(m_rfl == 2)
	{
		m_grid[m_grid_w/2][0] = 1;
	}
	
	//Generate Cellular Automata
	for(int y = 1; y < m_grid_h; y++)
	{
		for(int x = 1; x < m_grid_w-1; x++)
		{
			if(rule.r[0] == true) //is rule 0 enabled?
			{
				if(m_grid[x-1][y-1] == true && m_grid[x][y-1] == true && m_grid[x+1][y-1] == true) //Check Rule
				{
					m_grid[x][y] = true;
				}
			}
			
			if(rule.r[1] == true) //is rule 1 enabled?
			{
				if(m_grid[x-1][y-1] == true && m_grid[x][y-1] == true && m_grid[x+1][y-1] == false) //Check Rule
				{
					m_grid[x][y] = true;
				}
			}
			
			if(rule.r[2] == true) //is rule 2 enabled?
			{
				if(m_grid[x-1][y-1] == true && m_grid[x][y-1] == false && m_grid[x+1][y-1] == true) //Check Rule
				{
					m_grid[x][y] = true;
				}
			}
			
			if(rule.r[3] == true) //is rule 3 enabled?
			{
				if(m_grid[x-1][y-1] == true && m_grid[x][y-1] == false && m_grid[x+1][y-1] == false) //Check Rule
				{
					m_grid[x][y] = true;
				}
			}
			
			if(rule.r[4] == true) //is rule 4 enabled?
			{
				if(m_grid[x-1][y-1] == false && m_grid[x][y-1] == true && m_grid[x+1][y-1] == true) //Check Rule
				{
					m_grid[x][y] = true;
				}
			}
			
			if(rule.r[5] == true) //is rule 5 enabled?
			{
				if(m_grid[x-1][y-1] == false && m_grid[x][y-1] == true && m_grid[x+1][y-1] == false) //Check Rule
				{
					m_grid[x][y] = true;
				}
			}
			
			if(rule.r[6] == true) //is rule 6 enabled?
			{
				if(m_grid[x-1][y-1] == false && m_grid[x][y-1] == false && m_grid[x+1][y-1] == true) //Check Rule
				{
					m_grid[x][y] = true;
				}
			}
			
			if(rule.r[7] == true) //is rule 7 enabled?
			{
				if(m_grid[x-1][y-1] == false && m_grid[x][y-1] == false && m_grid[x+1][y-1] == false) //Check Rule
				{
					m_grid[x][y] = 1;
				}
			}
		}
	}
}


//Generate Cellular Automata 3C
void Cellular2D3C::Generate(Rule3C rule, int m_rfl)
{	
	//If RFL is 1 then generate a random first line of white and black
	if(m_rfl == 1)
	{
		for(int i = 0; i < m_grid_w; i++)
		{
			m_grid[i][0] = qRandBool() ? 1 : 0;
		}
	}
	
	//If RFL is 2 generate a random first line of white black and grey
	if(m_rfl == 3)
	{
		for(int i = 0; i < m_grid_w; i++)
		{
			m_grid[i][0] = qRand(0, 3); //this means 0 - 2
		}
	}
	
	//If rfl is 3 just place one grey pixel in the middle
	if(m_rfl == 2)
	{
		m_grid[m_grid_w/2][0] = 1;
	}
	
	//If rfl is 4 just place one black pixel in the middle
	if(m_rfl == 4)
	{
		m_grid[m_grid_w/2][0] = 2;
	}
	
	//Generate Cellular Automata
	for(int y = 1; y < m_grid_h; y++)
	{
		for(int x = 1; x < m_grid_w-1; x++)
		{
			if(rule.r[0] != 0) //is rule 0 enabled?
			{
				if(m_grid[x-1][y-1] + m_grid[x][y-1] + m_grid[x+1][y-1] == 6) //Check Rule
				{
					m_grid[x][y] = rule.r[0];
				}
			}
			
			if(rule.r[1] != 0) //is rule 1 enabled?
			{
				if(m_grid[x-1][y-1] + m_grid[x][y-1] + m_grid[x+1][y-1] == 5) //Check Rule
				{
					m_grid[x][y] = rule.r[1];
				}
			}
			
			if(rule.r[2] != 0) //is rule 2 enabled?
			{
				if(m_grid[x-1][y-1] + m_grid[x][y-1] + m_grid[x+1][y-1] == 4) //Check Rule
				{
					m_grid[x][y] = rule.r[2];
				}
			}
			
			if(rule.r[3] != 0) //is rule 3 enabled?
			{
				if(m_grid[x-1][y-1] + m_grid[x][y-1] + m_grid[x+1][y-1] == 3) //Check Rule
				{
					m_grid[x][y] = rule.r[3];
				}
			}
			
			if(rule.r[4] != 0) //is rule 4 enabled?
			{
				if(m_grid[x-1][y-1] + m_grid[x][y-1] + m_grid[x+1][y-1] == 2) //Check Rule
				{
					m_grid[x][y] = rule.r[4];
				}
			}
			
			if(rule.r[5] != 0) //is rule 5 enabled?
			{
				if(m_grid[x-1][y-1] + m_grid[x][y-1] + m_grid[x+1][y-1] == 1) //Check Rule
				{
					m_grid[x][y] = rule.r[5];
				}
			}
			
			if(rule.r[6] != 0) //is rule 6 enabled?
			{
				if(m_grid[x-1][y-1] + m_grid[x][y-1] + m_grid[x+1][y-1] == 0) //Check Rule
				{
					m_grid[x][y] = rule.r[6];
				}
			}
		}
	}
}


//Generate 1D Cellular Automata with 2 Colours
void Cellular1D2C::Generate(Rule2C rule, int rfl)
{	
	//If RFL is true then randomly generate the first three elements
	if(rfl == 1)
	{
		m_array[0] = qRandBool();
		m_array[1] = qRandBool();
		m_array[2] = qRandBool();
	}
	
	//Else just set the second element to true
	if(rfl == 2)
	{
		m_array[0] = false;
		m_array[1] = true;
		m_array[2] = false;
	}
	
	//Generate Cellular Automata
	for(int i = 4; i < m_array_len; i++)
	{
		if(rule.r[0] == true) //is rule 0 enabled?
		{
			if(m_array[i-3] == true && m_array[i-2] == true && m_array[i-1] == true)
			{
				m_array[i] = true;
			}
		}
		
		if(rule.r[1] == true) //is rule 1 enabled?
		{
			if(m_array[i-3] == true && m_array[i-2] == true && m_array[i-1] == false)
			{
				m_array[i] = true;
			}
		}
		
		if(rule.r[2] == true) //is rule 2 enabled?
		{
			if(m_array[i-3] == true && m_array[i-2] == false && m_array[i-1] == true)
			{
				m_array[i] = true;
			}
		}
		
		if(rule.r[3] == true) //is rule 3 enabled?
		{
			if(m_array[i-3] == true && m_array[i-2] == false && m_array[i-1] == false)
			{
				m_array[i] = true;
			}
		}
		
		if(rule.r[4] == true) //is rule 4 enabled?
		{
			if(m_array[i-3] == false && m_array[i-2] == true && m_array[i-1] == true)
			{
				m_array[i] = true;
			}
		}
		
		if(rule.r[5] == true) //is rule 5 enabled?
		{
			if(m_array[i-3] == false && m_array[i-2] == true && m_array[i-1] == false)
			{
				m_array[i] = true;
			}
		}
		
		if(rule.r[6] == true) //is rule 6 enabled?
		{
			if(m_array[i-3] == false && m_array[i-2] == false && m_array[i-1] == true)
			{
				m_array[i] = true;
			}
		}
		
		if(rule.r[7] == true) //is rule 7 enabled?
		{
			if(m_array[i-3] == false && m_array[i-2] == false && m_array[i-1] == false)
			{
				m_array[i] = true;
			}
		}
	}
}


//Generate 1D Cellular Automata with 2 Colours
void Cellular1D3C::Generate(Rule3C rule, int rfl)
{
	//If RFL is 1 then the firs three elements are random 0 or 1
	if(rfl == 1)
	{
		m_array[0] = qRandBool() ? 1 : 0;
		m_array[1] = qRandBool() ? 1 : 0;
		m_array[2] = qRandBool() ? 1 : 0;
	}
	
	//If RFL is 2 then the firs three elements are random 0, 1 or 2
	if(rfl == 3)
	{
		m_array[0] = qRand(0, 3);
		m_array[1] = qRand(0, 3);
		m_array[2] = qRand(0, 3);
	}
	
	//If RFL is 3 then the second element is 1
	if(rfl == 2)
	{
		m_array[0] = 0;
		m_array[1] = 1;
		m_array[2] = 0;
	}
	
	//If RFL is 4 then the second element is 2
	if(rfl == 4)
	{
		m_array[0] = 0;
		m_array[1] = 2;
		m_array[2] = 0;
	}
	
	//Generate Cellular Automata
	for(int i = 4; i < m_array_len; i++)
	{
		if(rule.r[0] != 0) //is rule 0 enabled?
		{
			if(m_array[i-3] + m_array[i-2] + m_array[i-1] == 6)
			{
				m_array[i] = rule.r[0];
			}
		}
		
		if(rule.r[1] != 0) //is rule 1 enabled?
		{
			if(m_array[i-3] + m_array[i-2] + m_array[i-1] == 5)
			{
				m_array[i] = rule.r[1];
			}
		}
		
		if(rule.r[2] != 0) //is rule 2 enabled?
		{
			if(m_array[i-3] + m_array[i-2] + m_array[i-1] == 4)
			{
				m_array[i] = rule.r[2];
			}
		}
		
		if(rule.r[3] != 0) //is rule 3 enabled?
		{
			if(m_array[i-3] + m_array[i-2] + m_array[i-1] == 3)
			{
				m_array[i] = rule.r[3];
			}
		}
		
		if(rule.r[4] != 0) //is rule 4 enabled?
		{
			if(m_array[i-3] + m_array[i-2] + m_array[i-1] == 2)
			{
				m_array[i] = rule.r[4];
			}
		}
		
		if(rule.r[5] != 0) //is rule 5 enabled?
		{
			if(m_array[i-3] + m_array[i-2] + m_array[i-1] == 1)
			{
				m_array[i] = rule.r[5];
			}
		}
		
		if(rule.r[6] != 0) //is rule 6 enabled?
		{
			if(m_array[i-3] + m_array[i-2] + m_array[i-1] == 0)
			{
				m_array[i] = rule.r[6];
			}
		}
	}
}


//Create a Cellular Automata 3C Texture
LPDIRECT3DTEXTURE9 CreateCellular3CTexture(IDirect3DDevice9* d3dDevice, Rule3C rule, int rfl, int texscale, float hue, float saturation, float lightness)
{
	Cellular2D3C ca;
	LPDIRECT3DTEXTURE9 texture;
	D3DLOCKED_RECT lr;

	ca.InitCellular(texscale, texscale);
	ca.Generate(rule, rfl);

	d3dDevice->CreateTexture(texscale, texscale, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, 0);
	texture->LockRect(0, &lr, NULL, 0);
	UCHAR* pRect = (UCHAR*)lr.pBits;
		
	for(int y = 0; y < texscale; y++)
	{
		for(int x = 0; x < texscale; x++)
		{
			if(ca.GetValue(x, y) == 0)
			{
				const int offset = ((y*texscale)+x)*4;
				mColour oc(1.f, 1.f, 1.f);
				oc = RGBtoHSL(oc);
				oc.r = hue;
				oc.g = saturation;
				oc.b += lightness;
				oc = clamp(HSLtoRGB(oc));
				pRect[offset] = oc.r*255;
				pRect[offset+1] = oc.g*255;
				pRect[offset+2] = oc.b*255;
			}

			if(ca.GetValue(x, y) == 1)
			{
				const int offset = ((y*texscale)+x)*4;
				mColour oc(0.5f, 0.5f, 0.5f);
				oc = RGBtoHSL(oc);
				oc.r = hue;
				oc.g = saturation;
				oc.b += lightness;
				oc = clamp(HSLtoRGB(oc));
				pRect[offset] = oc.r*255;
				pRect[offset+1] = oc.g*255;
				pRect[offset+2] = oc.b*255;
			}

			if(ca.GetValue(x, y) == 2)
			{
				const int offset = ((y*texscale)+x)*4;
				mColour oc(0.f, 0.f, 0.f);
				oc = RGBtoHSL(oc);
				oc.r = hue;
				oc.g = saturation;
				oc.b += lightness;
				oc = clamp(HSLtoRGB(oc));
				pRect[offset] = oc.r*255;
				pRect[offset+1] = oc.g*255;
				pRect[offset+2] = oc.b*255;
			}
		}
	}
		
	texture->UnlockRect(0);
	texture->GenerateMipSubLevels();
	return texture;
}


//Create a Cellular Automata 2C Texture
LPDIRECT3DTEXTURE9 CreateCellular2CTexture(IDirect3DDevice9* d3dDevice, Rule2C rule, int rfl, int texscale, float hue, float saturation, float lightness)
{
	Cellular2D2C ca;
	LPDIRECT3DTEXTURE9 texture;
	D3DLOCKED_RECT lr;

	ca.InitCellular(texscale, texscale);
	ca.Generate(rule, rfl);

	d3dDevice->CreateTexture(texscale, texscale, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, 0);
	texture->LockRect(0, &lr, NULL, 0);
	UCHAR* pRect = (UCHAR*)lr.pBits;
		
	for(int y = 0; y < texscale; y++)
	{
		for(int x = 0; x < texscale; x++)
		{
			if(ca.GetValue(x, y) == false)
			{
				const int offset = ((y*texscale)+x)*4;
				mColour oc(1.f, 1.f, 1.f);
				oc = RGBtoHSL(oc);
				oc.r = hue;
				oc.g = saturation;
				oc.b += lightness;
				oc = clamp(HSLtoRGB(oc));
				pRect[offset] = oc.r*255;
				pRect[offset+1] = oc.g*255;
				pRect[offset+2] = oc.b*255;
			}

			if(ca.GetValue(x, y) == true)
			{
				const int offset = ((y*texscale)+x)*4;
				mColour oc(0.f, 0.f, 0.f);
				oc = RGBtoHSL(oc);
				oc.r = hue;
				oc.g = saturation;
				oc.b += lightness;
				oc = clamp(HSLtoRGB(oc));
				pRect[offset] = oc.r*255;
				pRect[offset+1] = oc.g*255;
				pRect[offset+2] = oc.b*255;
			}
		}
	}
		
	texture->UnlockRect(0);
	texture->GenerateMipSubLevels();
	return texture;
}


//Create a Cellular Automata 3C Texture
LPDIRECT3DTEXTURE9 CreateCellular3CTextureNoise(IDirect3DDevice9* d3dDevice, Rule3C rule, int rfl, int texscale, float hue, float saturation, float lightness, float noise)
{
	Cellular2D3C ca;
	LPDIRECT3DTEXTURE9 texture;
	D3DLOCKED_RECT lr;

	ca.InitCellular(texscale, texscale);
	ca.Generate(rule, rfl);

	d3dDevice->CreateTexture(texscale, texscale, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, 0);
	texture->LockRect(0, &lr, NULL, 0);
	UCHAR* pRect = (UCHAR*)lr.pBits;
		
	for(int y = 0; y < texscale; y++)
	{
		for(int x = 0; x < texscale; x++)
		{
			if(ca.GetValue(x, y) == 0)
			{
				const int offset = ((y*texscale)+x)*4;
				mColour oc(1.f, 1.f, 1.f);
				oc = RGBtoHSL(oc);
				oc.r = hue;
				oc.g = saturation;
				oc.b += lightness;
				oc = clamp(HSLtoRGB(oc) + (qNoise2D(x, y, rand()) * noise));
				pRect[offset] = oc.r*255;
				pRect[offset+1] = oc.g*255;
				pRect[offset+2] = oc.b*255;
			}

			if(ca.GetValue(x, y) == 1)
			{
				const int offset = ((y*texscale)+x)*4;
				mColour oc(0.5f, 0.5f, 0.5f);
				oc = RGBtoHSL(oc);
				oc.r = hue;
				oc.g = saturation;
				oc.b += lightness;
				oc = clamp(HSLtoRGB(oc) + (qNoise2D(x, y, rand()) * noise));
				pRect[offset] = oc.r*255;
				pRect[offset+1] = oc.g*255;
				pRect[offset+2] = oc.b*255;
			}

			if(ca.GetValue(x, y) == 2)
			{
				const int offset = ((y*texscale)+x)*4;
				mColour oc(0.f, 0.f, 0.f);
				oc = RGBtoHSL(oc);
				oc.r = hue;
				oc.g = saturation;
				oc.b += lightness;
				oc = clamp(HSLtoRGB(oc) + (qNoise2D(x, y, rand()) * noise));
				pRect[offset] = oc.r*255;
				pRect[offset+1] = oc.g*255;
				pRect[offset+2] = oc.b*255;
			}
		}
	}
		
	texture->UnlockRect(0);
	texture->GenerateMipSubLevels();
	return texture;
}


//Create a Cellular Automata 2C Texture
LPDIRECT3DTEXTURE9 CreateCellular2CTextureNoise(IDirect3DDevice9* d3dDevice, Rule2C rule, int rfl, int texscale, float hue, float saturation, float lightness, float noise)
{
	Cellular2D2C ca;
	LPDIRECT3DTEXTURE9 texture;
	D3DLOCKED_RECT lr;

	ca.InitCellular(texscale, texscale);
	ca.Generate(rule, rfl);

	d3dDevice->CreateTexture(texscale, texscale, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, 0);
	texture->LockRect(0, &lr, NULL, 0);
	UCHAR* pRect = (UCHAR*)lr.pBits;
		
	for(int y = 0; y < texscale; y++)
	{
		for(int x = 0; x < texscale; x++)
		{
			if(ca.GetValue(x, y) == false)
			{
				const int offset = ((y*texscale)+x)*4;
				mColour oc(1.f, 1.f, 1.f);
				oc = RGBtoHSL(oc);
				oc.r = hue;
				oc.g = saturation;
				oc.b += lightness;
				oc = clamp(HSLtoRGB(oc) + (qNoise2D(x, y, rand()) * noise));
				pRect[offset] = oc.r*255;
				pRect[offset+1] = oc.g*255;
				pRect[offset+2] = oc.b*255;
			}

			if(ca.GetValue(x, y) == true)
			{
				const int offset = ((y*texscale)+x)*4;
				mColour oc(0.f, 0.f, 0.f);
				oc = RGBtoHSL(oc);
				oc.r = hue;
				oc.g = saturation;
				oc.b += lightness;
				oc = clamp(HSLtoRGB(oc) + (qNoise2D(x, y, rand()) * noise));
				pRect[offset] = oc.r*255;
				pRect[offset+1] = oc.g*255;
				pRect[offset+2] = oc.b*255;
			}
		}
	}
		
	texture->UnlockRect(0);
	texture->GenerateMipSubLevels();
	return texture;
}













