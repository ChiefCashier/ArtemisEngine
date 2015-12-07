#include "ResourceLoader.h"
#include "FreeImage.h"
#include <iostream>
#include <fstream>
#include <cassert>
/*
Parametrit:
filename: tiedoston nimi ja paate esim: "kuva.png"

Metodi:
Kauttaa FreeImagea kuvien lataamiseen suoraan merkkijonoon.

*/

namespace CML
{
	char* CML::ResourceLoader::LoadImage(char* filename)
	{

		FREE_IMAGE_FORMAT formato = FreeImage_GetFIFFromFilename(filename);
		FIBITMAP* imagen = FreeImage_Load(formato, filename);


		char* pixeles = (char*)FreeImage_GetBits(imagen);
		FreeImage_Unload(imagen);
		return pixeles;

	}

	/*
	Parametrit:
	filename: tiedoston nimi ja paate esim: "tiedosto.txt"

	Metodi:
	Kauttaa ifstreamiÅEtiedoston latamiseen, aukaisee tiedoston, etsii sen koon ja lukee datan.

	HUOM:
	bufferi pitaa poistaa kauton jalkeen

	Myohemmin pitaa suojata erroreilta kuten tiedostoa ei ole
	*/

	char* CML::ResourceLoader::LoadFile(char* filename)
	{
		std::ifstream is(filename, std::ifstream::binary);
		assert(is);
		if (is) {
			// tiedoston koko
			is.seekg(0, is.end);
			int length = is.tellg();
			is.seekg(0, is.beg);

			char * buffer = new char[length + 1];

			std::cout << "Reading " << length << " characters... " << std::endl;
			// lukee tiedoston datan
			is.read(buffer, length);

			buffer[length] = '\0';

			if (is)
				std::cout << "all characters read successfully." << std::endl;
			else
				std::cout << "error: only " << is.gcount() << " could be read" << std::endl;
			is.close();

			// buffer pitaa poistaa kauton jalkeen
			return buffer;
		}
		
		return NULL;
	}
}