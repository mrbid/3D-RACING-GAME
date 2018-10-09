/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
	
	This produces 1D and 2D Cellular Automata in
	2 Colours and 3 Colours.
	
	Rule Containers
	 - Rule2C
	 - Rule3C
	 
	Classes
	 - Cellular1D2C
	 - Cellular1D3C
	 - Cellular2D2C
	 - Cellular2D3C
	 - CellularRandomGaussian
	 
	Functions
	  - CellularRandom2C(min, max)
	  - CellularRandom3C(min, max)
	  - CharToBin() //Char to Binary (Base 2)
	  - IntToBase(); //Int to Base(x)

	DirectX Functions
	 - CreateCellular2CTexture()
	 - CreateCellular3CTexture()
	 - CreateCellular2CTextureNoise()
	 - CreateCellular3CTextureNoise()
*/

#ifndef CELLULARAUTOMATA_H
#define CELLULARAUTOMATA_H

#include "precom.h"
#include "Random.h"


//Both 2 Colour and 3 Colour
#define RFL_NULL 0
#define RFL_RAND10 1
#define RFL_1CENTER 2

//Just 3 Colour
#define RFL_RAND123 3
#define RFL_2CENTER 4


//CharToBin
MP_INLINE void CharToBin(char *dst, unsigned char value)
{
   for(unsigned char bit = 1 << (CHAR_BIT - 1); bit; bit >>= 1)
   {
      *dst++ = value & bit ? '1' : '0';
   }
   *dst = '\0';
}

//Convert Integer to specified base
MP_INLINE int IntToBase(int number, int base, char* out)
{
	if(number == 0){return 0;}
	const int size = int(log10((float)number) / log10((float)base)); //Why no log10(int)?
	for(int quotient = number, i = size; quotient > 0; quotient = quotient / base, i--)
	{
		out[i] = quotient % base;
	}
	return size;
}


//Rule Containers
struct Rule2C
{
	Rule2C(char rule)
	{
		char binrule[9];
		CharToBin(binrule, rule);
		for(int i = 0; i < 8; i++){r[i] = binrule[i] == 49 ? true : false;}
	}
	
	Rule2C(bool r1, bool r2, bool r3, bool r4, bool r5, bool r6, bool r7, bool r8)
	{
		r[0] = r1, r[1] = r2, r[2] = r3, r[3] = r4, r[4] = r5, r[5] = r6, r[6] = r7, r[7] = r8;
	}
	
	bool r[8];
};

struct Rule3C
{
	Rule3C(int rule)
	{
		char baserule[8];
		memset(&baserule, 0x00, sizeof(baserule));
		const int offset = 6 - IntToBase(rule, 3, baserule);
		if(offset != 0){for(int i = 0; i <= offset; i++){r[i] = 0;}}
		for(int i = offset; i < 7; i++){r[i] = baserule[i-offset];}
	}
	
	Rule3C(char r1, char r2, char r3, char r4, char r5, char r6, char r7)
	{
		r[0] = r1, r[1] = r2, r[2] = r3, r[3] = r4, r[4] = r5, r[5] = r6, r[6] = r7;
	}
	
	char r[7];
};


//2D Cellular Grid Struct (2 Colours)
class Cellular2D2C
{
public:
	//Init
	MP_INLINE void InitCellular(int w, int h)
	{
		m_grid_w = w, m_grid_h = h;
		
		//New 2D Array
		m_grid = new bool*[m_grid_w];
		for(int i = 0; i < m_grid_w; i++)
		{
			m_grid[i] = new bool[m_grid_h];
		}
		
		//Clear Array
		for(int y = 0; y < m_grid_h; y++)
		{
			for(int x = 0; x < m_grid_w; x++)
			{
				m_grid[x][y] = false;	
			}
		}
	}
	
	//Destructor
	~Cellular2D2C()
	{
		//Delete 2D Array
		for(int i = 0; i < m_grid_w; i++){delete m_grid[i];}
		delete m_grid;
	}
	
	//Accessors
	MP_INLINE bool GetValue(int x, int y){return m_grid[x][y];}
	MP_INLINE void SetValue(int x, int y, bool v){m_grid[x][y] = v;}
	MP_INLINE int GetGridWidth(){return m_grid_w;}
	MP_INLINE int GetGridHeight(){return m_grid_h;}
	
