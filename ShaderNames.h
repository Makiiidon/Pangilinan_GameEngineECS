#pragma once
#include <iostream>
#include <string>

class VertexShader; 
class PixelShader;

class ShaderNames {
public:
	typedef std::wstring String;

	const String BASE_VERTEX_SHADER_NAME = L"VertexShader.hlsl";
	const String TEXTURED_VERTEX_SHADER_NAME = L"TexturedVertexShader.hlsl";


	const String BASE_PIXEL_SHADER_NAME = L"PixelShader.hlsl";
	const String TEXTURED_PIXEL_SHADER_NAME = L"TexturedPixelShader.hlsl";
};