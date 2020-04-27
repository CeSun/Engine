cmake_minimum_required(VERSION 3.15)

#GameEngine Client

project(Client)

set(CMAKE_CXX_STANDARD 11)


# 头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../src)

# 编译文件配置


set (ClientFile
    "CClient/CClient.cpp"
    "base/CShader/CShader.cpp"
    "base/CCamera/CCamera.cpp"
    "base/CTexture/CTexture.cpp"
    "CWorld/CWorld.cpp"
    "base/CEntity/CEntity.cpp"
    "base/CModel/CModel.cpp"
    "base/CCube/CCube.cpp"
    "base/CSkyBox/CSkyBox.cpp"
    "CShaderMgr/CShaderMgr.cpp"
    "CTextureMgr/CTextureMgr.cpp"
    "base/CLight/CLight.cpp"
    "CLightMgr/CLightMgr.cpp"
    "base/CModel/CMesh/CMesh.cpp"
    )
## Imgui编译文件
set (ImguiFile 
    "libraries/imgui/imgui.cpp"
    "libraries/imgui/imgui_impl_glfw.cpp"
    "libraries/imgui/imgui_impl_opengl3.cpp"
    "libraries/imgui/imgui_impl_opengl3.cpp"
    "libraries/imgui/imgui_draw.cpp"
    "libraries/imgui/imgui_widgets.cpp"
)
add_executable(Client
    main.cpp
    ${ClientFile}
    ${ImguiFile}                   
)
# 动态库配置


# 设置输出目录
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../build/Client)
# 设置输出二进制名称
set_target_properties(Client PROPERTIES OUTPUT_NAME "GameClient")

FIND_LIBRARY(RUNTIME_LIB "${EXECUTABLE_OUTPUT_PATH}/libraries/" NO_DEFAULT_PATH)

# 静态库配置
set(MSVC_LIB 
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/msvc_static_lib/glad.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/msvc_static_lib/glfw3.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/msvc_static_lib/assimp.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/msvc_static_lib/zlib.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/msvc_static_lib/IrrXML.lib"
)

set (MINGW_LIB
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/win_static_lib/libglad_x64.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/win_static_lib/libglfw3_x64.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/win_static_lib/libassimp.dll.a"
)

set (GCC_LIB
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/linux_static_lib/glad.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/linux_static_lib/libglfw3.a"
    "GL m Xrandr Xi X11 Xxf86vm pthread dl Xinerama Xcursor"
)

set (MAC_GCC_LIB
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/mac_static_lib/libGLAD.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/mac_static_lib/libglfw3.a"
)

        MESSAGE(STATUS ${MSVC_LIB})
#跨平台的静态库配置
IF (WIN32)
    MESSAGE(STATUS "当前为Windows系统")
    IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        MESSAGE(STATUS "正在配置MSVC编译器的静态库")
        target_link_libraries(Client ${MSVC_LIB})
    ELSEIF(("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
        MESSAGE(STATUS "正在配置GCC编译器的静态库")
        target_link_libraries(Client ${MINGW_LIB})
    ELSE()
        MESSAGE(FATAL_ERROR  "${CMAKE_CXX_COMPILER_ID}编译器不支持")
    ENDIF()
ELSEIF(UNIX AND NOT APPLE)
    IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        MESSAGE(STATUS "正在配置GCC编译器的静态库")
        #linux下需要以下依赖
        #sudo apt-get install xorg-dev libglu1-mesa-dev
        MESSAGE(STATUS "is like Unix")
        target_link_libraries(Client ${GCC_LIB})
    ELSE()
        MESSAGE(FATAL_ERROR  "${CMAKE_CXX_COMPILER_ID}编译器不支持")
    ENDIF()
ELSEIF(APPLE)
    IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        MESSAGE(STATUS "当前为MacOS系统")
        MESSAGE(STATUS "正在配置GCC编译器的静态库")
        target_link_libraries(Client ${MAC_GCC_LIB})
        target_link_libraries(Client ${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/Cocoa.framework )
        target_link_libraries(Client ${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/IOKit.framework )
        target_link_libraries(Client ${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/OpenGL.framework )
        target_link_libraries(Client ${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/CoreVideo.framework )
    ELSE()
        MESSAGE(FATAL_ERROR  "${CMAKE_CXX_COMPILER_ID}编译器不支持")
    ENDIF()
ENDIF()
