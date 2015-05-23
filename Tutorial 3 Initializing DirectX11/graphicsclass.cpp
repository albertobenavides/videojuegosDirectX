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

	m_Cube = 0;
	m_Cylinder = 0;
	m_Cylinder = 0;

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
	m_Model = 0;
	m_BumpMapShader = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other){}

GraphicsClass::~GraphicsClass(){}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd){

	//////////////
	// Direct3D //
	//////////////
	m_D3D = new D3DClass;
	m_D3D->Initialize(screenWidth,screenHeight,VSYNC_ENABLED,hwnd,FULL_SCREEN,SCREEN_DEPTH,SCREEN_NEAR);

	////////////
	// Camera //
	////////////
	m_Camera = new cameraclass;
	m_Camera->SetPosition(0.0f,1.0f,-10.0f);
	
	/////////////
	// Shaders //
	/////////////
	m_ColorShader = new ColorShaderClass;
	m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);

	m_TextureShader = new TextureShaderClass;
	m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd, L"texture.vs", L"texture.ps");

	m_BlueShader = new TextureShaderClass;
	m_BlueShader->Initialize(m_D3D->GetDevice(), hwnd, L"texture.vs", L"blue.ps");

	m_GrayscaleShader = new TextureShaderClass;
	m_GrayscaleShader->Initialize(m_D3D->GetDevice(), hwnd, L"texture.vs", L"grayscale.ps");

	m_LightShader = new LightShaderClass;
	m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);

	m_BumpMapShader = new BumpMapShaderClass;
	m_BumpMapShader->Initialize(m_D3D->GetDevice(), hwnd);

	//////////////
	// Textures //
	//////////////
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
	
	////////////
	// Lights //
	////////////
	m_Light = new LightClass;
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	/////////////
	// Objects //
	/////////////
	m_Sphere = new SphereClass;
	int stacks = 36;
	int slices = 36;
	float radius = 1;
	D3DXVECTOR3 positionSphere = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR4 colorSphere = D3DXVECTOR4(1, 1, 0, 1);
	m_Sphere->Initialize(m_D3D->GetDevice(), positionSphere, stacks, slices, radius, colorSphere);

	m_Cube = new CubeClass;
	m_Cube->Initialize(m_D3D->GetDevice(), L"puzzle.jpg", 1, 1);

	m_Quad = new QuadClass;
	m_Quad->Initialize(m_D3D->GetDevice(), 10, 15);

	m_AnuncioQuad = new QuadClass;
	m_AnuncioQuad->Initialize(m_D3D->GetDevice(), 2, 3);

	m_Cone = new ConeClass;
	m_Cone->Initialize(m_D3D->GetDevice(), L"seafloor.dds", D3DXVECTOR3(2, 0, 0), 2, 20, 2);

	m_Cylinder = new CylinderClass;
	m_Cylinder->Initialize(m_D3D->GetDevice(), L"seafloor.dds", D3DXVECTOR3(-2, 0, 0), 2, 20, 2);

	m_Torus = new TorusClass;
	m_Torus->Initialize(m_D3D->GetDevice(), L"seafloor.dds", D3DXVECTOR3(0, 2, -3), 20, 20, 5, 1);
	m_Model = new ModelClass;
	m_Model->Initialize(m_D3D->GetDevice(), "Cube.txt", L"stone01.gif", L"bump01.gif");

	return  true;
}

void GraphicsClass::Shutdown()
{
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	//Release the light object
	if (m_Light){
		delete m_Light;
		m_Light = 0;
	}

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

	if (m_BumpMapShader){
		m_BumpMapShader->Shutdown();
		delete m_BumpMapShader;
		m_BumpMapShader = 0;
	}

	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	return;
}

bool GraphicsClass::Frame()
{
	bool result;

	//Render the graphics scene
	result = Render();
	if(!result)
		return false;
	return true;
}

