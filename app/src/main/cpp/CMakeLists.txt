# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

project("NDK_jni_cmake")

# 1.导入头文件
include_directories("inc")

#批量导入所有源文件,就不用一个个文件导入了
file(GLOB add-all-file *.c *.h *.cpp *.hpp)
add_library(
        jni_cmake_lib
        SHARED
        ${add-all-file}
)

find_library( # Sets the name of the path variable. 自定义名称，目的防止多次查找
        laputa-log-lib
        log)

# 2.导入库文件
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}")

# 3.链接
target_link_libraries( # Specifies the target library.
        jni_cmake_lib

        # Links the target library to the log library
        # included in the NDK. 使用自定义名称，也可以直接用log
        ${laputa-log-lib}
        fmod
        fmodL
        )