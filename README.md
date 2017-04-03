# 7zlib
一个封装了 7z 压缩解压功能的接口

### 使用
压缩 : 7zlib.exe a "e:\pro\folder" "d:\folder.7z"

解压 : 7zlib.exe x "d:\folder.7z" "e:\pro\"

### 说明
* 本工程提取 7z 16.04 源代码中压缩解压相关部分(具体是 CPP\7zip\UI\Client7z 下的工程)，修改成可用的压缩解压接口
* main.cpp 里的 #define DEBUG_7Z 包含压缩解压调试信息， #define LIB_MAIN 包含 main 函数入口，去掉的话可以把工程编译成 .lib 库使用。使用编译的静态库需要 .lib，SevenZipWorker.h，7z.dll 文件
* .exe 需要 7z.dll 支持(Debug 文件夹里包含)
* 工程编译环境为 win7 + vs2013，linux 可以使用 p7zip
* 用该接口压缩的文件也可以使用 7z 或 winrar 等工具解压缩
