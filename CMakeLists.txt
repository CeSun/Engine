cmake_minimum_required(VERSION 3.15)
project(Engine)
#C++标准11
set(CMAKE_CXX_STANDARD 17)
#设置输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
#设置子项目
set(PROJECT "LEARN")

#头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

#
IF (${PROJECT} STREQUAL "LEARN")      #学习Opengl项目
    add_executable(Engine
            # 本项目参与编译的Cpp文件
            LearnGl/main.cpp
            LearnGl/Texture.cpp
            )
ELSEIF(${PROJECT} STREQUAL "ENGINE")  #Engine项目
    add_executable(Engine
            # 本项目参与编译的Cpp文件
            Engine/main.cpp
            )
ENDIF()




#跨平台的静态库配置
IF (WIN32)
    MESSAGE(STATUS "IS Windows System")
    target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/lib/win_static_lib/libglad_x64.a)
    target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/lib/win_static_lib/libglfw3_x64.a)
ELSEIF(UNIX AND NOT APPLE)
    #linux下需要以下依赖
    #sudo apt-get build-dep glfw
    #sudo apt-get install xorg-dev libglu1-mesa-dev
    MESSAGE(STATUS "is like Unix")
    target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/lib/linux_static_lib/glad.a)
    target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/lib/linux_static_lib/libglfw3.a)
    target_link_libraries(Engine  GL m Xrandr Xi X11 Xxf86vm pthread dl Xinerama Xcursor)
ELSEIF(APPLE)
    MESSAGE(ERROR "Not support OSX")
ENDIF()
MESSAGE(STATUS CMAKE_CURRRENT_BINARY_DIR)


