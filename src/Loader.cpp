// loader.h
// CS 202 Project: Scrolling Space Shooter
// Team Members: William Horn, Corey Gray, Michael Bilan, Cameron Titus, Kyle Tam, Andrew Cummins
// Created: 201704??
// Updated: 20170426
//
// Definitions for loader functions

#include "Loader.h"

#include <fstream>

// Loads the images used for sprites
bool load_texture(sf::Texture& tex,const std::string& filename)
{
    char buffer;
	std::ifstream istr(filename.c_str(),std::ios_base::in|std::ios_base::binary);
	istr.unsetf(std::ios_base::skipws);

	if(!istr)
		return false;

	std::string data="";

	while(istr>>buffer)
		data+=buffer;

	istr.close();
	tex.loadFromMemory(data.c_str(),data.size());
	return true;
}

// Loads the images used for text
bool load_font(sf::Font& tex,const std::string& filename)
{
    char buffer;
	std::ifstream istr(filename.c_str(),std::ios_base::in|std::ios_base::binary);
	istr.unsetf(std::ios_base::skipws);

	if(!istr)
		return false;

	std::string data="";

	while(istr>>buffer)
		data+=buffer;

	istr.close();
	tex.loadFromMemory(data.c_str(),data.size());
	return true;
}
