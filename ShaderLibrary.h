#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

class VertexShader;
class PixelShader;

class ShaderLibrary
{
public:
	class ShaderData {
		void* shaderByteCode = nullptr;
		size_t sizeShader = 0;
	};

	typedef std::wstring String;
	typedef std::unordered_map<String, VertexShader*> VertexShaderTable;
	typedef std::unordered_map<String, PixelShader*> PixelShaderTable;

	static ShaderLibrary* getInstance();
	static void initialize();
	static void destroy();


	void requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader);
	VertexShader* getVertexShader(String vertexShaderName);
	PixelShader* getPixelShader(String pixelShaderName);

private:
	ShaderLibrary();
	~ShaderLibrary();
	ShaderLibrary(ShaderLibrary const&) {};
	static ShaderLibrary* sharedInstance;

	VertexShaderTable activeVertexShaders;
	PixelShaderTable activePixelShaders;
};

