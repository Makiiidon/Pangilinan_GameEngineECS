#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include <iostream>

IndexBuffer::IndexBuffer()
{
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::load(void* indexList, UINT listSize)
{
	if (this->buffer) this->buffer->Release();

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = 4 * listSize;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = indexList;
	this->listSize = listSize;

	ID3D11Device* directXDevice = GraphicsEngine::get()->getDirect3DDevice();
	HRESULT bufferResult = directXDevice->CreateBuffer(&bufferDesc, &initData, &this->buffer);

	if (SUCCEEDED(bufferResult)) {
		std::cout << "Creation of index buffer succeeded. \n";
	}
	else {
		std::cout << "An error occurred in creating a index buffer. \n";
	}
}

void IndexBuffer::release()
{
	this->buffer->Release();
	delete this;
}

ID3D11Buffer* IndexBuffer::getBuffer()
{
	return this->buffer;
}

UINT IndexBuffer::getIndexSize()
{
	return this->listSize;
}
