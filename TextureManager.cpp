#include "TextureManager.h"
#include "Texture.h"
#include <filesystem>

TextureManager* TextureManager::sharedInstance = NULL;

void TextureManager::initialize()
{
	sharedInstance = new TextureManager();
}

void TextureManager::destroy()
{
	delete sharedInstance;
}

TextureManager* TextureManager::getInstance()
{
	return sharedInstance;
}

Texture* TextureManager::createTextureFromFile(const wchar_t* filePath)
{
	std::wstring fullPath = std::filesystem::absolute(filePath);

	if (this->resourceMap[fullPath] == NULL) {
		std::cout << " null .." << std::endl;
		this->resourceMap[fullPath] = this->convertToResource(filePath);
	}

	//std::cout << fullPath.c_str() << "\n";

	return (Texture*)this->resourceMap[fullPath];
}

TextureManager::TextureManager() :AResourceManager()
{

}

TextureManager::~TextureManager()
{
	AResourceManager::~AResourceManager();
}

Resource* TextureManager::convertToResource(const wchar_t* filePath)
{
	Texture* tex = NULL;
	try
	{
		tex = new Texture(filePath);
	}
	catch (...)
	{
		
	}

	return (Resource*)tex;
}
