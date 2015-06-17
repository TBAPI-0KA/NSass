#using <System.dll>

using namespace System;

namespace NSass
{
	char* MarshalString(String^ s);
	void FreeString(char* p);

	const char* MarshalConstString(String^ s);
	void FreeConstString(const char* p);

	char** MarshalStringArray(array<String^>^ s);
	void FreeStringArray(char** p, int length);
}