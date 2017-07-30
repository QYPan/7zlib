#ifndef _SEVEN_ZIP_WORKER_H
#define _SEVEN_ZIP_WORKER_H

#include <vector>
#include <string>

namespace SevenZipStatus
{
	enum BackStatus {

		COMPRESS_BAD_SOURCE_PATH,
		COMPRESS_FIND_FILE_ERROR,
		COMPRESS_CREATE_ARCHIVE_FILE_ERROR,
		COMPRESS_GET_CLASS_OBJECT_ERROR,
		COMPRESS_UPDATE_ERROR,
		COMPRESS_GET_FAILED_FILES,
		COMPRESS_OK,

		EXTRACT_GET_CLASS_OBJECT_ERROR,
		EXTRACT_OPEN_ARCHIVE_FILE_ERROR,
		EXTRACT_OPEN_FILE_AS_ARCHIVE_ERROR,
		EXTRACT_FILES_ERROR,
		EXTRACT_OK,

		LIST_GET_CLASS_OBJECT_ERROR,
		LIST_OPEN_ARCHIVE_FILE_ERROR,
		LIST_OPEN_FILE_AS_ARCHIVE_ERROR,
		LIST_OK
	};

	std::string BackMsg(BackStatus result) {
		std::string msg;
		switch (result)
		{
		case COMPRESS_BAD_SOURCE_PATH:
			msg = "Compress Error: bad source path.";
			break;
		case COMPRESS_FIND_FILE_ERROR:
			msg = "Compress Error: find file error.";
			break;
		case COMPRESS_CREATE_ARCHIVE_FILE_ERROR:
			msg = "Compress Error: create archive file error.";
			break;
		case COMPRESS_GET_CLASS_OBJECT_ERROR:
			msg = "Compress Error: get class object error.";
			break;
		case COMPRESS_UPDATE_ERROR:
			msg = "Compress Error: update error.";
			break;
		case COMPRESS_GET_FAILED_FILES:
			msg = "Compress Error: get failed files.";
			break;
		case COMPRESS_OK:
			msg = "Compress Successed: ok.";
			break;
		case EXTRACT_GET_CLASS_OBJECT_ERROR:
			msg = "Extract Error: get class object error.";
			break;
		case EXTRACT_OPEN_ARCHIVE_FILE_ERROR:
			msg = "Extract Error: open archive file error.";
			break;
		case EXTRACT_OPEN_FILE_AS_ARCHIVE_ERROR:
			msg = "Extract Error: open file as archive error.";
			break;
		case EXTRACT_FILES_ERROR:
			msg = "Extract Error: files error.";
			break;
		case EXTRACT_OK:
			msg = "Extract Successed: ok.";
			break;
		case LIST_GET_CLASS_OBJECT_ERROR:
			msg = "List Error: get class object error.";
			break;
		case LIST_OPEN_ARCHIVE_FILE_ERROR:
			msg = "List Error: open archive file error.";
			break;
		case LIST_OPEN_FILE_AS_ARCHIVE_ERROR:
			msg = "List Error: open file as archive error.";
			break;
		case LIST_OK:
			msg = "List Successed: ok.";
			break;
		default:
			msg = "Error: Unknow back status.";
			break;
		}
		return msg;
	}
}

class SevenZipWorker {
public:

	SevenZipWorker();

	void Initialize();
	bool TraveseFolder(const std::string &folder_path);

	typedef void(*Func_Percent)(float percent);

	void RegisterPercentCallBackFunc(Func_Percent);

	SevenZipStatus::BackStatus Compress(const std::string &source_path, const std::string &goal_path);
	SevenZipStatus::BackStatus Extract(const std::string &source_path, const std::string &goal_path);
	SevenZipStatus::BackStatus ListArchive(const std::string &source_path);

	bool JudgeFileExist(const std::string &file_path);

	void ShowFiles();
private:
	std::vector<std::string> m_pack_list;
	int m_folders;
	int m_files;
	Func_Percent m_percent_func;
};

bool Initialize7zDll(const std::wstring &dll_path = L""); // 不填则默认 7z.dll 路径与 exe 相同，否则填绝对路径


#endif _SEVEN_ZIP_WORKER_H