bool GraphicsClass::Render(){
	
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix, RotationZ;

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

	m_Cube->SetScale(D3DXVECTOR3(0.1f, 2, 0.1f));
	m_Cube->SetRotation(D3DXVECTOR3(0, 0, 0)); 
	m_Cube->SetPosition(D3DXVECTOR3(0, 0, -3));
	m_Cube->Render(m_D3D->GetDeviceContext());
	m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Cube->GetIndexCount(), m_Cube->GetMatrix(), viewMatrix, projectionMatrix, m_MetalTexture->GetTexture());

	m_Cube->SetScale(D3DXVECTOR3(0.1f, 2, 0.1f)); 
	m_Cube->SetRotation(D3DXVECTOR3(0, rotation, 0));
	m_Cube->SetPosition(D3DXVECTOR3(2.5f, 0, -3));
	m_Cube->Render(m_D3D->GetDeviceContext());
	m_LightShader->Render(m_D3D->GetDeviceContext(), m_Cube->GetIndexCount(), m_Cube->GetMatrix(), viewMatrix, projectionMatrix,
		m_Cube->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	m_AnuncioQuad->SetScale(D3DXVECTOR3(1, 0.5f, 1));
	m_AnuncioQuad->SetPosition(D3DXVECTOR3(-2.5f, 2, -3.5f));
	m_AnuncioQuad->Render(m_D3D->GetDeviceContext());
	m_TextureShader->Render(m_D3D->GetDeviceContext(), m_AnuncioQuad->GetIndexCount(), m_AnuncioQuad->GetMatrix(), viewMatrix, projectionMatrix, m_AnuncioTexture->GetTexture());

	m_AnuncioQuad->SetPosition(D3DXVECTOR3(0, 2, -3.5f));
	m_AnuncioQuad->Render(m_D3D->GetDeviceContext());
	m_TextureShader->Render(m_D3D->GetDeviceContext(), m_AnuncioQuad->GetIndexCount(), m_AnuncioQuad->GetMatrix(), viewMatrix, projectionMatrix, m_Anuncio2Texture->GetTexture());

	m_AnuncioQuad->SetPosition(D3DXVECTOR3(2.5f, 2, -3.5f));
	m_AnuncioQuad->Render(m_D3D->GetDeviceContext());
	m_TextureShader->Render(m_D3D->GetDeviceContext(), m_AnuncioQuad->GetIndexCount(), m_AnuncioQuad->GetMatrix(), viewMatrix, projectionMatrix, m_Anuncio3Texture->GetTexture());

	m_D3D->SetRasterizerMode(D3D11_CULL_BACK); // Corregir

	m_Cone->Render(m_D3D->GetDeviceContext());
	m_Cone->SetPosition(D3DXVECTOR3(0.0f, 1.0f, -1.0f));
	m_Cone->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Cone->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Cone->GetIndexCount(), m_Cone->GetMatrix(), viewMatrix, projectionMatrix,
		m_Cube->GetTexture());

	m_Cylinder->Render(m_D3D->GetDeviceContext());
	m_Cylinder->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Cylinder->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Cylinder->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Cylinder->GetIndexCount(), m_Cylinder->GetMatrix(), viewMatrix, projectionMatrix, m_Cylinder->GetTexture());

	m_Torus->Render(m_D3D->GetDeviceContext());
	m_Torus->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Torus->SetRotation(D3DXVECTOR3(0.0f, rotation / 2, 0.0f));
	m_Torus->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	//m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Torus->GetIndexCount(), m_Torus->GetMatrix(), viewMatrix, projectionMatrix, m_Torus->GetTexture());
	m_LightShader->Render(m_D3D->GetDeviceContext(), m_Torus->GetIndexCount(), m_Torus->GetMatrix(), viewMatrix, projectionMatrix,
		m_Torus->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	m_D3D->SetRasterizerMode(D3D11_CULL_FRONT); // Corregir

	m_Cube->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_Cube->SetPosition(D3DXVECTOR3(-2.0f, 1.0f, -2.0f));
	m_Cube->SetRotation(D3DXVECTOR3(0, -rotation / 5, 0));
	m_Cube->Render(m_D3D->GetDeviceContext());
	m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Cube->GetIndexCount(), m_Cube->GetMatrix(), viewMatrix, projectionMatrix, m_Texture1->GetTexture());

	m_Model->Render(m_D3D->GetDeviceContext());
	m_Model->SetPosition(D3DXVECTOR3(1.0f, 1.0f, -4.0f));
	m_Model->SetRotation(D3DXVECTOR3(3.14159f, rotation, 0.0f));
	m_Model->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), m_Model->GetMatrix(), viewMatrix, projectionMatrix, m_Model->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	m_D3D->EndScene();
	return true;
}
