# CMakeList.txt: TEST 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。
project(Viewer)
include_directories(CameraFactorSDK/include)
link_directories(CameraFactorSDK)#lib目录
add_executable (${PROJECT_NAME} "Viewer.cpp" "Viewer.h")

IF (CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
    target_link_libraries(${PROJECT_NAME}  CameraFactory_x64)
    MESSAGE(STATUS  "Release CameraFactory_x64")
ELSE (CMAKE_BUILD_TYPE MATCHES "Debug")
    target_link_libraries(${PROJECT_NAME} CameraFactory_x64_d)
    MESSAGE(STATUS  "Debug CameraFactory_x64_d")
endif()
# TODO: 如有需要，请添加测试并安装目标。
