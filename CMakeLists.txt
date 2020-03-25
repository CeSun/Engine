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
include_directories(${CMAKE_SOURCE_DIR}/src)

# 设置服务端相关的文件
set (ServerFile
        # 服务端的文件放到这里
        src/Server/CMessage/CMessage.cpp
        src/Server/CServer/CServer.cpp)
set (ClientFile
        # 客户端的文件添加到这里
        src/Client/CClient/CClient.cpp
        src/Client/base/CShader/CShader.cpp
        src/Client/base/CCamera/CCamera.cpp
        src/Client/base/CTexture/CTexture.cpp
        src/Client/CWorld/CWorld.cpp
        src/Client/base/CEntity/CEntity.cpp
        src/Client/base/CModel/CModel.cpp
        src/Client/base/CCube/CCube.cpp
        src/Client/base/CSkyBox/CSkyBox.cpp
        src/Client/CShaderMgr/CShaderMgr.cpp
        src/Client/CTextureMgr/CTextureMgr.cpp
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
    MESSAGE(STATUS "当前为Windows系统")
    IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        MESSAGE(STATUS "正在配置MSVC编译器的静态库")
        target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/lib/msvc_static_lib/glad.lib)
        target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/lib/msvc_static_lib/glfw3.lib)
    ELSEIF(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
        MESSAGE(STATUS "正在配置GCC编译器的静态库")
        target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/lib/win_static_lib/libglad_x64.a)
        target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/lib/win_static_lib/libglfw3_x64.a)
    ELSE()
        MESSAGE(FATAL_ERROR  "${CMAKE_CXX_COMPILER_ID}编译器不支持")
    ENDIF()
ELSEIF(UNIX AND NOT APPLE)
    IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        MESSAGE(STATUS "正在配置GCC编译器的静态库")
        #linux下需要以下依赖
        #sudo apt-get install xorg-dev libglu1-mesa-dev
        MESSAGE(STATUS "is like Unix")
        target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/lib/linux_static_lib/glad.a)
        target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/lib/linux_static_lib/libglfw3.a)
        target_link_libraries(Engine GL m Xrandr Xi X11 Xxf86vm pthread dl Xinerama Xcursor)
    ELSE()
        MESSAGE(FATAL_ERROR  "${CMAKE_CXX_COMPILER_ID}编译器不支持")
    ENDIF()
ELSEIF(APPLE)
    IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        MESSAGE(STATUS "当前为MacOS系统")
        MESSAGE(STATUS "正在配置GCC编译器的静态库")
        target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/lib/mac_static_lib/libGLAD.a)
        target_link_libraries(Engine ${PROJECT_SOURCE_DIR}/lib/mac_static_lib/libglfw3.a)
        target_link_libraries(Engine ${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/Cocoa.framework )
        target_link_libraries(Engine ${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/IOKit.framework )
        target_link_libraries(Engine ${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/OpenGL.framework )
        target_link_libraries(Engine ${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/CoreVideo.framework )
    ELSE()
        MESSAGE(FATAL_ERROR  "${CMAKE_CXX_COMPILER_ID}编译器不支持")
    ENDIF()
ENDIF()
MESSAGE(STATUS CMAKE_CURRRENT_BINARY_DIR)


