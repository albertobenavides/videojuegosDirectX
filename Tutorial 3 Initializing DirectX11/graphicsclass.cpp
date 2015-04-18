/////////////////////////////////////
//Filename: graphicsclass.cpp
/////////////////////////////////////
#include "graphicsclass.h"

float rotation;

GraphicsClass::GraphicsClass(){
	m_D3D = 0;
	m_Camera = 0;
	m_Sphere = 0;
	m_Cube = 0;
	m_Quad = 0;
	m_AnuncioQuad = 0;
	m_ColorShader = 0;
	m_Texture1 = 0;
	m_Texture2 = 0;
	m_MetalTexture = 0;
	m_AnuncioTexture = 0;
	m_Anuncio2Texture = 0;
	m_Anuncio3Texture = 0;
	m_TextureShader = 0;
	m_BlueShader = 0;
	m_GrayscaleShader = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other){
}

GraphicsClass::~GraphicsClass(){
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd){

	bool result;


	//Create the Direct3D Object
	m_D3D = new D3DClass;
	if(!m_D3D)
		return false;

	//Initialize the Direct3D object
	m_D3D->Initialize(screenWidth,screenHeight,VSYNC_ENABLED,hwnd,FULL_SCREEN,SCREEN_DEPTH,SCREEN_NEAR);

	//Create the camera object
	m_Camera = new cameraclass;

	//Set the initial position of the camera
	m_Camera->SetPosition(0.0f,1.0f,-10.0f);

	//Create the sphere object
	m_Sphere = new SphereClass;
	int stacks = 36;
	int slices = 36;
	float radius = 1;
	D3DXVECTOR3 positionSphere = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR4 colorSphere = D3DXVECTOR4(1, 1, 0, 1);
	m_Sphere->Initialize(m_D3D->GetDevice(), positionSphere, stacks, slices, radius, colorSphere);

	m_Cube = new CubeClass;
	m_Cube->Initialize(m_D3D->GetDevice());

	// Shaders
	m_TextureShader = new TextureShaderClass;
	m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd, L"texture.vs", L"texture.ps");

	m_BlueShader = new TextureShaderClass;
	m_BlueShader->Initialize(m_D3D->GetDevice(), hwnd, L"texture.vs", L"blue.ps");

	m_GrayscaleShader = new TextureShaderClass;
	m_GrayscaleShader->Initialize(m_D3D->GetDevice(), hwnd, L"texture.vs", L"grayscale.ps");

	// Textures

	m_Texture1 = new TextureClass;
	m_Texture1->Initialize(m_D3D->GetDevice(), L"zacate.jpg");

	m_Texture2 = new TextureClass;
	m_Texture2->Initialize(m_D3D->GetDevice(), L"caca.jpg");

	m_MetalTexture = new TextureClass;
	m_MetalTexture->Initialize(m_D3D->GetDevice(), L"metal.jpg");

	m_AnuncioTexture = new TextureClass;
	m_AnuncioTexture->Initialize(m_D3D->GetDevice(), L"anuncio1.jpg");

	m_Anuncio2Texture = new TextureClass;
	m_Anuncio2Texture->Initialize(m_D3D->GetDevice(), L"anuncio2.jpg");

	m_Anuncio3Texture = new TextureClass;
	m_Anuncio3Texture->Initialize(m_D3D->GetDevice(), L"anuncio3.jpg");

	//Create the color shader object
	m_ColorShader = new ColorShaderClass;
	

	//Initialize the color shader object
	m_ColorShader->Initialize(m_D3D->GetDevice(),hwnd);

	m_Quad = new QuadClass;
	m_Quad->Initialize(m_D3D->GetDevice(), 10, 15);

	m_AnuncioQuad = new QuadClass;
	m_AnuncioQuad->Initialize(m_D3D->GetDevice(), 2, 3);

	return  true;
}

