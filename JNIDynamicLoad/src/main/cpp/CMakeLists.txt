cmake_minimum_required(VERSION 3.10.2)

# 工程名称
project("JNIDynamicLoad")

add_library( # Sets the name of the library.
        dynamic-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        jni/jni_dynamic_load.cpp )

include_directories(${CMAKE_SOURCE_DIR}/base/)

find_library( # Sets the name of the path variable.
        log-lib
        log )

target_link_libraries( # Specifies the target library.
        dynamic-lib
        ${log-lib} )