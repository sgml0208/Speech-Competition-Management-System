#声明要求的cmake最低版本
cmake_minimum_required(VERSION 3.26)   # C:\Program Files\cmake-3.26.0-rc5-windows-x86_64\bin\cmake.exe

#声明一个cmake工程
project("Speech-Competition-Management-System")

#设置c++版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_C_COMPILER "D:/Dev-Cpp/mingw64/bin/gcc.exe")
# set(CMAKE_CXX_COMPILER "D:/Dev-Cpp/mingw64/bin/g++.exe")

# 添加警告调试信息
add_definitions(-Wall -g)

#添加头文件  ${PROJECT_SOURCE_DIR}是一个内置变量，它代表了项目的源代码根目录。include是相对于项目源代码根目录的路径。
include_directories(${PROJECT_SOURCE_DIR}/include)

#添加可执行程序
add_executable(speech-system 
        main.cpp
        src/speechManager.cpp
        src/speaker.cpp
) 

# # #把可执行程序链接到库文件上
# target_link_libraries(main ${库名_LIBRARIES})




