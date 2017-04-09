#ifndef _SEVEN_ZIP_WORKER_H
#define _SEVEN_ZIP_WORKER_H

#include <vector>

class SevenZipWorker {
public:
	static bool compress(const char *in_path, const char *out_file_name); // 对目录进行压缩，example: in_path d:\\work\\folder     out_file_name d:\\folder\\folder.7z
	static bool uncompress(const char *in_file_name, const char *out_path, void (*persent)(double));// 对目录进行解压缩，example: in_file_name d:\\folder\\folder.7z     out_path e:\\test
	static bool displayUnZipFiles(const char *in_file_name);
	static void displayFilenames();
	~SevenZipWorker(){}
	//存放所有文件名
	enum FileType {NOTHING, ARCH, FOLDER};
public:
//private:
	SevenZipWorker();
	static std::vector<std::string> m_allFilename;
	static FileType initDir(const char *dir);
	//遍历目录 dir 下由 filespec 指定的文件类型(可使用 * ？ 等通配符) 
	static bool realTraveseDir(const char *dir, const char *filespec);
	static bool traveseDir(const char *dir);
	static double getUnZipCompletedPersent();
	static double getZipCompletedPersent();

	static unsigned int fileNumber; // 文件总数
	static unsigned int zipFileNumber; // 已压缩的文件总数
	static unsigned int folderNumber; // 子文件夹总数

	static unsigned int unZipFiles; // 压缩文件里的总文件数
	static unsigned int completedFiles; // 压缩文件里已经解压的文件数

private:
	//存放初始目录的绝对路径，以'\'结尾  
	static char m_szInitDir[_MAX_PATH];
	//存放文件夹所在目录的绝对路径
	static char m_folderDir[_MAX_PATH];
	static void(*persent_ptr)(double persent);
};

#endif _SEVEN_ZIP_WORKER_H