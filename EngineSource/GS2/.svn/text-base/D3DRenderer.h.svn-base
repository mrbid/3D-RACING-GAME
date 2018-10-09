/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#ifndef D3DRENDERER_H
#define D3DRENDERER_H

#include "precom.h"
#include "MatrixLib.h"
#include "Colours.h"
#include "ContentManager.h"

//Light Type
typedef enum LIGHTTYPE
{
	LIGHT_POINT         = 1,
	LIGHT_SPOT          = 2,
	LIGHT_DIRECTIONAL   = 3
};

//Light Structure
struct LIGHT
{
	LIGHT(){}
	LIGHTTYPE Type;
	clr::mColour4 Diffuse;
	clr::mColour4 Specular;
	clr::mColour4 Ambient;
	vec3::Vector3 Position;
	vec3::Vector3 Direction;
	float Range;
	float Falloff;
	float Attenuation0;
	float Attenuation1;
	float Attenuation2;
	float Theta;
	float Phi;
};

//Point Sprite Structure
struct PointSprite
{
	D3DXVECTOR3 m_pos;
	float m_scale;
	D3DCOLOR m_diffuse;

	void SetPosition(vec3::Vector3 v)
	{
		m_pos.x = v.x, m_pos.y = v.y, m_pos.z = v.z;
	}

	void SetColour(clr::mColour4 c)
	{
		m_diffuse = D3DCOLOR_COLORVALUE(c.r, c.g, c.b, c.a);
	}

	PointSprite() : m_pos(0.0f, 0.0f, 0.0f), m_scale(1.f)
	{
		m_diffuse = D3DCOLOR_COLORVALUE(1,1,1,1);
	}

	enum FVF
	{
		FVF_FLAGS = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE
	};
};

//Direct 3D Renderer
class D3DRenderer
{
public:

	//Return Singleton Instance
	static D3DRenderer& Inst()
	{
		static D3DRenderer singleton;
		return singleton;
	}

	//Destructor
	~D3DRenderer();

	//Init Direct 3D
	void InitD3D(HWND hwnd);
	void SetRenderStates();

	//Return Device pointer
	IDirect3DDevice9* GetDevice();

	//Rendering Functions
	void ClearRender() const;
	bool BeginRender() const;
	bool EndRender() const;
	bool ShowRender() const;

	//Primitive Drawing
	void RenderCube(vec3::Vector3 pos, float scale)
	{
		SetFillModeWireframe();
		SetWorldTransform(mat4::Scale(scale) * GetWorldMatrix());
		m_boxmesh->DrawSubset(0);
		SetFillModeSolid();
	}

	//Material / Texture Functions
	void SetMaterial(D3DMATERIAL9* material) const;
	void SetTexture(int sampler, IDirect3DBaseTexture9* tex) const;
	D3DMATERIAL9 CreateMaterial(clr::mColour4 diffuse, clr::mColour4 ambient, clr::mColour4 specular, clr::mColour4 emissive, float power) const;

	//Matrix Functions
	void SetupProjection(float fov, float aspect, float np, float fp) const;
	void SetWorldTransform(const mat4::MATRIX4& mat) const;
	void SetViewTransform(const mat4::MATRIX4& mat) const;
	mat4::MATRIX4 GetProjectionMatrix() const;
	mat4::MATRIX4 GetWorldMatrix() const;
	mat4::MATRIX4 GetViewMatrix() const;

	//Lighting Functions
	void EnableLight(int id, bool enable) const;
	void SetLight(int id, LIGHT& light) const;
	void SetAmbientLight(int r, int g, int b, int a) const;

	//Set Fill Mode
	void SetFillModeSolid();
	void SetFillModeWireframe();
	void SetFillModePoint();
	
	//Skybox Functions
	void RenderSkybox();
	void InitSkybox(std::string name);
	pMODEL GetSkybox();

	//Particle Functions
	bool InitParticleRenderer(int maxparticles);
	void RenderParticles(PointSprite* particles, int particles_size, IDirect3DBaseTexture9* texture);
	
private:

	D3DRenderer() : d3dObject(NULL), d3dDevice(NULL) {} //Constructor
	D3DRenderer(const D3DRenderer&); //Prevent Copy
	D3DRenderer& operator=(const D3DRenderer&); //Prevent Assignment

	//D3D Object & Device
	IDirect3D9* d3dObject;
	IDirect3DDevice9* d3dDevice;

	//Skybox Model
	pMODEL m_skybox;

	//Particle System Buffer
	LPDIRECT3DVERTEXBUFFER9 m_pointbuffer;
	int m_maxparticles;

	//Box Buffer
	LPD3DXMESH m_boxmesh;

};


MP_INLINE pMODEL D3DRenderer::GetSkybox()
{
	return m_skybox;
}

//Return Device pointer
MP_INLINE IDirect3DDevice9* D3DRenderer::GetDevice()
{
	return d3dDevice;
}

//Clear the Render Buffer
MP_INLINE void D3DRenderer::ClearRender() const
{
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0); //D3DCOLOR_XRGB(0,0,0)
}

//Set Renderer Material
MP_INLINE void D3DRenderer::SetMaterial(D3DMATERIAL9* material) const
{
	d3dDevice->SetMaterial(material);
}

//Set Renderer Texture
MP_INLINE void D3DRenderer::SetTexture(int sampler, IDirect3DBaseTexture9* tex) const
{
	d3dDevice->SetTexture(sampler, tex);
}

//Begin Writing to Render Buffer
MP_INLINE bool D3DRenderer::BeginRender() const
{
	return d3dDevice->BeginScene() == S_OK ? true : false;
}

