#ifndef _SEVEN_ZIP_WORKER_H
#define _SEVEN_ZIP_WORKER_H

#include <vector>

class SevenZipWorker {
public:
	static bool compress(const char *in_path, const char *out_file_name); // 对目录进行压缩，example: in_path d:\\work\\folder     out_file_name d:\\folder\\folder.7z
	static bool uncompress(const char *in_file_name, const char *out_path);// 对目录进行解压缩，example: in_file_name d:\\folder\\folder.7z     out_path e:\\test
	static void displayFilenames();
	static int getFileNumber();
	static int getFolderNumber();
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
private:
	//存放初始目录的绝对路径，以'\'结尾  
	static char m_szInitDir[_MAX_PATH];
	//存放文件夹所在目录的绝对路径
	static char m_folderDir[_MAX_PATH];
	static int m_fileNumber; // 文件总数
	static int m_folderNumber; // 子文件夹总数
};

#endif _SEVEN_ZIP_WORKER_H