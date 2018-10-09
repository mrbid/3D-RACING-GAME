/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#include "precom.h"
#include "ContentManager.h"
#include "D3DRenderer.h"
#include "CellularAutomata.h"
using namespace coll;


//Destructor
ContentManager::~ContentManager()
{
	//Release Textures
	for(unsigned int i = 0; i < m_xtextures.size(); ++i)
	{
		for(unsigned int i2 = 0; i2 < m_xmodels[i].totalmaterials-1; ++i2)
		{
			if(m_xtextures[i].diffuse[i2] != NULL)
				m_xtextures[i].diffuse[i2]->Release();

			if(m_xtextures[i].hasnorm != NULL)
				if(m_xtextures[i].hasnorm[i2] != NULL)
					m_xtextures[i].normal[i2]->Release();

			if(m_xtextures[i].hasspec != NULL)
				if(m_xtextures[i].hasspec[i2] != NULL)
					m_xtextures[i].specular[i2]->Release();
		}

		if(m_xtextures[i].hasnorm != NULL)
			delete [] m_xtextures[i].hasnorm;

		if(m_xtextures[i].hasspec != NULL)
			delete [] m_xtextures[i].hasspec;
	}
	m_xtextures.clear();

	//Release Models
	for(std::vector<XMODEL>::iterator iter = m_xmodels.begin(); iter < m_xmodels.end(); ++iter)
	{
        iter->mesh->Release();
	}
	m_xmodels.clear();

	//Release Effect
	//m_pEffect->Release();
}

//Init Content Manager
void ContentManager::Init(IDirect3DDevice9* dev)
{
	//Set Device Pointer
	d3dDevice = dev;

	//Load Effect File
	/*if(FAILED(D3DXCreateEffectFromFile( d3dDevice, "models/fx/lol.fx",
										NULL, // CONST D3DXMACRO* pDefines,
										NULL, // LPD3DXINCLUDE pInclude,
										D3DXSHADER_NO_PRESHADER, NULL, &m_pEffect, NULL )))
	{
		MessageBox(0, "Error FX Could not be loaded.", "Error", MB_OK | MB_TOPMOST);
		exit(0);
	}*/
}

//Set Texture
void XTEXTURE::SetTexture(pTEXTURE id)
{
	//Set Diffuse
	RenderSystem().SetTexture(0, diffuse[id]);

	//Set Specular
	if(hasspec[id] == true)
	{
		RenderSystem().SetTexture(1, specular[id]);
	}
	else
	{
		RenderSystem().SetTexture(1, NULL);
	}

	//Set Normal
	if(hasnorm[id] == true)
	{
		//
	}
	else
	{
		//
	}
}

//Get Normal Path
void ContentManager::GetNormalPath(char* normalpath, char* diffusepath)
{
	for(unsigned int i = 0, i2 = 0; i < strlen(diffusepath); ++i)
	{
		if(diffusepath[i] != '.')
		{
			normalpath[i2] = diffusepath[i];
			i2++;
		}
		else
		{
			normalpath[i2] = '_';
			normalpath[i2+1] = 'n';
			normalpath[i2+2] = 'o';
			normalpath[i2+3] = 'r';
			normalpath[i2+4] = 'm';
			normalpath[i2+5] = 'a';
			normalpath[i2+6] = 'l';
			normalpath[i2+7] = '.';
			i2 += 8;
		}
	}
}

//Get Specular Path
void ContentManager::GetSpecularPath(char* specularpath, char* diffusepath)
{
	for(unsigned int i = 0, i2 = 0; i < strlen(diffusepath); ++i)
	{
		if(diffusepath[i] != '.')
		{
			specularpath[i2] = diffusepath[i];
			i2++;
		}
		else
		{
			specularpath[i2] = '_';
			specularpath[i2+1] = 's';
			specularpath[i2+2] = 'p';
			specularpath[i2+3] = 'e';
			specularpath[i2+4] = 'c';
			specularpath[i2+5] = 'u';
			specularpath[i2+6] = 'l';
			specularpath[i2+7] = 'a';
			specularpath[i2+8] = 'r';
			specularpath[i2+9] = '.';
			i2 += 10;
		}
	}
}

//Checks if a path exists
bool ContentManager::PathExist(const char* path)
{
	FILE* exist = fopen(path, "r");
	if(exist != NULL)
	{
		fclose(exist);
		return true;
	}

	return false;
}



