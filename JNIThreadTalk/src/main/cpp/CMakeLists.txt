cmake_minimum_required(VERSION 3.10.2)

project("JNIThreadInvoke")

add_library( # Sets the name of the library.
        thread-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ./jni_thread_test.cpp
        ./jni_thread_syn.cpp
        jni_product_consumer.cpp
        base/jvm.cpp)

include_directories(${CMAKE_SOURCE_DIR}/base/)

find_library( # Sets the name of the path variable.
        log-lib
        log)

target_link_libraries( # Specifies the target library.
        thread-lib
        ${log-lib})