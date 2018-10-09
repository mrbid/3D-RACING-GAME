
/*** Generated through Lumonix shaderFX  by: h8101260 in 3dsmax at: 23/02/2011 15:46:49  ***/ 

// This FX shader was built to support FX Composer. 


texture UICubeMap_7961 : environment
<
	string ResourceName = "OutputCube.dds";
	string UIName = "Cube Map";
	string ResourceType = "Cube";
	int MipLevels = 4;
>;
 
samplerCUBE UICubeMap_7961Sampler = sampler_state
{
	Texture = <UICubeMap_7961>;
	MinFilter = ANISOTROPIC;
	MagFilter = ANISOTROPIC;
	MipFilter = ANISOTROPIC;
	AddressU = CLAMP;
	AddressV = CLAMP;
};
 
float3 UIColor_4284
<
	string UIName = "Color";
	string UIWidget = "Color";
> = {0.0f, 0.0f, 0.0f };
 
float FresnelPower
<
	string UIWidget = "slider";
	float UIMin = 0.0;
	float UIMax = 100.0;
	float UIStep = 0.01;
	string UIName = "Fresnel Power";
> = 1.0;
 
float FresnelScale
<
	string UIWidget = "slider";
	float UIMin = 0.0;
	float UIMax = 100.0;
	float UIStep = 0.01;
	string UIName = "Fresnel Scale";
> = 2.0;
 
float FresnelBias
<
	string UIWidget = "slider";
	float UIMin = -100.0;
	float UIMax = 100.0;
	float UIStep = 0.01;
	string UIName = "Fresnel Bias";
> = 0.0;
 
texture TextureMap_8325
<
	string ResourceName = "spec.jpg";
	string UIName = "Texture Map";
	string ResourceType = "2D";
>;
 
sampler2D TextureMap_8325Sampler = sampler_state
{
	Texture = <TextureMap_8325>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};
 
float UIConst_1590
<
	string UIWidget = "slider";
	float UIMin = -999.0;
	float UIMax = 999.0;
	float UIStep = 0.1;
	string UIName = "Constant";
> = 64.0;
 
texture BumpMap_7881
<
	string ResourceName = "texture.jpg";
	string UIName = "Bump Map";
	string ResourceType = "2D";
>;
 
sampler2D BumpMap_7881Sampler = sampler_state
{
	Texture = <BumpMap_7881>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};
 
// this function does the different types of light attenuation 
float attenuation_func(int lightattenType, float4 lightAttenuation, float3 lightVec) 
{ 
	float att = 1.0; 
	return att; 
} 
	 
// this function does the different types of cone angle 
float coneangle_func(int lightconeType, float lightHotspot, float lightFalloff, float3 lightVec, float3 lightDir) 
{ 
	float cone = 1.0; 
	return cone; 
} 

/************** light info **************/ 

float3 light1Dir : Direction 
< 
	string UIName = "Light 1 Direction"; 
	string Object = "TargetLight"; 
	string Space = "World"; 
> = {100.0f, 100.0f, 100.0f}; 

float3 light1Pos : POSITION 
< 
	string UIName = "Light 1 Position"; 
	string Object = "PointLight"; 
	string Space = "World"; 
> = {100.0f, 100.0f, 100.0f}; 

float4 light1Color : LIGHTCOLOR <string UIWidget = "Color"; > = { 1.0f, 1.0f, 1.0f, 1.0f}; 
float4 light1Attenuation : Attenuation <string UIName = "Attenuation Settings"; > = { 1.0f, 1.0f, 1.0f, 1.0f}; 
float light1Hotspot : HotSpot <string UIName = "Hot Spot Value"; > = { 43.0f }; 
float light1Falloff : FallOff <string UIName = "Falloff Value"; > = { 45.0f }; 

#define light1Type 1
#define light1attenType 0
#define light1coneType 0
#define light1CastShadows true

//---------------------------------- 


float4x4 wvp : WorldViewProjection < string UIWidget = "None"; >;  
float4x4 worldI : WorldInverse < string UIWidget = "None"; >;  
float4x4 worldIT : WorldInverseTranspose < string UIWidget = "None"; >;  
float4x4 viewInv : ViewInverse < string UIWidget = "None"; >;  
float4x4 world : World < string UIWidget = "None"; >;  
// create the light vector 
float3 lightVec_func(float3 worldSpacePos, float3 lightVector, float3x3 objTangentXf, int lightType) 
{ 
	float3 lightVec = mul(objTangentXf, (mul((lightVector - worldSpacePos), worldI).xyz)); 
	return lightVec; 
} 