//Loads a DirectX Model (.x)
pMODEL ContentManager::LoadXModel(std::string path, bool loadtextures, bool generatemips, bool useexisting)
{
	XMODEL nxm;
	XTEXTURE nxt;
	LPD3DXBUFFER pD3DXMtrlBuffer;

	//Load Mesh
	LPD3DXBUFFER pAdjacencyBuffer;
	if(D3DXLoadMeshFromX(path.c_str(), D3DPOOL_DEFAULT | D3DUSAGE_WRITEONLY,
											  d3dDevice, &pAdjacencyBuffer,
										   	  &pD3DXMtrlBuffer, NULL, &nxm.totalmaterials,
											  &nxm.mesh ) != D3D_OK)
	{
		MessageBox(0, path.c_str(), "Failed to load X File.", MB_OK | MB_TOPMOST);
		exit(0);
	}
	generatemips=false;

	//Calculate Sphere Bound
	nxm.spherebound = GetSphereBound(nxm.mesh);
	nxm.aaboxbound = CreateAABox(nxm.mesh);

	//Load Materials
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	//Init Material Buffers
	nxm.materials = new D3DMATERIAL9[nxm.totalmaterials];
	nxt.diffuse = new LPDIRECT3DTEXTURE9[nxm.totalmaterials];
	nxt.normal = new LPDIRECT3DTEXTURE9[nxm.totalmaterials];
	nxt.specular = new LPDIRECT3DTEXTURE9[nxm.totalmaterials];
	nxt.hasnorm = new bool[nxm.totalmaterials];
	nxt.hasspec = new bool[nxm.totalmaterials];
	for(unsigned int i = 0; i < nxm.totalmaterials; ++i)
	{
		nxt.hasnorm[i] = false;
		nxt.hasspec[i] = false;
	}

	//Load Materials and Textures
	for(DWORD i = 0; i < nxm.totalmaterials; ++i)
	{
		//Load material
		nxm.materials[i] = d3dxMaterials[i].MatD3D;
		nxm.materials[i].Ambient = nxm.materials[i].Diffuse; //TODO: Hack
		/*nxm.materials[i].Emissive.r = 0.f;
		nxm.materials[i].Emissive.g = 0.f;
		nxm.materials[i].Emissive.b = 0.f;
		nxm.materials[i].Emissive.a = 0.f;
		nxm.materials[i].Specular.r = 1.0f;
		nxm.materials[i].Specular.g = 1.0f;
		nxm.materials[i].Specular.b = 1.0f;
		nxm.materials[i].Specular.a = 1.0f;
		nxm.materials[i].Power = 50.f;*/

		//Null Textures
		nxt.diffuse[i] = NULL;
		nxt.normal[i] = NULL;
		nxt.specular[i] = NULL;

		//Load Textures?
		if(loadtextures == true)
		{
			//Is Diffuse Avalible?
			if(d3dxMaterials[i].pTextureFilename != NULL && lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
			{
				std::string texpath = "textures/";
				texpath.append(d3dxMaterials[i].pTextureFilename);

				//If path doesnt exist check if the TGA does
				if(PathExist(texpath.c_str()) == false)
				{
					texpath[texpath.size()-3] = 'T';
					texpath[texpath.size()-2] = 'G';
					texpath[texpath.size()-1] = 'A';
				}

				D3DXCreateTextureFromFile(d3dDevice, texpath.c_str(), &nxt.diffuse[i]);

				//Check if texture is already loaded
				if(useexisting == true)
				{
					const int tex = FindTexture(texpath.c_str());
					if(tex != -1)
					{
						nxm.texture = tex;
						m_xmodels.push_back(nxm);
						return m_xmodels.size()-1;
					}
				}

				//Texture doesnt exist!
				nxt.path = texpath;

				//Get Normal Map Path
				/*char normalpath[256];
				memset(&normalpath, 0x00, sizeof(normalpath));
				GetNormalPath(normalpath, d3dxMaterials[i].pTextureFilename);

				//Get Specular Map Path
				char specularpath[256];
				memset(&specularpath, 0x00, sizeof(specularpath));
				GetNormalPath(specularpath, d3dxMaterials[i].pTextureFilename);

				//If normal map exists
				if(PathExist(normalpath) == true)
				{
					D3DXCreateTextureFromFileA(d3dDevice, normalpath, &nxt.normal[i]);
					nxt.hasnorm[i] = true;
				}
				
				//If specular map exists
				if(PathExist(specularpath) == true)
				{
					D3DXCreateTextureFromFileA(d3dDevice, specularpath, &nxt.specular[i]);
					nxt.hasspec[i] = true;
				}

				//Generate Mip Levels?
				if(generatemips == true)
					GenerateMipLevels(&nxt, i);*/
			}
		}
	}

	//nxt.diffuse[0] = CreateCellular3CTextureNoise(RenderSystem().GetDevice(), Rule3C(qRand(0, 2187)), 3, 32, qRandFloat(0.000f, 1.000f), qRandFloat(0.000f, 1.000f), qRandFloat(-0.400f, 0.400f), qRandFloat(0.000f, 0.500f));

	//Release Material Buffer
	pD3DXMtrlBuffer->Release();

	//Add to model and texture array
	m_xtextures.push_back(nxt);
	nxm.texture = m_xtextures.size()-1;
	m_xmodels.push_back(nxm);
	return m_xmodels.size()-1;
}

//Find Existing Texture in Memory
pTEXTURE ContentManager::FindTexture(const char* path)
{
	for(unsigned int i = 0; i < m_xtextures.size()-1; ++i)
	{
		if(m_xtextures[i].path.compare(path) == 0)
			return i;
	}

	return -1;
}


//Set Shader Parameters
void ContentManager::SetEffectParameters(pTEXTURE id, int i)
{
    /*m_pEffect->SetMatrix("worldViewProjectionMatrix", &worldViewProjectionMatrix);
    m_pEffect->SetValue("light.specular", g_light.specular, sizeof(g_light.specular));;
    m_pEffect->SetFloat("material.shininess", g_material.shininess);
    m_pEffect->SetTexture("colorMapTexture", g_disableColorMapTexture ? g_pNullTexture : g_pColorMap);*/
	

	//Calc Matricies
	/*D3DXMATRIXA16 projection, world, view;
	d3dDevice->GetTransform(D3DTS_PROJECTION, &projection);
	d3dDevice->GetTransform(D3DTS_WORLD, &world);
	d3dDevice->GetTransform(D3DTS_VIEW, &view);

	D3DXMATRIXA16 worldinverse, viewinverse;
	D3DXMatrixInverse(&worldinverse, NULL, &world);
	D3DXMatrixInverse(&viewinverse, NULL, &view);

	D3DXMATRIXA16 worldinversetranspose;
	D3DXMatrixTranspose(&worldinversetranspose, &worldinverse);




	D3DXMATRIXA16 worldViewProjectionMatrix = world * view * projection;
	D3DXMATRIXA16 worldInverseTransposeMatrix;
	D3DXVECTOR3 campos(0,0,0);
	float g_sceneAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	Light g_light =
	{
		Light::DIR_LIGHT,
		0.0f, 0.0f, 1.0f,                               // dir
		campos.x, campos.y, campos.z,    // pos
		1.0f, 1.0f, 1.0f, 0.0f,                         // ambient
		1.0f, 1.0f, 1.0f, 0.0f,                         // diffuse
		1.0f, 1.0f, 1.0f, 0.0f,                         // specular
		LIGHT_SPOT_INNER_CONE,                          // spotInnerCone
		LIGHT_SPOT_OUTER_CONE,                          // spotOuterCone
		LIGHT_RADIUS                                    // radius
	};


    // Calculate the transpose of the inverse of the world matrix.
    D3DXMatrixInverse(&worldInverseTransposeMatrix, 0, &world);
    D3DXMatrixTranspose(&worldInverseTransposeMatrix, &worldInverseTransposeMatrix);

    // Set the matrices for the shader.
    m_pEffect->SetMatrix("worldMatrix", &world);
    m_pEffect->SetMatrix("worldInverseTransposeMatrix", &worldInverseTransposeMatrix);
    m_pEffect->SetMatrix("worldViewProjectionMatrix", &worldViewProjectionMatrix);

    // Set the camera position.
    m_pEffect->SetValue("cameraPos", &campos, sizeof(campos));

    // Set the scene global ambient term.
    m_pEffect->SetValue("globalAmbient", &g_sceneAmbient, sizeof(g_sceneAmbient));

    // Set the lighting parameters for the shader.
    m_pEffect->SetValue("light.dir", g_light.dir, sizeof(g_light.dir));
    m_pEffect->SetValue("light.pos", g_light.pos, sizeof(g_light.pos));
    m_pEffect->SetValue("light.ambient", g_light.ambient, sizeof(g_light.ambient));
    m_pEffect->SetValue("light.diffuse", g_light.diffuse, sizeof(g_light.diffuse));
    m_pEffect->SetValue("light.specular", g_light.specular, sizeof(g_light.specular));
    m_pEffect->SetFloat("light.spotInnerCone", g_light.spotInnerCone);
    m_pEffect->SetFloat("light.spotOuterCone", g_light.spotOuterCone);
    m_pEffect->SetFloat("light.radius", g_light.radius);

    // Set the material parameters for the shader.
   // m_pEffect->SetValue("material.ambient", g_material.ambient, sizeof(g_material.ambient));
    //m_pEffect->SetValue("material.diffuse", m_xtextures[id].diffuse[i], sizeof(m_xtextures[id].diffuse[i]));
   // m_pEffect->SetValue("material.emissive", g_material.emissive, sizeof(g_material.emissive));
   // m_pEffect->SetValue("material.specular", g_material.specular, sizeof(g_material.specular));
    //m_pEffect->SetFloat("material.shininess", g_material.shininess);

    // Bind the textures to the shader.
    m_pEffect->SetTexture("colorMapTexture", m_xtextures[id].diffuse[i]);
    //m_pEffect->SetTexture("normalMapTexture", m_xtextures[id].diffuse[i]);









	//Set Matricies
	m_pEffect->SetMatrix("ViewInverse", &viewinverse);
	m_pEffect->SetMatrix("World", &world);
	m_pEffect->SetMatrix("WorldInverse", &worldinverse);
	m_pEffect->SetMatrix("WorldInverseTranspose", &worldinversetranspose);
	m_pEffect->SetMatrix("WorldViewProjection", &(world * view * projection));
	
	
	//Set Diffuse Map
	m_pEffect->SetTexture("TextureMap_218", m_xtextures[id].diffuse[i]);

	//Set Specular Map
	if(m_xtextures[id].hasspec[i] == true)
		m_pEffect->SetTexture("TextureMap_8325", m_xtextures[id].specular[i]);

	//Set Bump Map
	if(m_xtextures[id].hasnorm[i] == true)
		m_pEffect->SetTexture("BumpMap_7881", m_xtextures[id].normal[i]);

	//Set CubeMap
	//m_pEffect->SetTexture("environment", "cubemap.dds");

	//Set Fresnel Power
	m_pEffect->SetFloat("FresnelPower.UIMin", 0.f);
	m_pEffect->SetFloat("FresnelPower.UIMax", 100.f);
	m_pEffect->SetFloat("FresnelPower.UIStep ", 0.01f);

	//Set Fresnel Scale
	m_pEffect->SetFloat("FresnelScale.UIMin", 0.f);
	m_pEffect->SetFloat("FresnelScale.UIMax", 100.f);
	m_pEffect->SetFloat("FresnelScale.UIStep ", 0.01f);

	//Set Fresnel Bias
	m_pEffect->SetFloat("FresnelBias.UIMin", -100.f);
	m_pEffect->SetFloat("FresnelBias.UIMax", 100.f);
	m_pEffect->SetFloat("FresnelBias.UIStep ", 0.01f);

	//Some Shiney Stuff
	m_pEffect->SetFloat("UIConst_1590.UIMin", -999.f);
	m_pEffect->SetFloat("UIConst_1590.UIMax", 999.f);
	m_pEffect->SetFloat("UIConst_1590.UIStep ", 0.1f);*/

}

//Render Model
void ContentManager::RenderModel(pMODEL modelid)
{
	//Set FX Shader
	//m_pEffect->SetTechnique(m_pEffect->GetTechniqueByName("Complete"));
	//m_pEffect->SetTechnique(m_pEffect->GetTechniqueByName("NormalMappingDirectionalLighting"));

	//Begin
	//UINT passes;
	//m_pEffect->Begin(&passes,  0);
	
	//Iterate for each FX Shader pass
	//for(UINT i = 0; i < passes; ++i)
	//{
		//Begin Pass
		//m_pEffect->BeginPass(i);

		//Draw Mesh Subset with Materials & Textures
		for(DWORD i = 0; i < m_xmodels[modelid].totalmaterials; ++i)
		{
			RenderSystem().SetMaterial(&m_xmodels[modelid].materials[i]);

			m_xtextures[m_xmodels[modelid].texture].SetTexture(i);
			//SetEffectParameters(m_xmodels[modelid].texture, i);

			m_xmodels[modelid].mesh->DrawSubset(i);

			RenderSystem().SetTexture(0, NULL);
			RenderSystem().SetTexture(1, NULL);
		}

		//End Pass
		//m_pEffect->EndPass();
	//}

	//Unset FX Shader
	//m_pEffect->End();
}

//Get's info from DX model
void ContentManager::GetXModelInfo(pMODEL id, ModelInfo* xi)
{
	//Clone mesh
	LPD3DXMESH m;
    m_xmodels[id].mesh->CloneMeshFVF(0, D3DFVF_XYZ, d3dDevice, &m);

	//Get total number of verticies
	xi->NumVerts = m->GetNumVertices();

	//Get total number of triangles
	xi->NumTriangles = m->GetNumFaces();

	//Get total number of indicies
	xi->NumIndex = xi->NumTriangles*3;

	//Init Info VertexBuffer
	xi->VertBuff = new vec3::Vector3[xi->NumVerts];

	//Init Info IndexBuffer
	xi->IndexBuff = new int[xi->NumIndex];


	//Get Vertex Buffer
	LPDIRECT3DVERTEXBUFFER9 vertbuff;
	m->GetVertexBuffer(&vertbuff);

	D3DXVECTOR3* vec;
	vertbuff->Lock(0, 0, (void**)&vec, 0);

	for(int i = 0; i < xi->NumVerts; ++i)
	{
		xi->VertBuff[i].x = vec[i].x;
		xi->VertBuff[i].y = vec[i].y;
		xi->VertBuff[i].z = vec[i].z;
    }

	vertbuff->Unlock();
	vertbuff->Release();


	//Get Index Buffer
	LPDIRECT3DINDEXBUFFER9 indexbuff;
	m->GetIndexBuffer(&indexbuff);

	WORD* index;
	indexbuff->Lock(0, 0, (void**)&index, 0);

	for(int i = 0; i <xi->NumIndex; ++i)
	{
		xi->IndexBuff[i] = index[i];
    }

	indexbuff->Unlock();
	indexbuff->Release();


	//Release model clone
	m->Release();
}

//Mesh Scale
void ContentManager::meshScale(pMODEL modelid, float scale)
{
	//Vertex Definition
	struct Vertex
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 normal;
	    float tu;
		float tv;

		enum
		{
			VertexFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 
		};
	};

	//Copy Mesh
	LPD3DXMESH newmesh;
	Vertex *pVertex;
	DWORD NUM_VERTICES = m_xmodels[modelid].mesh->GetNumVertices();
	m_xmodels[modelid].mesh->CloneMeshFVF(0, Vertex::VertexFVF, d3dDevice, &newmesh);

		//Access vertex buffer & rescale
		newmesh->LockVertexBuffer( 0, (void**)&pVertex);
		for(unsigned int i = 0; i < NUM_VERTICES; ++i)
			pVertex[i].pos *= scale;
		newmesh->UnlockVertexBuffer();

	m_xmodels[modelid].mesh->Release(); //Release old mesh
	m_xmodels[modelid].mesh = newmesh; //Make old mesh point to new mesh

	//Recalculate Bounds
	m_xmodels[modelid].spherebound = GetSphereBound(m_xmodels[modelid].mesh);
	m_xmodels[modelid].aaboxbound = CreateAABox(m_xmodels[modelid].mesh);
}

