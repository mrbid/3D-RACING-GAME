/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/

	TODO:
	Prevent the same textures being stored in memory multiple times.
	Prevent the same models being stored in memory multiple times.

	I have decided against this TODO now because each car needs it's
	own customizable texture, and mesh incase we add car damage.
*/

#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include "precom.h"

#include "MathLib.h"
#include "Collision.h"

//Typedef to make things look nice
typedef int pMODEL;
typedef int pTEXTURE;
#define NULL_MODEL -1

//X Model Struct
struct XMODEL
{

	//Constructor
	XMODEL() : mesh(NULL), materials(NULL), totalmaterials(0) {}

	//Mesh
	LPD3DXMESH mesh;

	//Materials
	D3DMATERIAL9* materials;
	DWORD totalmaterials;

	//Texture ID
	pTEXTURE texture;

	//Bounding Objects
	coll::Sphere spherebound;
	coll::AABox aaboxbound;

};

//X Texture Struct
struct XTEXTURE
{

	//Constructor
	XTEXTURE() : diffuse(NULL), specular(NULL), normal(NULL), hasnorm(NULL), hasspec(NULL) {}

	//Set Texture
	void SetTexture(pTEXTURE id);

	//Variables
	LPDIRECT3DTEXTURE9* diffuse;
	LPDIRECT3DTEXTURE9* normal;
	LPDIRECT3DTEXTURE9* specular;
	bool *hasnorm, *hasspec;
	std::string path;

};

//ModelInfo struct
struct ModelInfo
{
	~ModelInfo()
	{
		if(VertBuff != NULL)
			delete [] VertBuff;

		if(IndexBuff != NULL)
			delete [] IndexBuff;
	}

	int NumVerts;
	int NumIndex;
	int NumTriangles;
	vec3::Vector3* VertBuff;
	int* IndexBuff;
};

//Content Manager Class
class ContentManager
{
public:

	//Return Singleton Instance
	static ContentManager& Inst()
	{
		static ContentManager singleton;
		return singleton;
	}

	//Destructor
	~ContentManager();

	//Init Content Manager
	void Init(IDirect3DDevice9* dev);

	//Renders Mesh of Model
	void RenderModel(pMODEL modelid);

	//Load a DrectX Model (.x)
	pMODEL LoadXModel(std::string path, bool loadtextures, bool generatemips, bool useexisting);

	//Set's XMODEL texture
	void SetDiffuse(pMODEL modelid, pTEXTURE diffuseid, LPDIRECT3DTEXTURE9 tex);
	void LoadDiffuse(pMODEL modelid, pTEXTURE diffuseid, std::string file);
	void SetNormal(pMODEL modelid, pTEXTURE normalid, LPDIRECT3DTEXTURE9 tex);
	void LoadNormal(pMODEL modelid, pTEXTURE normalid, std::string file);
	void SetSpecular(pMODEL modelid, pTEXTURE specularid, LPDIRECT3DTEXTURE9 tex);
	void LoadSpecular(pMODEL modelid, pTEXTURE specularid, std::string file);

	//Get a DirectX Model from the Content Manager
	XMODEL* GetXModel(pMODEL modelid);
	XTEXTURE* GetXTexture(pTEXTURE textureid);

	//Scale Mesh
	void meshScale(pMODEL modelid, float scale);
	void GenerateMipLevels(pMODEL modelid, pTEXTURE mapid);
	void GenerateMipLevels(XTEXTURE* tex, pTEXTURE mapid);

	//Get's model info from ID
	void GetXModelInfo(pMODEL modelid, ModelInfo* xi);

	//Create Bounding Shapes for Models
	coll::AABox CreateAABox(LPD3DXMESH mesh);
	void GetSphereBound(LPD3DXMESH mesh, float* radius, vec3::Vector3* center);
	coll::Sphere GetSphereBound(LPD3DXMESH mesh);

private:

	ContentManager(){} //Constructor
	ContentManager(const ContentManager&); //Prevent Copy
	ContentManager& operator=(const ContentManager&); //Prevent Assignment

	//Get Texture Paths
	void GetNormalPath(char* normalpath, char* diffusepath);
	void GetSpecularPath(char* specularpath, char* diffusepath);
	bool PathExist(const char* path);
	pTEXTURE FindTexture(const char* path);
	void SetEffectParameters(pTEXTURE id, int i);

