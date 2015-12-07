#pragma once

// For mbstowcs()
#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <Windows.h>

namespace CML
{
	bool WriteLog = false;
}
	class DebugLogger
	{
	public:
		static void Print(char *format, ...)
		{
			va_list marker;
			TCHAR szBuf[256];
			char tempChar[256] = {};

			va_start(marker, format);
			vsprintf(tempChar, format, marker);
			va_end(marker);

			// Print to console
			va_list arg;
			va_start(arg, format);
			vfprintf(stdout, format, arg);
			std::cout << std::endl;
			va_end(arg);

			// char conversion to wchar_t
			wchar_t temp[256];
			std::mbstowcs(temp, tempChar, 256);

			// Output to debug console
			// Unicode characters that cannot be represented in the system code page will be replaced with ?.
			OutputDebugString(temp);
			OutputDebugString(TEXT("\n"));

			// If WriteLog is set true, write message to file
			if (CML::WriteLog)
				WriteToFile(tempChar);
		}
		// Write message to file
		static void WriteToFile(std::string msg)
		{
			std::ofstream outputFile;
			outputFile.open("ErrorLog.txt", std::ios::app);
			if (outputFile.is_open())
			{
				outputFile << msg << std::endl;
			}
			outputFile.close();
		}
	};
