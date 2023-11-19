#include "PixelShader.h"
#include "Utilities.h"

PixelShader::PixelShader()
{
	m_ps = nullptr;
}

void PixelShader::release()
{
	if (m_ps)
		m_ps->Release();
	delete this;

}

PixelShader::~PixelShader()
{
}

ID3D11PixelShader* PixelShader::getShader()
{
	return this->m_ps;
}

bool PixelShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	HRESULT hr = GraphicsEngine::get()->getDirect3DDevice()->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps);
	if (FAILED(hr)) {
		Utilities::PrintHResult("CreatePixelShader:", hr);
		return false;
	}
	return true;
}
