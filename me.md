## 1. CMakeLists.txt
这个文件是项目的核心
VS Code 的 C/C++ 插件现在对 CMake 支持极好（通过 CMake Tools 插件）。你只需要在根目录写好这个文件，VS Code 就能自动识别源文件。
```cmake
cmake_minimum_required(VERSION 3.15)
project(MyCppProject LANGUAGES CXX)

# 设置 C++ 标准 (2026年建议默认 C++20 或 C++23)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件
add_executable(MyApp
    src/main.cpp
    src/utils.cpp
)

# 如果有额外的包含目录
target_include_directories(MyApp PRIVATE ${CMAKE_SOURCE_DIR}/include)
```
## 2. .vscode/settings.json
用于告诉 VS Code 如何理解你的项目。如果你安装了 CMake Tools 插件，很多配置会自动生成，但你可能需要手动指定编译器。
```json
{
    "cmake.configureOnOpen": true, // 打开项目自动配置 CMake
    "C_Cpp.default.compilerPath": "/usr/bin/g++", // 或者 Windows 下的 "C:/mingw64/bin/g++.exe"
    "C_Cpp.default.cStandard": "gnu17",
    "C_Cpp.default.cppStandard": "gnu++20",
    "files.exclude": {
        "**/build": true // 在文件列表中隐藏 build 目录
    }
}
```

## 3. .vscode/launch.json
用于按 F5 进行断点调试。使用 CMake Tools 时，通常选择 `CMake: debug` 类型即可。
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "C++ Debug",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/build/MyApp", // 根据实际输出路径调整
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb", // Windows 下可能是 "miDebuggerPath": "C:/mingw64/bin/gdb.exe"
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "CMake: build" // 调试前自动执行构建任务
        }
    ]
}
```
## 不同场景的结构变体
### 场景一:简单的单文件学习/算法练习
如果你只是在刷 LeetCode 或写简单的测试代码，不需要复杂的 CMake 结构。
```text
AlgorithmPractice/
├── .vscode/
│   ├── settings.json
│   └── tasks.json (配置直接调用 g++ 编译当前文件)
├── 01_hello.cpp
├── 02_sort.cpp
└── ...
```
在这种模式下，`tasks.json` 会配置命令如 `g++ ${file} -o ${fileBasenameNoExtension}`。

## 场景二:大型库项目 (Header Only 或 静态库)
```text
MyLibrary/
├── include/mylib/   # 对外暴露的头文件
├── src/             # 内部实现源文件
├── tests/           # 测试用例
├── examples/        # 使用示例
└── CMakeLists.txt   # 配置为 BUILD_SHARED_LIBS 或 INSTALL 目标
```
## 总结
- 小型项目/学习：扁平结构，配合 tasks.json 直接编译。
- 正式项目/工作：必须使用 CMake，采用 src/include/build 分离结构，利用 .vscode 文件夹保存团队共享的配置，利用 CMake Tools 插件管理构建流程。