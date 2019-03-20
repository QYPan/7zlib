
#include <iostream>
#include <string>
#include <windows.h>
#include "../7zlib/7zlib.h"

#ifdef _DEBUG
#pragma comment(lib, "E:\\vspro\\7zlib\\Debug\\7zlib.lib")
#else
#pragma comment(lib, "E:\\vspro\\7zlib\\Release\\7zlib.lib")
#endif

void TestCallback(float percent, void* user)
{
	char* str = static_cast<char*>(user);
	std::cout << str << " : " << percent << "%" << std::endl;
}

void TestDll()
{
	typedef bool(*InitializeFunc)();
	typedef SevenZip::ResultCode(*CompressFunc)(const wchar_t*, const wchar_t*, SevenZip::CallbackFunc, void*);
	typedef SevenZip::ResultCode(*UncompressFunc)(const wchar_t*, const wchar_t*, SevenZip::CallbackFunc, void*);
	typedef void(*UninitializeFunc)();

	InitializeFunc initializeFunc = nullptr;
	CompressFunc compressFunc = nullptr;
	UncompressFunc uncompressFunc = nullptr;
	UninitializeFunc uninitializeFunc = nullptr;

	HMODULE hDLL = LoadLibraryW(L"E:\\vspro\\7zlib\\Debug\\7zlib.dll");
	if (hDLL != NULL)
	{
		initializeFunc = (InitializeFunc)GetProcAddress(hDLL, "Initialize");
		compressFunc = (CompressFunc)GetProcAddress(hDLL, "Compress");
		uncompressFunc = (UncompressFunc)GetProcAddress(hDLL, "Uncompress");
		uninitializeFunc = (UninitializeFunc)GetProcAddress(hDLL, "Uninitialize");

		if (initializeFunc && compressFunc && uncompressFunc && uninitializeFunc)
		{
			bool result = initializeFunc();
			if (result)
			{
				SevenZip::ResultCode resultCode1 = compressFunc(L"D:\\temp\\tt\\test7z\\gobang2.exe", L"D:\\temp\\tt\\test7z\\gobang2.7z", nullptr, nullptr);
				std::cout << "compress resultCode[" << resultCode1 << "]" << std::endl;

				SevenZip::ResultCode resultCode2 = uncompressFunc(L"D:\\temp\\tt\\test7z\\gobang2.7z", L"D:\\temp\\tt\\test7z\\out7z", nullptr, nullptr);
				std::cout << "uncompress resultCode[" << resultCode2 << "]" << std::endl;
			}
			else
			{
				std::cout << "initialize error!" << std::endl;
			}
		}
		else
		{
			std::cout << "bad func address!" << std::endl;
		}

		uninitializeFunc();
	}
	else
	{
		std::cout << "can not load dll!" << std::endl;
	}
}

void TestLib()
{
	bool result = SevenZip::Initialize();
	if (result)
	{
		char c[] = { "Compress" };
		char unc[] = { "Uncompress" };

		SevenZip::ResultCode resultCode1 = SevenZip::Compress(L"D:\\temp\\tt\\test7z/../fan.exe", L"D:\\temp\\tt/test7z/..\\fan.7z", TestCallback, c);
		std::cout << "compress resultCode[" << resultCode1 << "]" << std::endl;

		SevenZip::ResultCode resultCode2 = SevenZip::Uncompress(L"D:\\temp\\tt\\test7z/../fan.7z", L"D:\\temp\\tt\\out7z\\", TestCallback, unc);
		std::cout << "uncompress resultCode[" << resultCode2 << "]" << std::endl;
	}
	else
	{
		std::cout << "initialize error!" << std::endl;
	}

	SevenZip::Uninitialize();
}

int main()
{
	TestLib();
	return 0;
}