#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SFML/Graphics.hpp>

bool load_texture(sf::Texture& tex,const std::string& filename);

bool load_font(sf::Font& tex,const std::string& filename);

#endif
