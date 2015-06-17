#using <System.dll>
#include "StringToANSI.hpp"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace NSass
{
	char* MarshalString(String^ s)
	{
		return (char*) Marshal::StringToHGlobalAnsi(s).ToPointer();
	}

	void FreeString(char* p)
	{
		if (p) Marshal::FreeHGlobal(IntPtr((void *) p));
	}

	const char* MarshalConstString(String^ s)
	{
		return (const char*) Marshal::StringToHGlobalAnsi(s).ToPointer();
	}

	void FreeConstString(const char* p)
	{
		if (p) Marshal::FreeHGlobal(IntPtr((void *) p));
	}

	char** MarshalStringArray(array<String^>^ s)
	{
		int length = s -> Length;
		char** arr = new char*[length];

		for (int i = 0; i < length; ++i)
		{
			arr[i] = (char*) Marshal::StringToHGlobalAnsi(s[i]).ToPointer();
		}

		return arr;
	}

	void FreeStringArray(char** p, int length)
	{
		if (p)
		{
			for (int i = 0; i < length; ++i)
			{
				if (p[i]) Marshal::FreeHGlobal(IntPtr((void *) p[i]));
			}

			delete[] p;
		}
	}
}