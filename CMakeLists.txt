cmake_minimum_required(VERSION 3.14)

# 项目名 相当于设置全局变量PROJECT_NAME
project(socket-server)

message(STATUS "System Platform: " ${CMAKE_SYSTEM_NAME})

# C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# cmake v3.20后，引入第三方库推荐使用跨平台写法（通过CONFIG引入）
find_package(Boost REQUIRED CONFIG COMPONENTS system)

# 引入源文件
file(GLOB SRC_FILES "src/*.cpp")
# 可执行文件编译
add_executable(${PROJECT_NAME} src/main.cpp ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} ${boost_LIBRARES} pthread)
