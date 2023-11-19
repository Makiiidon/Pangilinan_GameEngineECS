#pragma once
#include "GraphicsEngine.h"

class PixelShader
{
public: 
	PixelShader();
	~PixelShader();

	ID3D11PixelShader* getShader();

	void release();
private:
	bool init(const void* shader_byte_code, size_t byte_code_size);
	ID3D11PixelShader* m_ps = nullptr;

	friend class GraphicsEngine;
};