//Create AABox from Mesh
AABox ContentManager::CreateAABox(LPD3DXMESH mesh)
{
	AABox ret;
	float iv;

	LPD3DXMESH m;
    if(FAILED(mesh->CloneMeshFVF(0, D3DFVF_XYZ, d3dDevice, &m)))
	{
		ret.m_max = vec3::Vector3(100000.f, 100000.f, 100000.f);
		ret.m_min = vec3::Vector3(-100000.f, -100000.f, -100000.f);
		return ret;
	}

	LPDIRECT3DVERTEXBUFFER9 vertbuff;
	m->GetVertexBuffer(&vertbuff);

	D3DXVECTOR3* vec;
	vertbuff->Lock(0, 0, (void**)&vec, 0);

	//Find Min X
	iv = vec[0].x;
	for(DWORD i = 1; i < m->GetNumVertices(); i++){if(vec[i].x < iv){iv = vec[i].x;}}
	ret.m_min.x = iv;

	//Find Min Y
	iv = vec[0].y;
	for(DWORD i = 1; i < m->GetNumVertices(); i++){if(vec[i].y < iv){iv = vec[i].y;}}
	ret.m_min.y = iv;

	//Find Min Z
	iv = vec[0].z;
	for(DWORD i = 1; i < m->GetNumVertices(); i++){if(vec[i].z < iv){iv = vec[i].z;}}
	ret.m_min.z = iv;

	//Find Max X
	iv = vec[0].x;
	for(DWORD i = 1; i < m->GetNumVertices(); i++){if(vec[i].x > iv){iv = vec[i].x;}}
	ret.m_max.x = iv;

	//Find Max Y
	iv = vec[0].y;
	for(DWORD i = 1; i < m->GetNumVertices(); i++){if(vec[i].y > iv){iv = vec[i].y;}}
	ret.m_max.y = iv;

	//Find Max Z
	iv = vec[0].z;
	for(DWORD i = 1; i < m->GetNumVertices(); i++){if(vec[i].z > iv){iv = vec[i].z;}}
	ret.m_max.z = iv;

	vertbuff->Unlock();
	vertbuff->Release();
	m->Release();

	return ret;
}

