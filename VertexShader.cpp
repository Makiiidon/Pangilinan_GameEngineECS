#include "VertexShader.h"
#include "GraphicsEngine.h"
#include "Utilities.h"

VertexShader::VertexShader()
{
	m_vs = nullptr;
}

void VertexShader::release()
{
	if (m_vs)
		m_vs->Release();
	delete this;

}

VertexShader::~VertexShader()
{
}

ID3D11VertexShader* VertexShader::getShader()
{
	return this->m_vs;
}

bool VertexShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	HRESULT hr = GraphicsEngine::get()->getDirect3DDevice()->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs);
	if (FAILED(hr)) {
		Utilities::PrintHResult("CreateVertexShader:", hr);
		return false;
	}
	return true;
}