	//Reset Grid
	MP_INLINE void Clear()
	{
		for(int y = 0; y < m_grid_h; y++){
			for(int x = 0; x < m_grid_w; x++){m_grid[x][y] = false;}}
	}
	
	//Generate Cellular Automata 2C
	MP_INLINE void Generate(Rule2C rule, int rfl);
		
private:
	bool **m_grid;
	int m_grid_w;
	int m_grid_h;
};


//2D Cellular Grid Struct (3 Colours)
class Cellular2D3C
{
public:
	//Init
	MP_INLINE void InitCellular(int w, int h)
	{
		m_grid_w = w, m_grid_h = h;
		
		//New 2D Array
		m_grid = new char*[m_grid_w];
		for(int i = 0; i < m_grid_w; i++)
		{
			m_grid[i] = new char[m_grid_h];
		}
		
		//Clear Array
		for(int y = 0; y < m_grid_h; y++)
		{
			for(int x = 0; x < m_grid_w; x++)
			{
				m_grid[x][y] = 0;	
			}
		}
	}
	
	//Destructor
	~Cellular2D3C()
	{
		//Delete 2D Array
		for(int i = 0; i < m_grid_w; i++){delete m_grid[i];}
		delete m_grid;
	}
	
	//Accessors
	MP_INLINE char GetValue(int x, int y){return m_grid[x][y];}
	MP_INLINE void SetValue(int x, int y, char v){m_grid[x][y] = v;}
	MP_INLINE int GetGridWidth(){return m_grid_w;}
	MP_INLINE int GetGridHeight(){return m_grid_h;}
	
	//Reset Grid
	MP_INLINE void Clear()
	{
		for(int y = 0; y < m_grid_h; y++){
			for(int x = 0; x < m_grid_w; x++){m_grid[x][y] = 0;}}
	}
	
	//Generate Cellular Automata 3C
	void Generate(Rule3C rule, int rfl);
		
private:
	char **m_grid;
	int m_grid_w;
	int m_grid_h;
};


//1D Cellular Struct (2 Colours)
class Cellular1D2C
{
public:
	//Init
	MP_INLINE void InitCellular(int size)
	{
		m_array_len = size;
		m_array = new bool[size];
		for(int i = 0; i < m_array_len; i++){m_array[i] = false;}
	}
	
	//Destructor
	~Cellular1D2C(){delete m_array;}
	
	//Accessors
	MP_INLINE bool GetValue(int x) const{return m_array[x];}
	MP_INLINE void SetValue(int x, bool v){m_array[x] = v;}
	MP_INLINE int GetArrayLength() const{return m_array_len;}
	
	//Reset array
	MP_INLINE void Clear(){for(int i = 0; i < m_array_len; i++){m_array[i] = false;}}
	
	//Generate 1D Cellular Automata with 2 Colours
	void Generate(Rule2C rule, int rfl);
	
private:
	bool* m_array;
	int m_array_len;
};


//1D Cellular Struct (3 Colours)
class Cellular1D3C
{
public:
	//Init
	MP_INLINE void InitCellular(int size)
	{
		m_array_len = size;
		m_array = new char[size];
		for(int i = 0; i < m_array_len; i++){m_array[i] = 0;}
	}
	
	//Destructor
	~Cellular1D3C(){delete m_array;}
	
	//Accessors
	MP_INLINE char GetValue(int x) const{return m_array[x];}
	MP_INLINE void SetValue(int x, char v){m_array[x] = v;}
	MP_INLINE int GetArrayLength() const{return m_array_len;}
	
	//Reset Array
	MP_INLINE void Clear(){for(int i = 0; i < m_array_len; i++){m_array[i] = 0;}}
	
	//Generate 1D Cellular Automata with 2 Colours
	void Generate(Rule3C rule, int rfl);
	
private:
	char* m_array;
	int m_array_len;
};


//Cellular Random Class
class CellularRandomGaussian
{
public:
	//Init
	MP_INLINE void InitCellularRandom(int archive_size, int width, int height, int rfl)
	{
		m_archivesize = archive_size;
		m_grid_w = width;
		m_grid_h = height;
		
		//Create array of cellular automata
		if(m_cellarchive == NULL){m_cellarchive = new Cellular2D2C[m_archivesize];}
		
		//Init Archive
		for(int i = 0; i < m_archivesize; i++)
		{
			m_cellarchive[i].InitCellular(m_grid_w, m_grid_h);
			m_cellarchive[i].Generate(RandomRule(), rfl);
		}
	}
	