	//Array of XMODELS
	std::vector<XMODEL> m_xmodels;

	//Array of XTEXTURES
	std::vector<XTEXTURE> m_xtextures;

	//Pointer to D3D Device
	IDirect3DDevice9* d3dDevice;

	//The game only uses one FX file to minimize pipeline changes
	ID3DXEffect* m_pEffect;

};

MP_INLINE void ContentManager::SetDiffuse(pMODEL modelid, pTEXTURE diffuseid, LPDIRECT3DTEXTURE9 tex)
{
	m_xtextures[m_xmodels[modelid].texture].diffuse[diffuseid] = tex;
}

MP_INLINE void ContentManager::LoadDiffuse(pMODEL modelid, pTEXTURE diffuseid, std::string file)
{
	D3DXCreateTextureFromFile(d3dDevice, file.c_str(), &m_xtextures[m_xmodels[modelid].texture].diffuse[diffuseid]);
}

MP_INLINE void ContentManager::SetNormal(pMODEL modelid, pTEXTURE normalid, LPDIRECT3DTEXTURE9 tex)
{
	m_xtextures[m_xmodels[modelid].texture].normal[normalid] = tex;
	m_xtextures[m_xmodels[modelid].texture].hasnorm[normalid] = true;
}

MP_INLINE void ContentManager::LoadNormal(pMODEL modelid, pTEXTURE normalid, std::string file)
{
	D3DXCreateTextureFromFile(d3dDevice, file.c_str(), &m_xtextures[m_xmodels[modelid].texture].normal[normalid]);
	m_xtextures[m_xmodels[modelid].texture].hasnorm[normalid] = true;
}

MP_INLINE void ContentManager::SetSpecular(pMODEL modelid, pTEXTURE specularid, LPDIRECT3DTEXTURE9 tex)
{
	m_xtextures[m_xmodels[modelid].texture].specular[specularid] = tex;
	m_xtextures[m_xmodels[modelid].texture].hasspec[specularid] = true;
}

MP_INLINE void ContentManager::LoadSpecular(pMODEL modelid, pTEXTURE specularid, std::string file)
{
	D3DXCreateTextureFromFile(d3dDevice, file.c_str(), &m_xtextures[m_xmodels[modelid].texture].specular[specularid]);
	m_xtextures[m_xmodels[modelid].texture].hasspec[specularid] = true;
}

/*MP_INLINE void ContentManager::LoadAlphaMapTexture(int modelid, int textureid, std::string file)
{
	D3DXCreateTextureFromFileExA(d3dDevice, file.c_str(), D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &m_xmodels[modelid].textures[textureid]);
}*/

MP_INLINE XMODEL* ContentManager::GetXModel(pMODEL modelid)
{
	return &m_xmodels[modelid];
}

MP_INLINE XTEXTURE* ContentManager::GetXTexture(pTEXTURE textureid)
{
	return &m_xtextures[textureid];
}

MP_INLINE void ContentManager::GenerateMipLevels(pMODEL modelid, pTEXTURE mapid)
{
	if(m_xtextures[m_xmodels[modelid].texture].diffuse[mapid] != NULL)
		m_xtextures[m_xmodels[modelid].texture].diffuse[mapid]->GenerateMipSubLevels();

	if(m_xtextures[m_xmodels[modelid].texture].hasnorm[mapid] == true)
		m_xtextures[m_xmodels[modelid].texture].normal[mapid]->GenerateMipSubLevels();

	if(m_xtextures[m_xmodels[modelid].texture].hasspec[mapid] == true)
		m_xtextures[m_xmodels[modelid].texture].specular[mapid]->GenerateMipSubLevels();
}

MP_INLINE void ContentManager::GenerateMipLevels(XTEXTURE* tex, pTEXTURE mapid)
{
	if(tex->diffuse[mapid] != NULL)
		tex->diffuse[mapid]->GenerateMipSubLevels();

	if(tex->hasnorm[mapid] == true)
		tex->normal[mapid]->GenerateMipSubLevels();

	if(tex->hasspec[mapid] == true)
		tex->specular[mapid]->GenerateMipSubLevels();
}

//Return Instance to Singleton
MP_INLINE ContentManager& ContentManager(){return ContentManager::Inst();}

#endif





