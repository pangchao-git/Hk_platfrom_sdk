# cmake_minimum_required(VERSION <specify CMake version here>)
project(hik_sdk_platform)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH D:/Softtware/Qt/qt5.11/5.11.3/mingw53_32)
#设置静态编译
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories("D:/Softtware/pc_libevnet_2.1.11/include")
link_directories("../lib/")
link_libraries(HikPlatformSDK CrashAPI)
add_executable(hik_sdk_platform main.cpp Sdk_Base.cpp include/Sdk_Base.h
        Platfrom_Server.cpp include/Platfrom_Server.h)

target_link_libraries(
        hik_sdk_platform
        HikPlatformSDK CrashAPI  hlog hpr
        libevent libevent_core libevent_extra ws2_32 Advapi32
        libCjson
         )