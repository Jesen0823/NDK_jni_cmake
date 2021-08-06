# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# 指定cmake最小支持版本
cmake_minimum_required(VERSION 3.10.2)
# 工程名称
project("NDK_jni_cmake")

#[[################### cmake语法测试 #################

# 声明变量
set(var 12)
# 使用变量
message("myVar = ${var}")

set(list_var 1 3 5)
message("list:${list_var}")

set(str "")
while(NOT str STREQUAL "OOOO")
    set(str "${str}O")
    message("str = ${str}")
    if(${str} STREQUAL "OOO")
        break()
    endif()
endwhile()

#遍历
foreach(items 11 12 13 14 15)
    if(${items} EQUAL 13)
        break()
    endif()
    message("item = ${items}")
endforeach()

# 函数
function(func x y z)
    message("call func")
    message("x = ${x}")
    message("y = ${y}")
    message("z = ${z}")
    message("ARGC ${ARGC}")
    message("arg1 = ${ARGV0} arg2 = ${ARGV1} arg3 = ${ARGV2}")
    message("all args = ${ARGV}")
endfunction()
func(7 8 9)

# 自定义宏命令,mine是变量名
macro(mine x y z)
    message("call macro ma")
    message("x = ${x}")
    message("y = ${y}")
    message("z = ${z}")
endmacro(mine)
mine("hello" "mm" "Iam hungry")

#[=[
/home/jesen/AndroidStudioProjects/Cmake_JNI/app/src/main/cpp下：
cmake
]=]

###########################################]]

############ ** 以下为项目编译配置 ** ############

# 1.设置头文件目录
# CMAKE_SOURCE_DIR：Cmake_Lists.txt文件所在当前目录
#include_directories(${CMAKE_SOURCE_DIR}/inc)
include_directories("inc")

# 2.添加一个库，根据native-lib.cpp源文件编译一个jni_cmake_lib动态库
#[[add_library(
        jni_cmake_lib
        SHARED
        native-lib.cpp )]]
#批量导入所有源文件,就不用一个个文件导入了
file(GLOB u-all-file *.c *.h *.cpp *.hpp)
add_library(
        jni_cmake_lib
        SHARED
        ${u-all-file}
)

#[[3.
查找系统库，如查找系统日志库log,赋值给变量log-lib
路径：
/home/jesen/Android/Sdk/ndk/21.1.6352462/platforms/android-21
/arch-arm/usr/lib/liblog.so

注：可以去掉find_library()，而target_link_libraries直接使用：
target_link_libraries(
                       native-lib
                       log)
]]
find_library( # Sets the name of the path variable. 自定义名称，目的防止多次查找
        u-log-lib

        log)

# 4.设置C++编译参数，全局变量,指定.so三方库路径，Cmake文件上一层的上一层是/main
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}")

# 5.链接，设置依赖的库，第一个参数必须是目标模块
target_link_libraries( # Specifies the target library.
        jni_cmake_lib
        # included in the NDK. 使用自定义名称，也可以直接用log
        ${u-log-lib}
        fmod
        fmodL
        )

