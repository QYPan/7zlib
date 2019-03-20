#pragma once


#ifdef SEVEN_ZIP_LIB
#	define SEVEN_ZIP_API
#else
#	ifdef SEVEN_ZIP_EXPORTS
#	define SEVEN_ZIP_API __declspec(dllexport)
#	else
#	define SEVEN_ZIP_API __declspec(dllimport)
#	endif
#endif

namespace SevenZip
{

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

	typedef void(*CallbackFunc)(float, void*);

	extern "C" SEVEN_ZIP_API bool Initialize();

	extern "C" SEVEN_ZIP_API ResultCode Compress(const wchar_t* source, const wchar_t* dest, CallbackFunc callback = 0, void* user = 0);

	extern "C" SEVEN_ZIP_API ResultCode Uncompress(const wchar_t* source, const wchar_t* dest, CallbackFunc callback = 0, void* user = 0);

	extern "C" SEVEN_ZIP_API void Uninitialize();
} // namespace SevenZip
