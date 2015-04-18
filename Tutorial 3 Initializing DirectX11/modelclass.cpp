//////////////////////////
//Filename: modelclass.cpp
//////////////////////////
#include "modelclass.h"

ModelClass::ModelClass(){
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

ModelClass::ModelClass(const ModelClass& other){
}

ModelClass::~ModelClass(){
}

bool ModelClass::Initialize(ID3D11Device* device){

	bool result;

	//Initialize the vertex and index buffer that hold the geometry for the triangle
	result = InitializeBuffers(device);
	if(!result)
		return false;

	return true;
}

void ModelClass::Shutdown(){

	//Release the vertex and index buffers;
	ShutdownBuffers();

	return;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext){

	//Put the vertex and index buffers on the graphics pipeline to prepare them for drawing
	RenderBuffers(deviceContext);

	return;
}

int ModelClass::GetIndexCount(){

	return m_indexCount;
}

bool ModelClass::InitializeBuffers(ID3D11Device* device){

	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	//Set the number of vertices in the vertex array
	m_vertexCount = 8;

	//Set the number of indices in the index array
	m_indexCount = 36;

	//Create the vertex array
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
		return false;

	//Create the index array
	indices = new unsigned long[m_indexCount];
	if(!indices)
		return false;

	//Load the vertex array with data
	vertices[0].position = D3DXVECTOR3(-1.0f,-1.0f,0.0f); //Bottom left
	vertices[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[1].position = D3DXVECTOR3(-1.0f,1.0f,0.0f); //Top left
	vertices[1].color = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = D3DXVECTOR3(1.0f,-1.0f,0.0f); //Bottom right
	vertices[2].color = D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f);

	vertices[3].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f); //Bottom right
	vertices[3].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);

	vertices[4].position = D3DXVECTOR3(-1.0f, -1.0f, 2.0f); //Top left
	vertices[4].color = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);

	vertices[5].position = D3DXVECTOR3(-1.0f, 1.0f, 2.0f); //Bottom right
	vertices[5].color = D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f);

	vertices[6].position = D3DXVECTOR3(1.0f, -1.0f, 2.0f); //Top left
	vertices[6].color = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);

	vertices[7].position = D3DXVECTOR3(1.0f, 1.0f, 2.0f); //Bottom right
	vertices[7].color = D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f);

	//Load the index array with data
	indices[0] = 1; //Bottom left
	indices[1] = 0; //Top Middle
	indices[2] = 3; //Bottom right
	indices[3] = 0; //Bottom right
	indices[4] = 2; //Bottom right
	indices[5] = 3; //Bottom right

	indices[6] = 3;
	indices[7] = 2;
	indices[8] = 7;
	indices[9] = 2;
	indices[10] = 6;
	indices[11] = 7;

	indices[12] = 7;
	indices[13] = 6;
	indices[14] = 5;
	indices[15] = 6;
	indices[16] = 4;
	indices[17] = 5;

	indices[18] = 5;
	indices[19] = 4;
	indices[20] = 1;
	indices[21] = 4;
	indices[22] = 0;
	indices[23] = 1;

	indices[24] = 5;
	indices[25] = 1;
	indices[26] = 7;
	indices[27] = 1;
	indices[28] = 3;
	indices[29] = 7;

	indices[30] = 6;
	indices[31] = 0;
	indices[32] = 4;
	indices[33] = 6;
	indices[34] = 2;
	indices[35] = 0;
	//Set up the description of the static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType)* m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	//Give the subresource structure a pointer to the vertex data
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch=0;
	vertexData.SysMemSlicePitch = 0;

	//Now create the vertex buffer
	result = device->CreateBuffer(&vertexBufferDesc,&vertexData,&m_vertexBuffer);
	if(FAILED(result))
		return false;

	//Set up the description of the static index buffer
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long)* m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	//Give the subresource structure a pointer to the index data
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch =0;

	//Create the index buffer
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
		return false;

	//Release the arrays now that the vertex and index buffers have been created and loaded
	delete []vertices;
	vertices = 0;

	delete []indices;
	indices = 0;

	return true;

}

void ModelClass::ShutdownBuffers(){

	//Release the index buffer
	if(m_indexBuffer){
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	//Release the vertex buffer
	if(m_vertexBuffer){
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;	
	}

	return;
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext){

	unsigned int stride;
	unsigned int offset;

	//Set vertex buffer stride and offset
	stride = sizeof(VertexType);
	offset=0;

	//Set the vertex buffer to active in the input assembler so it can be rendered
	deviceContext->IASetVertexBuffers(0,1,&m_vertexBuffer,&stride,&offset);

	//Set the index buffer to active in th input assembler so it can be rendered
	deviceContext->IASetIndexBuffer(m_indexBuffer,DXGI_FORMAT_R32_UINT,0);

	//Set the tupe of primitive that should be rendered from this vertex buffer, in this case triangles
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}
