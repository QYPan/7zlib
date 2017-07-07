#ifndef _SEVEN_ZIP_WORKER_H
#define _SEVEN_ZIP_WORKER_H

#include <vector>
#include <string>

class SevenZipWorker {
public:
	SevenZipWorker();

	void Initialize();
	bool TraveseFolder(const std::string &folder_path);
	bool Compress(const std::string &source_path, const std::string &goal_path);
	bool Extract(const std::string &source_path, const std::string &goal_path);

	bool JudgeFileExist(const std::string &file_path);

	void ShowFiles();
private:
	std::vector<std::string> m_pack_list;
	int m_folders;
	int m_files;
};

bool Initialize7zDll(const std::string &dll_path); // ¾ø¶ÔÂ·¾¶


#endif _SEVEN_ZIP_WORKER_H