//Calculate Mesh Sphere Bound
void ContentManager::GetSphereBound(LPD3DXMESH mesh, float* radius, vec3::Vector3* center)
{
	LPD3DXMESH m;
    if(FAILED(mesh->CloneMeshFVF(0, D3DFVF_XYZ, d3dDevice, &m)))
	{
		*radius = 100000.f;
		return;
	}

	LPDIRECT3DVERTEXBUFFER9 vertbuff;
	m->GetVertexBuffer(&vertbuff);

	D3DXVECTOR3* vec;
	vertbuff->Lock(0, 0, (void**)&vec, 0);

    float xt = 0.0f, yt = 0.0f, zt = 0.0f;
    for(DWORD i = 0; i < m->GetNumVertices(); i++)
	{
		xt += vec[i].x;
		yt += vec[i].y;
		zt += vec[i].z;
    }

	const float NumVerts = 1.0f/m->GetNumVertices();
	*center = vec3::Vector3(xt * NumVerts, yt * NumVerts, zt * NumVerts);

    *radius = 0.f;
    for(DWORD i = 0; i < m->GetNumVertices(); i++)
	{
		const float f = math::isqrt( (vec[i].x - center->x) * (vec[i].x - center->x) +
									 (vec[i].y - center->y) * (vec[i].y - center->y) +
									 (vec[i].z - center->z) * (vec[i].z - center->z));

		if(f > *radius){*radius = f;}
    }

	vertbuff->Unlock();
	vertbuff->Release();
	m->Release();
}

