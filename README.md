# 7zlib
一个封装了 7z 压缩解压功能的接口

### 使用
####压缩
7zlib.exe a "e:\pro\folder" "d:\folder.7z"

####解压
7zlib.exe x "d:\folder.7z" "e:\pro\folder"

### 说明
* main.cpp 里的 #define DEBUG_7Z 包含压缩解压调试信息， #define LIB_MAIN 包含 main 函数入口，去掉的话可以把工程编译成 .lib 库使用
* .exe 需要 7z.dll 支持(Debug 文件夹里包含)
