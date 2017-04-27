/*
Loader.h
CS 202 Final Project: Scrolling Space Shooter
Team Members: Michael Bilan, Andrew Cummins, Corey Gray, William Horn, Kyle Tam, Cameron Titus
Created: 20/4/2017
Last Updated: 27/04/2017
Header for functions for loading text and font files.
*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

bool load_texture(sf::Texture& tex,const std::string& filename);

bool load_buffer(sf::SoundBuffer& soundBuffer, const std::string& filename);

#endif
