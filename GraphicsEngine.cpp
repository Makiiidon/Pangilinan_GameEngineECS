#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "GraphicsEngine.h"
#include <d3dcompiler.h>
#include <iostream>

#include "Utilities.h"

GraphicsEngine::GraphicsEngine(): m_selected_feature_level()
{
	m_d3d_device = nullptr;
	m_imm_context = nullptr;

	m_dxgi_device = nullptr;
	m_dxgi_adapter = nullptr;
	m_dxgi_factory = nullptr;

	m_custom_blob = nullptr;
}

GraphicsEngine::~GraphicsEngine()
{
}

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driver_types[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	constexpr UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] = {
		D3D_FEATURE_LEVEL_11_0
	};
	constexpr UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;

	ID3D11DeviceContext* imm_context;
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(
			NULL,
			driver_types[driver_type_index],
			NULL, D3D11_CREATE_DEVICE_DEBUG,
			feature_levels, num_feature_levels,
			D3D11_SDK_VERSION,
			&m_d3d_device,
			&m_selected_feature_level,
			&imm_context
		);
		if (SUCCEEDED(res)) {
			m_imm_context = new DeviceContext(imm_context);
			std::cout << "D3D11Device Created: " << driver_types[driver_type_index] << std::endl;
			break;
		}

		++driver_type_index;
	}

	if (FAILED(res))
		return false;

	// Without using CreateDeviceAndSwapChain Swap chain can only be created through idxgifactory
	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetAdapter(&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);


	return true;
}

bool GraphicsEngine::release()
{
	m_imm_context->release();
	m_d3d_device->Release();

	//// release dxgi resources
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	return true;
}

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine instance;

	return &instance;

}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain;
}

ID3D11Device* GraphicsEngine::getDirect3DDevice()
{
	return m_d3d_device;
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
	return m_imm_context;
}

VertexBuffer* GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer();
}

TexturedVertexBuffer* GraphicsEngine::createTexturedBuffer()
{
	return new TexturedVertexBuffer();
}

IndexBuffer* GraphicsEngine::createIndexBuffer()
{
	return new IndexBuffer();
}

VertexShader* GraphicsEngine::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VertexShader* vs = new VertexShader();

	if (!vs->init(shader_byte_code, byte_code_size)) {
		vs->release();
		return nullptr;
	}

	return vs;
}

bool GraphicsEngine::compileVertexShader(LPCWSTR file_name, LPCSTR entry_point_name, void** shaderByteCode, size_t* byteCodeSize)
{
	ID3DBlob* error_blob = nullptr;
	HRESULT hres = D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", NULL, NULL, &m_custom_blob, &error_blob);

	Utilities::PrintHResult("CompileVertexShader:", hres);
	if (FAILED(hres))
	{

		if (error_blob) {
			OutputDebugString(L"Error blob:");
			OutputDebugString(static_cast<LPCWSTR>(error_blob->GetBufferPointer()));
			error_blob->Release();
		}
		return false;
	}
	*shaderByteCode = this->m_custom_blob->GetBufferPointer();
	*byteCodeSize = this->m_custom_blob->GetBufferSize();

	return true;
}

void GraphicsEngine::releaseCompiledShader()
{
	if (m_custom_blob)
		m_custom_blob->Release();
}

PixelShader* GraphicsEngine::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShader* ps = new PixelShader();

	if (!ps->init(shader_byte_code, byte_code_size)) {
		ps->release();
		return nullptr;
	}

	return ps;
}

bool GraphicsEngine::compilePixelShader(LPCWSTR file_name, LPCSTR entry_point_name, void** shaderByteCode,
	size_t* byteCodeSize)
{
	ID3DBlob* error_blob = nullptr;
	HRESULT hres = D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", NULL, NULL, &m_custom_blob, &error_blob);

	Utilities::PrintHResult("CompilePixelShader:", hres);
	if (FAILED(hres))
	{

		if (error_blob) {
			OutputDebugString(L"Error blob:");
			OutputDebugString(reinterpret_cast<LPCWSTR>(error_blob->GetBufferPointer()));
			error_blob->Release();
		}
		return false;
	}
	*shaderByteCode = this->m_custom_blob->GetBufferPointer();
	*byteCodeSize = this->m_custom_blob->GetBufferSize();

	return true;
}

ConstantBuffer* GraphicsEngine::createConstantBuffer()
{
	return new ConstantBuffer();
}