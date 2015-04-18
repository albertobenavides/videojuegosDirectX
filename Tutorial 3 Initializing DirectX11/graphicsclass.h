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
	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;
	TextureClass* m_Texture1;
	TextureClass* m_Texture2;
};

#endif