	//Destructor
	~CellularRandomGaussian(){delete m_cellarchive;}
	
	//Get a random rule from 10 predefined rules that are good for sourcing random numbers.
	Rule2C RandomRule()
	{
		const int r = qRand(0, 10);
		if(r == 0){return Rule2C(0,1,0,1,1,0,1,0);}
		if(r == 1){return Rule2C(0,1,1,1,1,1,1,0);}
		if(r == 2){return Rule2C(1,0,0,0,0,0,0,1);}
		if(r == 3){return Rule2C(1,0,0,0,1,0,0,1);}
		if(r == 4){return Rule2C(0,1,1,0,1,1,1,0);}
		if(r == 5){return Rule2C(0,0,0,1,1,1,1,0);}
		if(r == 6){return Rule2C(0,1,0,1,0,1,1,0);}
		if(r == 7){return Rule2C(0,0,1,0,1,1,0,1);}
		if(r == 8){return Rule2C(0,1,1,1,1,1,0,0);}
		if(r == 9){return Rule2C(1,0,0,1,0,0,1,0);}
		return Rule2C(qRandBool(),qRandBool(),qRandBool(),qRandBool(),qRandBool(),qRandBool(),qRandBool(),qRandBool());
	}
	
	//Get Random Number
	MP_INLINE int GetRandomGaussian() const
	{
		int ret = 0; //generated number
		const int cap = qRand(0, m_archivesize); //cell archive pos
		const int cah = qRand(0, m_grid_h); //cell archive height pos
		
		for(int i = 0; i < m_grid_w; i++)
		{
			ret += m_cellarchive[cap].GetValue(i, cah) ? 1 : 0;
		}
		
		return ret;
	}
	
private:
	Cellular2D2C *m_cellarchive;
	int m_archivesize;
	int m_grid_w;
	int m_grid_h;
};


//Return a Cellular Random
inline int CellularRandom2C(int min, int max)
{
	int ret = 0;
	
	Cellular1D2C ra;
    ra.InitCellular(max-min);
    ra.Generate(Rule2C( qRandBool(),
						qRandBool(),
						qRandBool(),
						qRandBool(),
						qRandBool(),
						qRandBool(),
						qRandBool(),
						qRandBool() ), qRand(1, 3));
    
    for(int i = 0; i < ra.GetArrayLength(); i++){ret += ra.GetValue(i) ? 1 : 0;}

	const int r = min+ret;
	return r > max ? max : r;
}

//Return a Cellular Random
inline int CellularRandom3C(int min, int max)
{
	int ret = 0;
	
	Cellular1D3C ra;
    ra.InitCellular(max-min);
    ra.Generate(Rule3C( qRand(0, 3),
						qRand(0, 3),
						qRand(0, 3),
						qRand(0, 3),
						qRand(0, 3),
						qRand(0, 3),
						qRand(0, 3) ), qRand(1, 5));
    
    for(int i = 0; i < ra.GetArrayLength(); i++){ret += ra.GetValue(i);}

	const int r = min+ret;
	return r > max ? max : r;
}

//Create a Cellular Automata 3C Texture
LPDIRECT3DTEXTURE9 CreateCellular3CTexture(IDirect3DDevice9* d3dDevice,
										   Rule3C rule,
										   int rfl,
										   int texscale,
										   float hue,
										   float saturation,
										   float lightness);

//Create a Cellular Automata 2C Texture
LPDIRECT3DTEXTURE9 CreateCellular2CTexture(IDirect3DDevice9* d3dDevice,
										   Rule2C rule,
										   int rfl,
										   int texscale,
										   float hue,
										   float saturation,
										   float lightness);

//Create a Cellular Automata 3C Texture
LPDIRECT3DTEXTURE9 CreateCellular3CTextureNoise(IDirect3DDevice9* d3dDevice,
											    Rule3C rule,
											    int rfl,
											    int texscale,
											    float hue,
											    float saturation,
											    float lightness,
												float noise);

//Create a Cellular Automata 2C Texture
LPDIRECT3DTEXTURE9 CreateCellular2CTextureNoise(IDirect3DDevice9* d3dDevice,
											    Rule2C rule,
											    int rfl,
											    int texscale,
											    float hue,
											    float saturation,
											    float lightness,
												float noise);

#endif