//End Writing to Render Buffer
MP_INLINE bool D3DRenderer::EndRender() const
{
	return d3dDevice->EndScene() == S_OK ? true : false;
}
	
//Flip the Render Buffer to the Screen
MP_INLINE bool D3DRenderer::ShowRender() const
{
	return d3dDevice->Present(NULL, NULL, NULL, NULL) == S_OK ? true : false;
}

//Setup Projection Matrix
MP_INLINE void D3DRenderer::SetupProjection(float fov, float aspect, float np, float fp) const
{
	d3dDevice->SetTransform(D3DTS_PROJECTION, (const D3DMATRIX*)&mat4::PerspectiveFOV(fov, aspect, np, fp));
}

//Set World Tranform Matrix
MP_INLINE void D3DRenderer::SetWorldTransform(const mat4::MATRIX4& mat) const
{
	d3dDevice->SetTransform(D3DTS_WORLD, &D3DXMATRIX(mat._11, mat._12, mat._13, mat._14,
														mat._21, mat._22, mat._23, mat._24,
														mat._31, mat._32, mat._33, mat._34,
														mat._41, mat._42, mat._43, mat._44));
}

//Set View Transform Matrix
MP_INLINE void D3DRenderer::SetViewTransform(const mat4::MATRIX4& mat) const
{
	d3dDevice->SetTransform(D3DTS_VIEW, &D3DXMATRIX(mat._11, mat._12, mat._13, mat._14,
													mat._21, mat._22, mat._23, mat._24,
													mat._31, mat._32, mat._33, mat._34,
													mat._41, mat._42, mat._43, mat._44));
}

//Get Projection Matrix
MP_INLINE mat4::MATRIX4 D3DRenderer::GetProjectionMatrix() const
{
	D3DXMATRIXA16 mp;
	d3dDevice->GetTransform(D3DTS_PROJECTION, &mp);
	return mat4::MATRIX4(mp);
}

//Get View Matrix
MP_INLINE mat4::MATRIX4 D3DRenderer::GetViewMatrix() const
{
	D3DXMATRIXA16 mp;
	d3dDevice->GetTransform(D3DTS_VIEW, &mp);
	return mat4::MATRIX4(mp);
}

//Get World Matrix
MP_INLINE mat4::MATRIX4 D3DRenderer::GetWorldMatrix() const
{
	D3DXMATRIXA16 mp;
	d3dDevice->GetTransform(D3DTS_WORLD, &mp);
	return mat4::MATRIX4(mp);
}

//Enable/Disable Light
MP_INLINE void D3DRenderer::EnableLight(int id, bool enable) const
{
	d3dDevice->LightEnable(id, enable);
}

//Set Light
MP_INLINE void D3DRenderer::SetLight(int id, LIGHT& light) const
{
	D3DLIGHT9 l;
	l.Type = (D3DLIGHTTYPE)light.Type;
	l.Diffuse.r = light.Diffuse.r;
	l.Diffuse.g = light.Diffuse.g;
	l.Diffuse.b = light.Diffuse.b;
	l.Diffuse.a = light.Diffuse.a;
	l.Direction.x = light.Direction.x;
	l.Direction.y = light.Direction.y;
	l.Direction.z = light.Direction.z;
	l.Position.x = light.Position.x;
	l.Position.y = light.Position.y;
	l.Position.z = light.Position.z;
	l.Range = light.Range;
	l.Phi = light.Phi;
	l.Theta = light.Theta;
	l.Attenuation0 = light.Attenuation0;
	l.Attenuation1 = light.Attenuation1;
	l.Attenuation2 = light.Attenuation2;
	l.Falloff = light.Falloff;
	l.Specular.r = light.Specular.r;
	l.Specular.g = light.Specular.g;
	l.Specular.b = light.Specular.b;
	l.Specular.a = light.Specular.a;
	l.Ambient.r = light.Ambient.r;
	l.Ambient.g = light.Ambient.g;
	l.Ambient.b = light.Ambient.b;
	l.Ambient.a = light.Ambient.a;
	d3dDevice->SetLight(id, &l);
}

//Set Ambient Light
MP_INLINE void D3DRenderer::SetAmbientLight(int r, int g, int b, int a) const
{
	d3dDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(r,g,b,a));
}

//Set Fill Mode
MP_INLINE void D3DRenderer::SetFillModeSolid(){d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);}
MP_INLINE void D3DRenderer::SetFillModeWireframe(){d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);}
MP_INLINE void D3DRenderer::SetFillModePoint(){d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);}

//Create Material
MP_INLINE D3DMATERIAL9 D3DRenderer::CreateMaterial(clr::mColour4 diffuse, clr::mColour4 ambient, clr::mColour4 specular, clr::mColour4 emissive, float power) const
{
	D3DMATERIAL9 mat;

	mat.Diffuse.r = diffuse.r;
	mat.Diffuse.g = diffuse.g;
	mat.Diffuse.b = diffuse.b;
	mat.Diffuse.a = diffuse.a;

	mat.Ambient.r = ambient.r;
	mat.Ambient.g = ambient.g;
	mat.Ambient.b = ambient.b;
	mat.Ambient.a = ambient.a;

	mat.Specular.r = specular.r;
	mat.Specular.g = specular.g;
	mat.Specular.b = specular.b;
	mat.Specular.a = specular.a;

	mat.Emissive.r = emissive.r;
	mat.Emissive.g = emissive.g;
	mat.Emissive.b = emissive.b;
	mat.Emissive.a = emissive.a;

	mat.Power = power;

	return mat;
}

//Return Instance to Singleton
MP_INLINE D3DRenderer& RenderSystem(){return D3DRenderer::Inst();}

#endif


