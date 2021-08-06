# NDK_jni_cmake

** a demo witrojecth cmake build a NDK project **

### Cmake语法：

##### 1.单行注释 ：# xxx

##### 2.多行注释：
#[[ xxx
xxxxx
]]

##### 3.变量
```cmake
# Cmake中所有变量都是String类型
set(变量名 变量值) #声明变量：
set(var 12)
unset() #移除变量
${变量名} # 引用变量:
message("var = ${var}")
```

##### 4.列表
```cmake
set(列表名 值a 值b 值c ...)
set(列表名 “值1;值2;值3”)
set(list_var 1 3 5)
//或
set(list_var "1;3;5")
使用：
message("list = ${list_var}")
```

##### 5.操作符
```cmake
# 一元操作符：
EXIST, COMMAND, DEFINED
# 二元：
EQUAL, _ESS, LESS_EQUAL,GREATER, GREATER_EQUAL,
STREQUAL, STRLESS, STRLESS_EQUAL, STRGREATER,
STRGREATER_EQUAL, VERSION_EQUAL, VERSION_LESS,
VERSION_LESS_EQUAL, VERSION_GREATER,
VERSION_GREATER_EQUAL, MATCHES
# 逻辑：
NOT, AND, OR 
# true:
1,ON,YES,TRUE,Y,非0值

# false:
0,OFF,NO,FALSE,N,IGNORE,NOTFOUND,空字符串，以-NOTFOUND结尾的字符串

```

##### 4.条件控制
```cmake
set(if_tap OFF)
set(elseif_tap ON)

if(${if_tap})
  message("---if")
elseif(${elseif_tap})
    message("---elseif")
else(${if_tap})
   message("---else")
endif(${if_tap})
```

##### 5.循环命令
```cmake
set(str " ")
while(NOT str STREQUAL "xxxx")
  set(str "${str}x")
  message("str = ${str}")
  if(Y str STREQUAL "xx")
    break()
  endif
endwhile()
```

##### 6.遍历
```cmake
foreach(items 11 12 13 14 15)
    if(${items} EQUAL 13)
        break()
    endif()
    message("item = ${items}")
endforeach()
```

```cmake
foreach(items RANGE 3)
    message("item = ${items}")
endforeach()
```

*步长*
```cmake
foreach(items RANGE 1 7 2)
    message("item = ${items}")
endforeach()
```

```cmake
set(list1 1 2 3 4)
foreach(item IN LISTS list1)
    message("item = ${item}")
endforeach(item)
```

##### 7.自定义函数
```cmake
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
```
##### 8.自定义宏命令,mine是变量名
```cmake
macro(mine x y z)
    message("call macro ma")
    message("x = ${x}")
    message("y = ${y}")
    message("z = ${z}")
endmacro(mine)
mine("hello" "mm" "Iam hungry")
```

##### 9.变量作用域
1. 全局变量：
   整个项目可见，在set定义变量时指定为CACHE参数
2. 目录变量：
   在当前目录CMakeLists.txt中定义，以及在该文件include的其他cmake文件中定义的变量
3. 函数变量：
   在命令函数中定义的变量，类似java中的局部变量

### CMakeList.txt文件详解：
```cmake
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# cmake最低支持的版本
cmake_minimum_required(VERSION 3.10.2)
# 工程的名称
project("cmake_jni")

# 查找当前目录所有源文件，将源文件列表保存在DIR_SRCS变量中，不能查找子目录
#aux_source_directory( .DIR_SRCS)

#[[
 情况1：添加一个库
param0 添加一个库文件，库文件名称，如 为native-lib
param1 指定库的类型：静态库STATIC,动态库SHARED,MODULE（在使用dyld的系统有效）
param2 EXCLUDE_FROM_ALL 表示该库不会被默认构建
param3 指定库的源文件， 如 native-lib.cpp

 情况2：导入/添加一个已经存在的预编译库，通常与set_target_properties一起使用
param0: 库名称
param1: 同样是STATIC/SHARED/MODULE
param2:指定参数IMPORTED，通用参数
如：
add_library(test SHARED IMPORTED)
set_target_properties(
    test #目标库名
    PROPERTIES IMPORTED_LOCATION # 设置的参数
    库路径/${ANDROID_ABI}/libtest.so #导入库的路径
)
]]

add_library( # Sets the name of the library.
             native-lib
             SHARED
             native-lib.cpp )

find_library(
              log-lib
              log )

#[[
将若干库链接到目标库文件,允许循环依赖
链接规则要符合gcc链接顺序规则：被链接的被依赖的库应放后面，
即若lib1依赖lib2,lib2依赖lib3,顺序应是lib1 lib2 lib3;
]]
target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
```
##### set常用命令：
```cmake
# 设置可执行文件的输出路径，全局变量
set(EXECUTABLE_OUTPUT_PATH [output_path])
# 设置库文件的输出路径，全局变量
set(LIBRARY_OUTPUT_PATH [output path])
# 设置C++编译参数，全局变量
set(CMAKE_CXX_FLAGS "-Wall std=c++11")
# 设置源文件集合，本地自定义变量
set(SOURCE_FILES main.cpp test,cpp...)
```
##### -include_directories
设置头文件目录，相对于g++中-I参数，可以使用相对路径，绝对路径，或者自定义变量
```cmake
include_directories(./include ${MY_INCLUDE})
```
##### add_executable(<name> ${SRC_LIST})
添加可执行文件

##### add_subdirecroty(sub_dir [binary_dir])
若当前目录下还有子目录，且子目录也包含了一个CMakeList.txt
sub_dir 包含CmakeLists.txt和源码文件的子目录路径
binary_dir 输出路径，可选参数，一般不用指定

##### 常用命令 -file
[常用命令-file.png]


....

### build.gradle配置
 ```groovy
android {
    compileSdkVersion 30
    buildToolsVersion "30.0.2"

    defaultConfig {
        applicationId "com.xxx.code.cmake_jni"
        minSdkVersion 21
        targetSdkVersion 30
        versionCode 1
        versionName "1.0"
        
        externalNativeBuild {
            cmake {
                // 使用的编译器clang/gcc        
                arguments "-DANDROID_TOOLCHAIN=clang", 
                // cmake默认是gnustl_static        
                "-DANDROID_STL=gnustl_static"
                // 指定cflags和cppflags,效果和cmakelist一样
                cppFlags ""
                cFlags ""
                // 指定cpu架构
                abiFilters "armeabi-v7a"
            }
        }
    }
    buildTypes {/*...*/}
    externalNativeBuild {
        cmake {
            // 指定CMakeLists.txt文件相对当前build.gradle的路径
            path "src/main/cpp/CMakeLists.txt"
            version "3.10.2"
        }
    }
}
```