#include "ConstantBuffer.h"

#include "GraphicsEngine.h"
#include "Utilities.h"

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
}

bool ConstantBuffer::load(void* buffer, UINT size_buffer)
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT; // read and write rules for the buffer
	buff_desc.ByteWidth = size_buffer; // size of the constant buffer
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // dictates where the vertex buffer will be bound to in the render pipeline
	buff_desc.CPUAccessFlags = 0;	// read/write rules of the CPU for the buffer
	buff_desc.MiscFlags = 0; // contains a variety of settings or flags that can be enabled for the vertex buffer

	D3D11_SUBRESOURCE_DATA init_data = {};	// initialization data for the vertex buffer to be created
	init_data.pSysMem = buffer; // pSysMem is a pointer to the initialization data

	HRESULT res = GraphicsEngine::get()->getDirect3DDevice()->CreateBuffer(&buff_desc, &init_data, &m_buffer);

	if (FAILED(res))
	{
		Utilities::PrintHResult("ConstantBuffer.load: ", res);
		return false;
	}

	return true;
}

void ConstantBuffer::update(DeviceContext* context, void* buffer)
{
	context->getDeviceContext()->UpdateSubresource(m_buffer, 0, nullptr, buffer, NULL, NULL);
}

void ConstantBuffer::release()
{
	if (m_buffer)
		m_buffer->Release();

	delete this;
}
