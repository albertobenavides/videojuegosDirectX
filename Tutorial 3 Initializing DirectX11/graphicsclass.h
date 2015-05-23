/////////////////////////////////////
//Filename: graphicsclass.h
/////////////////////////////////////

#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

////////////
//INCLUDES//
////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "sphereclass.h"
#include "cubeclass.h"
#include "colorshaderclass.h"
#include "textureshaderclass.h"
#include "textureclass.h"
#include "QuadClass.h"
#include "LightClass.h"
#include "LightShaderClass.h"
#include "modelclass.h"
#include "bumpmapshaderclass.h"

///////////
//GLOBALS//
///////////

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

////////////////////////////////////////
//Class name: GraphicsClass
////////////////////////////////////////
class GraphicsClass{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

private:

	D3DClass* m_D3D;
	cameraclass* m_Camera;
	SphereClass* m_Sphere;
	CubeClass* m_Cube;
	QuadClass* m_Quad;
	QuadClass* m_AnuncioQuad;
	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;
	TextureShaderClass* m_BlueShader;
	TextureShaderClass* m_GrayscaleShader;
	TextureClass* m_Texture1;
	TextureClass* m_Texture2;
	TextureClass* m_MetalTexture;
	TextureClass* m_AnuncioTexture;
	TextureClass* m_Anuncio2Texture;
	TextureClass* m_Anuncio3Texture;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	ModelClass* m_Model;
	BumpMapShaderClass* m_BumpMapShader;
};

#endif
