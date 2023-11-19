#pragma once
#include "GraphicsEngine.h"

class VertexShader
{
public:
	VertexShader();
	void release();
	~VertexShader();
	ID3D11VertexShader* getShader();
private:
	bool init(const void* shader_byte_code, size_t byte_code_size);

	ID3D11VertexShader* m_vs;
	friend class GraphicsEngine;
};

