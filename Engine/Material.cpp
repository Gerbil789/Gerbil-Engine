#include "Material.h"
#include "../Utilities/ImageLoader.h"

Material::Material(std::string path, std::string _name)
{
	name = _name;
	textureID = ImageLoader::LoadTexture(path);
}



