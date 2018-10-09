/*
	Code written by James Fletcher. 
	Copyright 2010 - 2011. 
	ethocybin@googlemail.com
	http://www.mrpuzzle.org/
*/

#include "precom.h"
#include "D3DRenderer.h"
#include "MathLib.h"


//Destructor
D3DRenderer::~D3DRenderer()
{
	if(d3dDevice){d3dDevice->Release();}
	if(d3dObject){d3dObject->Release();}
	m_boxmesh->Release();
}

//Initialize D3D
void D3DRenderer::InitD3D(HWND hwnd)
{
	//Setup D3D
	d3dObject = Direct3DCreate9(D3D_SDK_VERSION);
	if(!d3dObject)
	{
		MessageBox(hwnd, "Could not create Direct 3D Object.", "Error", MB_OK | MB_TOPMOST);
		exit(0);
	}

	//Setup D3D vars
	bool windowed = true;
	DWORD multisampquality;
	D3DPRESENT_PARAMETERS presParams;
	ZeroMemory(&presParams, sizeof(presParams));
	presParams.Windowed = windowed;
	presParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presParams.BackBufferFormat = D3DFMT_UNKNOWN;
	presParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	presParams.EnableAutoDepthStencil = TRUE;
    presParams.AutoDepthStencilFormat = D3DFMT_D16;

	//Check Multi Sampling is avalible
	if(d3dObject->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, windowed, D3DMULTISAMPLE_NONMASKABLE, &multisampquality) == D3D_OK)
	{
		presParams.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
		presParams.MultiSampleQuality = 1;
	}

	//Create Device Object
	HRESULT hr = d3dObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &presParams, &d3dDevice);
	if(FAILED(hr))
	{
		hr = d3dObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_MIXED_VERTEXPROCESSING, &presParams, &d3dDevice);
		
		if(FAILED(hr))
		{
			hr = d3dObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &presParams, &d3dDevice);

			if(FAILED(hr))
			{
				MessageBox(hwnd, "Could not create Direct 3D Device.", "Error", MB_OK | MB_TOPMOST);
				exit(0);
			}
		}
	}


	//Get Device Caps
	D3DCAPS9 d3dCaps;
	d3dDevice->GetDeviceCaps(&d3dCaps);

	//Check that point sprites are supported
	if(!(d3dCaps.FVFCaps & D3DFVFCAPS_PSIZE))
	{
		MessageBox(hwnd, "Your card does not support Point Sprites.", "Error", MB_OK | MB_TOPMOST);
		exit(0);
	}

	if(d3dCaps.MaxPointSize <= 1.0f)
	{
		MessageBox(hwnd, "Your card does not support Point Sprites larger than one texel.", "Error", MB_OK | MB_TOPMOST);
		exit(0);
	}


	//Set Render States
	SetRenderStates();

	//Create box mesh
	D3DXCreateBox(d3dDevice, 1.f, 1.f, 1.f, &m_boxmesh, NULL);
}

//Set Render States
void D3DRenderer::SetRenderStates()
{
	//Z Buffering and Culling
	d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//Texture Filtering
	d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); //D3DTEXF_ANISOTROPIC
	d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); //D3DTEXF_ANISOTROPIC
	d3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	//d3dDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 8);

	//Anti Aliasing
	d3dDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);
	d3dDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);

	//Setup Alpha Blending
	d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//d3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	d3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	d3dDevice->SetRenderState(D3DRS_ALPHAREF, 128);

	//Set texture stages
	d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	d3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADD);
	d3dDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	d3dDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	d3dDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	d3dDevice->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	d3dDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	//Lighting
	d3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	d3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//Render the Skybox
void D3DRenderer::RenderSkybox()
{
	d3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	d3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU,  D3DTADDRESS_CLAMP);
	d3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV,  D3DTADDRESS_CLAMP);

	mat4::MATRIX4 om = GetViewMatrix();

	mat4::MATRIX4 cm = om;
	cm._41 = 0.f;
	cm._42 = 0.f;
	cm._43 = 0.f;
	SetViewTransform(cm);

	ContentManager().RenderModel(m_skybox);

	SetViewTransform(om);

	d3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU,  D3DTADDRESS_WRAP);
	d3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV,  D3DTADDRESS_WRAP);
	d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	d3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//Load Skybox
void D3DRenderer::InitSkybox(std::string name)
{
	m_skybox = ContentManager().LoadXModel(name, true, false, true);
	ContentManager().meshScale(m_skybox, 20.f);
}

//Init Particle Renderer
bool D3DRenderer::InitParticleRenderer(int maxparticles)
{
	//Create PointSprite Vertex Buffer
	if(FAILED(d3dDevice->CreateVertexBuffer( maxparticles * sizeof(PointSprite), 
											 D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY | D3DUSAGE_POINTS, 
											 PointSprite::FVF_FLAGS, D3DPOOL_DEFAULT, &m_pointbuffer, NULL)))
	{
		//Failed to create PointSprite Vertex Buffer
		return false;
	}

	//Set max particles
	m_maxparticles = maxparticles-1;

	//Sucessfully Initiated Particle Renderer
	return true;
}

//Render Particles
void D3DRenderer::RenderParticles(PointSprite* particles, int particles_size, IDirect3DBaseTexture9* texture)
{
	//Are there any particles to render?
	if(particles_size == 0 || particles_size >= m_maxparticles)
		return;

	//Set Render States
	d3dDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	d3dDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	const float fPointSize = 1.0f, fPointScaleB = 1.0f;
	d3dDevice->SetRenderState(D3DRS_POINTSIZE, *((DWORD*)&fPointSize));
	d3dDevice->SetRenderState(D3DRS_POINTSCALE_B, *((DWORD*)&fPointScaleB));
	//d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
  	//d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//Set particle texture
	d3dDevice->SetTexture(0, texture);

	//Vertex buffer pointer
	PointSprite *pVertices;

	//Lock the vertex buffer
	if(FAILED(m_pointbuffer->Lock(0, particles_size * sizeof(PointSprite), (void**)&pVertices, D3DLOCK_DISCARD)))
		return;

	//Copy particles to particle vertex buffer
	memcpy(pVertices, particles, particles_size * sizeof(PointSprite));

	//Unlock the vertex buffer
	m_pointbuffer->Unlock();

	//Render Vertex Buffer
	d3dDevice->SetStreamSource(0, m_pointbuffer, 0, sizeof(PointSprite));
	d3dDevice->SetFVF(PointSprite::FVF_FLAGS);
	d3dDevice->DrawPrimitive(D3DPT_POINTLIST, 0, particles_size);

	//Restore Render States
	d3dDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	d3dDevice->SetRenderState(D3DRS_POINTSCALEENABLE,  FALSE);
	d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}










