cmake_minimum_required(VERSION 3.14)

# 项目名 相当于设置全局变量PROJECT_NAME
project(socket-server)

# C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 库编译

# 引入头文件目录
include_directories(include)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    include_directories(/usr/include)
elseif(CMAKE_SYSTEM_NAME STREQUAL "MacOS")
    include_directories(/usr/local/include)
endif()

# 查找头文件路径
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(Boost REQUIRED)  # mac用boost；linux用Boost
elseif(CMAKE_SYSTEM_NAME STREQUAL "MacOS")
    find_package(boost REQUIRED)  # mac用boost；linux用Boost
endif()

# 引入源文件
file(GLOB SRC_FILES "src/*.cpp")

# 可执行文件编译
add_executable(${PROJECT_NAME} src/main.cpp ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} ${boost_LIBRARES} pthread)
