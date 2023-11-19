#pragma once
#include <d3d11.h>
#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	bool init();
	bool release();

	static GraphicsEngine* get();

	SwapChain* createSwapChain();
	ID3D11Device* getDirect3DDevice();
	DeviceContext* getImmediateDeviceContext();

	VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	bool compileVertexShader(LPCWSTR file_name, LPCSTR entry_point_name, void** shaderByteCode, size_t* byteCodeSize);
	void releaseCompiledShader();


	PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);
	bool compilePixelShader(LPCWSTR file_name, LPCSTR entry_point_name, void** shaderByteCode, size_t* byteCodeSize);


	VertexBuffer* createVertexBuffer();
	IndexBuffer* createIndexBuffer();
	ConstantBuffer* createConstantBuffer();

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_selected_feature_level;
	DeviceContext* m_imm_context;

	// for swap chain creation
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;

	ID3DBlob* m_custom_blob;
	//ID3DBlob* m_ps_blob;

	//ID3D11VertexShader* m_vs;
	ID3D11PixelShader* m_ps;


	friend class SwapChain;
	friend class VertexBuffer;
	friend class IndexBuffer;
};

