# 7zlib
一个封装了 7z 压缩解压功能的接口

### 说明
* 本工程提取 7z 16.04 源代码中压缩解压相关部分(具体是 CPP\7zip\UI\Client7z 下的工程)，修改成可用的压缩解压接口
* 工程编译环境为 win7 + vs2017 社区版
* 用该接口压缩的文件也可以使用 7z 或 winrar 等工具解压缩

### 使用
* 接口头文件为 7zip/7zlib.h
* 编译或使用静态库(lib)需要定义 SEVEN_ZIP_LIB 宏
* 可将根目录 7zip 目录里的代码添加到自己的工程中直接编译使用
* 可将本工程编译成自己需要的动态(静态)库使用
* 可直接使用 Backup 里编译好的库
* 未证明线程安全(但测试没有发现线程不安全问题)
* Backup 里的 7z.dll 要跟编出来的库放在同一目录下

### 接口

```cpp
enum ResultCode
{
	COMPRESS_BAD_SOURCE, // Compress Error: bad source.
	COMPRESS_BAD_DEST, // Compress Error: bad dest.
	COMPRESS_FIND_FILE_ERROR, // Compress Error: find file error.
	COMPRESS_CREATE_ARCHIVE_FILE_ERROR, // Compress Error: create archive file error.
	COMPRESS_GET_CLASS_OBJECT_ERROR, // Compress Error: get class object error.
	COMPRESS_UPDATE_ERROR, // Compress Error: update error.
	COMPRESS_GET_FAILED_FILES, // Compress Error: get failed files.
	COMPRESS_OK, // Compress Successed: ok.

	EXTRACT_BAD_SOURCE, // Extract Error: bad source.
	EXTRACT_BAD_DEST, // Extract Error: bad dest.
	EXTRACT_GET_CLASS_OBJECT_ERROR, // Extract Error: get class object error.
	EXTRACT_OPEN_ARCHIVE_FILE_ERROR, // Extract Error: open archive file error.
	EXTRACT_OPEN_FILE_AS_ARCHIVE_ERROR, // Extract Error: open file as archive error.
	EXTRACT_FILES_ERROR, // Extract Error: files error.
	EXTRACT_OK, // Extract Successed: ok.

	LIST_GET_CLASS_OBJECT_ERROR, // List Error: get class object error.
	LIST_OPEN_ARCHIVE_FILE_ERROR, // List Error: open archive file error.
	LIST_OPEN_FILE_AS_ARCHIVE_ERROR, // List Error: open file as archive error.
	LIST_OK, // List Successed: ok.

	UNKNOW_ERROR // Error: Unknow result.
};

// float - 如：56.7998%
typedef void(*CallbackFunc)(float, void*);

// 初始化(请勿多次初始化)
bool Initialize();

// source - 可以是相对路径或绝对路径，可以是文件 file 或目录 dir(目录的话如果以斜杠结尾则压缩包里没有顶层目录 dir，否则有)
// dest - 压缩包生成路径(要带文件名)，注意：请确保目录存在
// callback - 进度回调
// user - 用户数据，接口不会做任何修改，会在进度回调时传回 callback 的第二个参数
ResultCode Compress(const wchar_t* source, const wchar_t* dest, CallbackFunc callback = 0, void* user = 0);

// source - 压缩包生成路径(要带文件名)，注意：请确保目录存在
// dest - 解压所在目录，不在乎是否以斜杠结尾，注意：请确保目录存在
// callback - 同上
// user - 同上
ResultCode Uncompress(const wchar_t* source, const wchar_t* dest, CallbackFunc callback = 0, void* user = 0);

// 卸载
void Uninitialize();
```

### 例子

```cpp
// lib

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include "7zlib.h" // 替换成对应的路径

// 替换成对应的路径
#pragma comment(lib, "E:\\vspro\\test\\Release\\7zlib_MT.lib")

using namespace std;

struct TestInfo
{
	std::thread::id id;
	std::string content;
};

void TestCallback(float percent, void* user)
{
	TestInfo* ti = static_cast<TestInfo*>(user);
	std::cout << "threadId: " << ti->id << " " << ti->content << " " << percent << "%" << std::endl;
}

void TestLib(const wchar_t* source, const wchar_t* dest, const wchar_t* out)
{
	TestInfo tic;
	tic.id = std::this_thread::get_id();
	tic.content = "Compress";

	TestInfo tiuc;
	tiuc.id = std::this_thread::get_id();
	tiuc.content = "Uncompress";

	SevenZip::ResultCode resultCode1 = SevenZip::Compress(source, dest, TestCallback, &tic);
	std::cout << "threadId: " << tic.id << " compress resultCode[" << resultCode1 << "]" << std::endl;

	SevenZip::ResultCode resultCode2 = SevenZip::Uncompress(dest, out, TestCallback, &tiuc);
	std::cout << "threadId: " << tiuc.id << " uncompress resultCode[" << resultCode2 << "]" << std::endl;
}

int main()
{
	bool result = SevenZip::Initialize();
	if (result)
	{
		// 替换成对应的路径
		std::thread t1(TestLib, L"D:\\temp\\tt\\fan.exe", L"D:\\temp\\tt\\fan.7z", L"D:\\temp\\tt\\out7z");
		std::thread t2(TestLib, L"D:\\temp\\tt\\test7z/", L"D:\\temp\\tt/test7z.7z", L"D:\\temp\\tt\\out7z");

		t1.join();
		t2.join();
	}
	else
	{
		std::cout << "initialize error!" << std::endl;
	}

	SevenZip::Uninitialize();

	return 0;
}
```

```cpp
// dll

#include <iostream>
#include <string>
#include <windows.h>
#include "7zlib.h" // 替换成对应的路径

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

	// 替换成对应的路径
	HMODULE hDLL = LoadLibraryW(L"E:\\vspro\\7zlib\\Release\\7zlib.dll");
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
				// 替换成对应的路径
				SevenZip::ResultCode resultCode1 = compressFunc(L"D:\\temp\\tt\\test7z", L"D:\\temp\\tt/test7z.7z", nullptr, nullptr);
				std::cout << "compress resultCode[" << resultCode1 << "]" << std::endl;

				SevenZip::ResultCode resultCode2 = uncompressFunc(L"D:\\temp\\tt/test7z.7z", L"D:\\temp\\tt\\out7z", nullptr, nullptr);
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

int main()
{
	TestDll();
	return 0;
}
```
