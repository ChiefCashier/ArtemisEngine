#pragma once
#include "FreeImage.h"
#include "glew.h"
#include "Resource.h"

	class Image : public Resource
	{
	public:
		Image() : Resource(""){};
		Image(std::string name);
		~Image();
		size_t getWidth();
		size_t getHeight();
		std::string getName();
		void* getPixelData();
		GLuint getImageFormat();
		GLuint getTextureId();
		FIBITMAP* getBITMAP();


	private:

		std::string _name;
		size_t _width;
		size_t _height;
		void* _pixelData;
		GLuint _imageFormat;
		GLuint _textureId;


	};
