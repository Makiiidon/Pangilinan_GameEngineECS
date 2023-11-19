#include "VertexBuffer.h"
#include "GraphicsEngine.h"

VertexBuffer::VertexBuffer(): m_input_layout(nullptr), m_buffer(nullptr)
{
}

VertexBuffer::~VertexBuffer()
{
}

UINT VertexBuffer::getSizeVertexList()
{
	return m_size_list;
}

bool VertexBuffer::load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader)
{
	if (m_buffer)
		m_buffer->Release();
	if (m_input_layout)
		m_input_layout->Release();


	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT; // read and write rules for the buffer
	buff_desc.ByteWidth = size_vertex * size_list; // size of the vertex buffer
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // dictates where the vertex buffer will be bound to in the render pipeline
	buff_desc.CPUAccessFlags = 0;	// read/write rules of the CPU for the buffer
	buff_desc.MiscFlags = 0; // contains a variety of settings or flags that can be enabled for the vertex buffer

	D3D11_SUBRESOURCE_DATA init_data = {};	// initialization data for the vertex buffer to be created
	init_data.pSysMem = list_vertices; // pSysMem is a pointer to the initialization data

	m_size_vertex = size_vertex;
	m_size_list = size_list;


	HRESULT res =  GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer);

	if (FAILED(res))
		return false;

	D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"COLOR", 1, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	UINT size_layout = ARRAYSIZE(layout);

	res = GraphicsEngine::get()->m_d3d_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_input_layout);
	if (FAILED(res))
		return false;


	return true;
}

bool VertexBuffer::release()
{
	m_input_layout->Release();
	m_buffer->Release();

	delete this;

	return true;
}
