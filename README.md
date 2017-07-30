# 7zlib
一个封装了 7z 压缩解压功能的接口

### 使用
7zlib.exe a E:\\work\\test G:\\tmp\\test.7z  : Compress folder test to test.7z
7zlib.exe x G:\\tmp\\test.7z E:\\work\\test  : Extract files to folder test from test.7z
7zlib.exe l G:\\tmp\\test.7z   : List contents of test.7z

### 说明
* 本工程提取 7z 16.04 源代码中压缩解压相关部分(具体是 CPP\7zip\UI\Client7z 下的工程)，修改成可用的压缩解压接口
* main.cpp 里的 #define USE_MAIN 包含 main 函数入口，去掉的话可以把工程属性做适当修改即可编译成 .lib 库使用
* 工程编译环境为 win7 + vs2013 社区版
* 用该接口压缩的文件也可以使用 7z 或 winrar 等工具解压缩
