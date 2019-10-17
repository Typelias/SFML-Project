#pragma once
#include <map>
#include <SFML/Graphics.hpp>
/*!
	AssetManger is used to hold all the assets for the game. It is used by
	the different states and it is a part of the enginge
*/
class AssetManager
{
public:
	//!The construcktor for the class
	AssetManager() {}
	//The destructor for the class
	~AssetManager() {}

	//!LoadTextures is used to load Textures to the manager
	void LoadTexture(std::string name, std::string fileName);
	//!GetTextures is used to get a reference to a Texture from the manager
	sf::Texture &GetTexture(std::string name);

	//!LoadFonts is used to load Fonts to the manager
	void LoadFont(std::string name, std::string fileName);
	//!GetFonts is used to get a reference to a Font from the manager
	sf::Font &GetFont(std::string name);

private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
};
