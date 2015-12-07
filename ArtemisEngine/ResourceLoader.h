#pragma once
namespace CML
{
	class ResourceLoader
	{
	public:
		static char* LoadFile(char* filename);
		static char* LoadImage(char* filename);
	};

}