//Calculate Mesh Sphere Bound
Sphere ContentManager::GetSphereBound(LPD3DXMESH mesh)
{
	Sphere ret;

	LPD3DXMESH m;
    if(FAILED(mesh->CloneMeshFVF(0, D3DFVF_XYZ, d3dDevice, &m)))
	{
		ret.radius = 100000.f;
		return ret;
	}

	LPDIRECT3DVERTEXBUFFER9 vertbuff;
	m->GetVertexBuffer(&vertbuff);

	D3DXVECTOR3* vec;
	vertbuff->Lock(0, 0, (void**)&vec, 0);

    float xt = 0.0f, yt = 0.0f, zt = 0.0f;
    for(DWORD i = 0; i < m->GetNumVertices(); i++)
	{
		xt += vec[i].x;
		yt += vec[i].y;
		zt += vec[i].z;
    }

	const float NumVerts = 1.0f/m->GetNumVertices();
	ret.center = vec3::Vector3(xt * NumVerts, yt * NumVerts, zt * NumVerts);

    ret.radius = 0.f;
    for(DWORD i = 0; i < m->GetNumVertices(); i++)
	{
		const float f = math::isqrt( (vec[i].x - ret.center.x) * (vec[i].x - ret.center.x) +
									 (vec[i].y - ret.center.y) * (vec[i].y - ret.center.y) +
									 (vec[i].z - ret.center.z) * (vec[i].z - ret.center.z));

		if(f > ret.radius){ret.radius = f;}
    }

	vertbuff->Unlock();
	vertbuff->Release();
	m->Release();

	return ret;
}