// input from application 
	struct a2v { 
	float4 position		: POSITION; 
	float4 tangent		: TANGENT; 
	float4 binormal		: BINORMAL; 
	float4 normal		: NORMAL; 

	float2 texCoord		: TEXCOORD0; 

}; 

// output to fragment program 
struct v2f { 
        float4 position    		: POSITION; 
        float3 lightVec    		: TEXCOORD0; 
        float3 eyeVec	    	: TEXCOORD1; 

        float3 worldTangent  	: TEXCOORD2; 
        float3 worldBinormal 	: TEXCOORD3; 
        float3 worldNormal   	: TEXCOORD4; 
        float3 viewDir	    	: TEXCOORD5; 
	float2 texCoord			: TEXCOORD6; 

}; 

//Ambient and Self-Illum Pass Vertex Shader
v2f av(a2v In, uniform float3 lightPos, uniform int lightType, uniform float3 lightDir) 
{ 
    v2f Out = (v2f)0; 
	Out.position = mul(In.position, wvp);				//transform vert position to homogeneous clip space 

	//this code was added by the World Space Transform Node 
	Out.worldNormal = mul(In.normal, worldIT).xyz;		//compute world space normal 
	Out.worldBinormal = mul(In.binormal, worldIT).xyz;	//compute world space binormal 
	Out.worldTangent = mul(In.tangent, worldIT).xyz;		//compute world space tangent 
	Out.viewDir = mul(In.position, world) - viewInv[3]; 
	//this code was added by the Eye Vector Node 
	float3x3 objTangentXf;								//build object to tangent space transform matrix 
	objTangentXf[0] = In.binormal.xyz; 
	objTangentXf[1] = -In.tangent.xyz; 
	objTangentXf[2] = In.normal.xyz; 
	//these three lines were added by the Eye Vector Node 
	float4 osIPos = mul(viewInv[3], worldI);			//put world space eye position in object space 
	float3 osIVec = osIPos.xyz - In.position.xyz;		//object space eye vector 
	Out.eyeVec = mul(objTangentXf, osIVec);				//tangent space eye vector passed out 

	return Out; 
} 

//Ambient and Self-Illum Pass Pixel Shader
float4 af(v2f In, uniform float3 lightDir, uniform float4 lightColor, uniform float4 lightAttenuation, uniform float lightHotspot, uniform float lightFalloff, uniform int lightType, uniform int lightattenType, uniform int lightconeType, uniform bool lightCastShadows, uniform int shadowPassCount) : COLOR 
{ 

	float3 Normal = float3(0,0,1);	//tangent space normal vector 
	//this code was added by the World Space Transform Node 
	float3 Nn = normalize(In.worldNormal); 		//input the vectors required for tangent to world space transform 
	float3 Tn = normalize(In.worldTangent); 
	float3 Bn = normalize(In.worldBinormal); 
		float3 MathWorldXform_1450 = ( Nn * Normal.z ) + (Normal.x * Bn ) + ( Normal.y * -Tn); 
	float3 MathReflect_3585 = reflect(In.viewDir, MathWorldXform_1450);		//Compute the reflection vector 
	float3 UICubeMap_7961InputVector = MathReflect_3585.xyz;
	UICubeMap_7961InputVector.xyz = UICubeMap_7961InputVector.xzy;  //swizzle required for Z up 
	float4 UICubeMap_7961 = texCUBE(UICubeMap_7961Sampler, UICubeMap_7961InputVector);
	float3 V = normalize(In.eyeVec.xyz);		//normalized eye vector 
	float NdotV_fresnel = saturate(dot(V,Normal)); 		//clamped dot product 
	float Pow_NdotV = pow(NdotV_fresnel,FresnelPower);		//x to the power of y 
	float3 MathLerp_4469 = lerp(UICubeMap_7961.rgb, UIColor_4284.rgb, ((Pow_NdotV * FresnelScale) + FresnelBias)); 
	float3 input1 = MathLerp_4469; 

	float4 ret =  float4(0,0,0,1); 
	ret = float4(input1, 1); 
	return ret; 
} 

//Diffuse and Specular Pass Vertex Shader
v2f v(a2v In, uniform float3 lightPos, uniform int lightType, uniform float3 lightDir) 
{ 
    v2f Out = (v2f)0; 
	float3x3 objTangentXf;								//build object to tangent space transform matrix 
	objTangentXf[0] = In.binormal.xyz; 
	objTangentXf[1] = -In.tangent.xyz; 
	objTangentXf[2] = In.normal.xyz; 
	float3 worldSpacePos = mul(In.position, world).xyz;	//world space position 
	Out.lightVec = lightVec_func(worldSpacePos, lightPos, objTangentXf, lightType); 
	float4 osIPos = mul(viewInv[3], worldI);			//put world space eye position in object space 
	float3 osIVec = osIPos.xyz - In.position.xyz;		//object space eye vector 
	Out.eyeVec = mul(objTangentXf, osIVec);				//tangent space eye vector passed out 
	Out.position = mul(In.position, wvp);				//transform vert position to homogeneous clip space 

	Out.texCoord = In.texCoord;						//pass through texture coordinates from channel 1 

	return Out; 
} 

