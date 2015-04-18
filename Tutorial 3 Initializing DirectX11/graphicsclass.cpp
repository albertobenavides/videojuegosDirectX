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
	m_ColorShader = 0;
	m_Texture1 = 0;
	m_TextureShader = 0;
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
	result = m_D3D->Initialize(screenWidth,screenHeight,VSYNC_ENABLED,hwnd,FULL_SCREEN,SCREEN_DEPTH,SCREEN_NEAR);
	if(!result){

		MessageBox(hwnd,L"Could not initialize Direct3D",L"Error",MB_OK);
	
	}

	//Create the camera object
	m_Camera = new cameraclass;
	if(!m_Camera)
		return false;

	

	//Set the initial position of the camera
	m_Camera->SetPosition(0.0f,0.0f,-10.0f);

	//Create the sphere object
	m_Sphere = new SphereClass;
	if (!m_Sphere)
		return false;

	m_Cube = new CubeClass;
	if (!m_Cube)
		return false;

	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
		return false;

	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initiazlize the texture shader object.", L"Error", MB_OK);
	}

	m_Texture1 = new TextureClass;
	if(!m_Texture1)
		return false;

	result = m_Texture1->Initialize(m_D3D->GetDevice(), L"puzzle2_1000.jpg");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture object.", L"Error", MB_OK);
		return false;
	}

	//Initialize the sphere object
	int stacks = 36;
	int slices = 36;
	float radius = 1;
	D3DXVECTOR3 positionSphere = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR4 colorSphere = D3DXVECTOR4(1, 1, 0, 1);
	result = m_Sphere->Initialize(m_D3D->GetDevice(), positionSphere, stacks, slices, radius, colorSphere);
	if (!result){
		MessageBox(hwnd, L"Could not initialize the sphere object.", L"Error", MB_OK);
		return false;
	}

	result = m_Cube->Initialize(m_D3D->GetDevice());
	if (!result){
		MessageBox(hwnd, L"Could not initialize the sphere object.", L"Error", MB_OK);
		return false;
	}

	//Create the color shader object
	m_ColorShader = new ColorShaderClass;
	if(!m_ColorShader)
		return false;

	//Initialize the color shader object
	result = m_ColorShader->Initialize(m_D3D->GetDevice(),hwnd);
	if(!result){
		MessageBox(hwnd,L"Could not initialize the color shader object.", L"Error",MB_OK);
		return false;
	}

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

	m_Sphere->SetScale(D3DXVECTOR3(1, 1, 1));
	m_Sphere->Render(m_D3D->GetDeviceContext());
	
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Sphere->GetIndexCount(), m_Sphere->GetMatrix(), viewMatrix, projectionMatrix, m_Texture1->GetTexture());
	if (!result)
		return false;

	m_Cube->SetScale(D3DXVECTOR3(1, 1, 1));
	m_Cube->SetPosition(D3DXVECTOR3(0, 2, 0));
	m_Cube->SetRotation(D3DXVECTOR3(0, rotation, 0));
	m_Cube->Render(m_D3D->GetDeviceContext());

	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Cube->GetIndexCount(), m_Cube->GetMatrix(), viewMatrix, projectionMatrix, m_Texture1->GetTexture());
	if (!result)
		return false;

	//Present the rendered scene to the sceen
	m_D3D->EndScene();
	return true;
}
