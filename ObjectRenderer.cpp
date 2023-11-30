#include "ObjectRenderer.h"
#include "TextureManager.h"

ObjectRenderer::ObjectRenderer()
{
    this->texture = TextureManager::getInstance()->createTextureFromFile(L"Assets/Textures/wood.jpg");
}

ObjectRenderer::~ObjectRenderer()
{
}

void ObjectRenderer::setRenderer(String path)
{
    this->materialPath = path;
    //this->texture = TextureManager::getInstance()->createTextureFromFile(path);
}

void ObjectRenderer::setTexture(Texture* texture)
{
    this->texture = texture;
}

ObjectRenderer::String ObjectRenderer::getMaterialPath()
{
    return this->materialPath;
}

Texture* ObjectRenderer::getTexture()
{
    return this->texture;
}
