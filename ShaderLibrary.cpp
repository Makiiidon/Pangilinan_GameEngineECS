#include "ShaderLibrary.h"

ShaderLibrary* ShaderLibrary::sharedInstance = nullptr;
ShaderLibrary* ShaderLibrary::getInstance()
{
	return sharedInstance;
}

void ShaderLibrary::initialize()
{
	if (sharedInstance == nullptr) sharedInstance = new ShaderLibrary();
}

void ShaderLibrary::destroy()
{
}

void ShaderLibrary::requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader)
{

}

VertexShader* ShaderLibrary::getVertexShader(String vertexShaderName)
{
	return activeVertexShaders[vertexShaderName];
}

PixelShader* ShaderLibrary::getPixelShader(String pixelShaderName)
{
	return activePixelShaders[pixelShaderName];
}

ShaderLibrary::ShaderLibrary()
{

}

ShaderLibrary::~ShaderLibrary()
{

}