//Diffuse and Specular Pass Pixel Shader
float4 f(v2f In, uniform float3 lightDir, uniform float4 lightColor, uniform float4 lightAttenuation, uniform float lightHotspot, uniform float lightFalloff, uniform int lightType, uniform int lightattenType, uniform int lightconeType, uniform bool lightCastShadows, uniform int shadowPassCount) : COLOR 
{ 
	float3 ret = float3(0,0,0); 
	float3 V = normalize(In.eyeVec);		//creating the eye vector  
	float3 L = normalize(In.lightVec);		//creating the light vector  

	float4 TextureMap_8325 = tex2D(TextureMap_8325Sampler, In.texCoord.xy);
	float3 input3 = TextureMap_8325.rgb; 


	float input5 = UIConst_1590; 


	float BumpMap_7881_center = tex2D(BumpMap_7881Sampler, In.texCoord.xy).r;		//center bump map sample
	float BumpMap_7881_U = tex2D(BumpMap_7881Sampler, In.texCoord.xy + float2( 0.005, 0)).r;		//U bump map sample
	float BumpMap_7881_V = tex2D(BumpMap_7881Sampler, In.texCoord.xy + float2(0, 0.005)).r;		//V bump map sample
	float BumpMap_7881_dHdU = BumpMap_7881_U - BumpMap_7881_center;		//create bump map U offset
	float BumpMap_7881_dHdV = BumpMap_7881_V - BumpMap_7881_center;		//create bump map V offset
	float3 BumpMap_7881 = float3( -BumpMap_7881_dHdU, BumpMap_7881_dHdV, 0.05 );		//create the tangent space normal
	BumpMap_7881 = normalize(BumpMap_7881);	 //normalize the result 
	float3 input8 = BumpMap_7881; 

	float3 N = input8;						//using the Normal socket  
	float3 diffuseColor = float3(0.0, 0.0, 0.0);			//the Diffuse Color socket is empty so we're using black
	float NdotL = dot(N, L);				//calculate the diffuse  
	float diffuse = saturate(NdotL);		//clamp to zero  
	float3 specularColor = input3;			//using the Specular Color socket 
	float glossiness = input5;				//using the Glossiness socket  
	float3 H = normalize(L + V);			//Compute the half angle  
	float NdotH = saturate(dot(N,H));		//Compute NdotH  
	specularColor *= pow(NdotH, glossiness);//Raise to glossiness power and compute final specular color  
	ret += specularColor + diffuseColor;	//add specular and diffuse color together
	ret *= lightColor;						//multiply by the color of the light 
	float attenuation = attenuation_func(lightattenType, lightAttenuation, In.lightVec); 					//calculate the light attenuation  
	float coneangle = coneangle_func(lightconeType, lightHotspot, lightFalloff, In.lightVec, lightDir); 	//calculate the light's cone angle 
	ret *= attenuation * coneangle;			//multiply by the light decay  
	float4 done = float4(ret, 1);			//create the final ouput value 
	return done; 
} 

technique Complete  
{  
	pass ambient  
    {		 
		VertexShader = compile vs_3_0 av(light1Pos,  light1Type, light1Dir); 
		ZEnable = true; 
		ZWriteEnable = true; 
		CullMode = cw; 
		ShadeMode = Gouraud;
		AlphaBlendEnable = false; 
		AlphaTestEnable = FALSE; 
	PixelShader = compile ps_3_0 af(light1Dir, light1Color, light1Attenuation, light1Hotspot, light1Falloff, light1Type, light1attenType, light1coneType, light1CastShadows, 1); 
	}  

	pass light1  
    {		 
		VertexShader = compile vs_3_0 v(light1Pos,  light1Type, light1Dir); 
		ZEnable = true; 
		CullMode = cw; 
		ShadeMode = Gouraud;
		ZWriteEnable = true; 
		ZFunc = LessEqual; 
		AlphaBlendEnable = true; 
		SrcBlend = One; 
		DestBlend = One; 
		AlphaTestEnable = FALSE; 
		PixelShader = compile ps_3_0 f(light1Dir, light1Color, light1Attenuation, light1Hotspot, light1Falloff, light1Type, light1attenType, light1coneType, light1CastShadows, 1); 
	}  
}    