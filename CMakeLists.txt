cmake_minimum_required(VERSION 3.15)

# Client 带服务端，用于局域网对战，一个玩家的电脑作为服务端
# Server 只有服务端，用于网络对战
# Server OR Client
set(program Client)
project(Engine)
#C++标准11
set(CMAKE_CXX_STANDARD 11)

#头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR})

# 设置服务端相关的文件
set (ServerFile
        # 服务端的文件放到这里
        src/Server/CMessage/CMessage.cpp
        src/Server/CServer/CServer.cpp)
set (ClientFile
        # 客户端的文件添加到这里
            src/Client/CClient/CClient.cpp
            src/Client/CDemo/CDemo.cpp
            src/Client/CShader/CShader.cpp
            src/Client/CCamera/CCamera.cpp
        )
IF (program STREQUAL Client)
    add_executable(Engine
        # 客户端入口
        src/Client/main.cpp
        ${ClientFile}
        ${ServerFile}
        )
    #设置输出目录
    SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/Client)
    set_target_properties(Engine PROPERTIES OUTPUT_NAME "GameClient")
ELSE()
    add_executable(Engine
            # 服务端入口
            src/Server/main.cpp
            ${ServerFile}
            )
    SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/Server)
    set_target_properties(Engine PROPERTIES OUTPUT_NAME "GameServer")

ENDIF()

#跨平台的静态库配置
IF (WIN32)
    MESSAGE(STATUS "IS Windows System")
    target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/lib/win_static_lib/libglad_x64.a)
    target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/lib/win_static_lib/libglfw3_x64.a)
ELSEIF(UNIX AND NOT APPLE)
    #linux下需要以下依赖
    #sudo apt-get install xorg-dev libglu1-mesa-dev
    MESSAGE(STATUS "is like Unix")
    target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/lib/linux_static_lib/glad.a)
    target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/lib/linux_static_lib/libglfw3.a)
    target_link_libraries(Engine GL m Xrandr Xi X11 Xxf86vm pthread dl Xinerama Xcursor)
ELSEIF(APPLE)
    MESSAGE(ERROR "Not support OSX")
ENDIF()
MESSAGE(STATUS CMAKE_CURRRENT_BINARY_DIR)


