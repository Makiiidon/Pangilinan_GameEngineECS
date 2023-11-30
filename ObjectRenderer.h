#pragma once
#include <string>
#include "Texture.h"
class ObjectRenderer
{
protected:
	typedef std::string String;
public:
	ObjectRenderer();
	~ObjectRenderer();

	void setRenderer(String path);
	void setTexture(Texture* texture);
	String getMaterialPath();
	Texture* getTexture();

private:
	String materialPath;
	Texture* texture;

};

