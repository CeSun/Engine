cmake_minimum_required(VERSION 3.15)
project(Engine)

#C++标准11
set(CMAKE_CXX_STANDARD 11)

#头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(Engine LearnGl/main.cpp)

#静态库
IF (WIN32)
    MESSAGE(STATUS "当前视窗系统")
    target_link_libraries(Engine ${CMAKE_SOURCE_DIR}/lib/win_static_lib/libglad_debug.a)
    target_link_libraries(Engine ${CMAKE_SOURCE_DIR}/lib/win_static_lib/libglfw3.a)

ELSEIF(UNIX && !APPLE)
    MESSAGE(STATUS "当前类Unix系统(不包括OSX)")
    target_link_libraries(Engine ${CMAKE_SOURCE_DIR}/lib/linux_static_lib/glad.a)
    target_link_libraries(Engine ${CMAKE_SOURCE_DIR}/lib/linux_static_lib/libglfw3.a)
    target_link_libraries(Engine  GL m Xrandr Xi X11 Xxf86vm pthread dl Xinerama Xcursor)
ELSEIF(APPLE)
    MESSAGE(ERROR "暂不支持OSX平台")
ENDIF()