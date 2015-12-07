#include "Image.h"
#include <assert.h>
#include <string>
#include <iostream>
Image::Image(std::string name) : Resource(name)
	{
		FREE_IMAGE_FORMAT formato = FreeImage_GetFIFFromFilename(name.c_str());
		FIBITMAP* imagen = FreeImage_Load(formato, name.c_str());
		_name = name.c_str();
		_width = FreeImage_GetWidth(imagen);
		_height = FreeImage_GetHeight(imagen);
		void* pixeles = (void*)FreeImage_GetBits(imagen);
		FREE_IMAGE_TYPE a = FreeImage_GetImageType(imagen);
		assert(a == FIT_BITMAP);

		unsigned int bitDepth= FreeImage_GetBPP(imagen);
		assert(bitDepth == 24 || bitDepth == 32 || bitDepth == 48);
		_pixelData = pixeles;


		switch (bitDepth)
		{
		case 24:
		
			_imageFormat = GL_BGR;
			break;
		case 32:

			_imageFormat = GL_BGRA;
			break;
		case 48:

			_imageFormat = GL_BGRA;
			break;
		}
		glGenTextures(1, &_textureId);//generates texture
		glBindTexture(GL_TEXTURE_2D, _textureId);

		glTexImage2D(
			GL_TEXTURE_2D, 0, 4, _width,
			_height, 0, _imageFormat,
			GL_UNSIGNED_BYTE, FreeImage_GetBits(imagen)
			);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0u);
		FreeImage_Unload(imagen);
	}

	FIBITMAP* Image::getBITMAP()
	{
		FREE_IMAGE_FORMAT formato = FreeImage_GetFIFFromFilename(_name.c_str());
		return FreeImage_Load(formato, _name.c_str());
	}
	Image::~Image()
	{
	}
	size_t Image::getWidth()
	{
		return _width;
	}
	size_t Image::getHeight()
	{
		return _height;
	}
	std::string Image::getName()
	{
		return _name;
	}
	void* Image::getPixelData()
	{
		return _pixelData;
	}
	GLuint Image::getImageFormat()
	{
		return _imageFormat;
	}
	GLuint Image::getTextureId()
	{
		return _textureId;
}
