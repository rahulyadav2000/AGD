#pragma once
#include "../utils/Vector2.h"
#include "../graphics/Window.h"
#include <sstream>
class TileTexture
{
private :
	sf::Texture texture;

public:
	TileTexture() {};

	TileTexture(const std::string& textureFilename)
	{
		if (!texture.loadFromFile(textureFilename))
		{
			std::stringstream sss;
			sss << "Texture file not found: " << textureFilename;
			throw std::exception(sss.str().c_str());
		}
	}

	sf::Texture& getTexture()
	{
		return texture;
	}
};