void GraphicsClass::Shutdown(){

	// Release the color shader object.
	if(m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	if (m_Sphere)
	{
		m_Sphere->Shutdown();
		delete m_Sphere;
		m_Sphere = 0;
	}

	if (m_Cube)
	{
		m_Cube->Shutdown();
		delete m_Cube;
		m_Cube = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	//Release the Direct3D object
	if(m_D3D){

		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	if (m_Quad)
	{
		m_Quad->Shutdown();
		delete m_Quad;
		m_Quad = 0;
	}

	return;
}

bool GraphicsClass::Frame(){

	bool result;

	//Render the graphics scene
	result = Render();
	if(!result)
		return false;
	return true;
}

bool GraphicsClass::Render(){
	
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix, RotationZ;
	bool result;
	rotation += .001f;

	m_D3D->BeginScene(0.0f,0.0f,0.0f,1.0f);

	m_Camera->Render();

	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Suelo
	m_Quad->SetScale(D3DXVECTOR3(10, 10, 10));
	m_Quad->SetPosition(D3DXVECTOR3(0, 0, 0));
	m_Quad->SetRotation(D3DXVECTOR3(2, 0, 0));
	m_Quad->Render(m_D3D->GetDeviceContext());
	m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Quad->GetIndexCount(), m_Quad->GetMatrix(), viewMatrix, projectionMatrix, m_Texture1->GetTexture());

	m_Sphere->SetScale(D3DXVECTOR3(1, 1, 1));
	m_Sphere->SetPosition(D3DXVECTOR3(-4, 4, 0));
	m_Sphere->Render(m_D3D->GetDeviceContext());
	m_GrayscaleShader->Render(m_D3D->GetDeviceContext(), m_Sphere->GetIndexCount(), m_Sphere->GetMatrix(), viewMatrix, projectionMatrix, m_Texture2->GetTexture());


	m_Sphere->SetScale(D3DXVECTOR3(1, 1, 1));
	m_Sphere->SetPosition(D3DXVECTOR3(4, 4, 0));
	m_Sphere->Render(m_D3D->GetDeviceContext());
	m_BlueShader->Render(m_D3D->GetDeviceContext(), m_Sphere->GetIndexCount(), m_Sphere->GetMatrix(), viewMatrix, projectionMatrix, m_Texture2->GetTexture());

	m_Cube->SetScale(D3DXVECTOR3(0.1f, 2, 0.1f));
	m_Cube->SetPosition(D3DXVECTOR3(-2.5f, 0, -3));
	m_Cube->SetRotation(D3DXVECTOR3(0, 0, 0));
	m_Cube->Render(m_D3D->GetDeviceContext());
	m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Cube->GetIndexCount(), m_Cube->GetMatrix(), viewMatrix, projectionMatrix, m_MetalTexture->GetTexture());

	
	m_Cube->SetPosition(D3DXVECTOR3(0, 0, -3));
	m_Cube->Render(m_D3D->GetDeviceContext());
	m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Cube->GetIndexCount(), m_Cube->GetMatrix(), viewMatrix, projectionMatrix, m_MetalTexture->GetTexture());

	m_Cube->SetPosition(D3DXVECTOR3(2.5f, 0, -3));
	m_Cube->Render(m_D3D->GetDeviceContext());
	m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Cube->GetIndexCount(), m_Cube->GetMatrix(), viewMatrix, projectionMatrix, m_MetalTexture->GetTexture());

	m_AnuncioQuad->SetScale(D3DXVECTOR3(1, 0.5f, 1));
	m_AnuncioQuad->SetPosition(D3DXVECTOR3(-2.5f, 2, -3.5f));
	m_AnuncioQuad->SetRotation(D3DXVECTOR3(0, 0, 0));
	m_AnuncioQuad->Render(m_D3D->GetDeviceContext());
	m_TextureShader->Render(m_D3D->GetDeviceContext(), m_AnuncioQuad->GetIndexCount(), m_AnuncioQuad->GetMatrix(), viewMatrix, projectionMatrix, m_AnuncioTexture->GetTexture());

	m_AnuncioQuad->SetPosition(D3DXVECTOR3(0, 2, -3.5f));
	m_AnuncioQuad->Render(m_D3D->GetDeviceContext());
	m_TextureShader->Render(m_D3D->GetDeviceContext(), m_AnuncioQuad->GetIndexCount(), m_AnuncioQuad->GetMatrix(), viewMatrix, projectionMatrix, m_Anuncio2Texture->GetTexture());

	m_AnuncioQuad->SetPosition(D3DXVECTOR3(2.5f, 2, -3.5f));
	m_AnuncioQuad->Render(m_D3D->GetDeviceContext());
	m_TextureShader->Render(m_D3D->GetDeviceContext(), m_AnuncioQuad->GetIndexCount(), m_AnuncioQuad->GetMatrix(), viewMatrix, projectionMatrix, m_Anuncio3Texture->GetTexture());


	//Present the rendered scene to the sceen
	m_D3D->EndScene();
	return true;
}
