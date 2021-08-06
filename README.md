# NDK_jni_cmake

** a demo witrojecth cmake build a NDK project **
### 概念辨义：
1.**gcc**
   > 它是GNU Compiler Collection（就是GNU编译器套件），也可以简单认为是编译器，它可以编译很多种编程语言（括C、C++、Objective-C、Fortran、Java等等）。
只有一个源文件时，直接就可以用gcc命令编译它。
如果程序包含很多个源文件时，用gcc命令逐个去编译时工作量会很大，所以出现了下面make工具。

2.**make**
   > make工具可以看成是一个智能的批处理工具，它本身并没有编译和链接的功能，而是用类似于批处理的方式—通过调用makefile文件中用户指定的命令来进行编译和链接的。

3.**makefile**
> makefile处理一些规则，告诉make工具怎么做，make工具就根据makefile中的命令进行编译和链接的。
makefile命令中就包含了调用gcc（也可以是别的编译器）去编译某个源文件的命令。
makefile需要手工编写，当工程非常大的时候，手写makefile非常麻烦，如果换了个平台makefile又要重新修改，于是就需要更强大的Cmake工具简化编译流程。

4.**cmake**
  > cmake就可以更加简单的生成makefile文件给make使用。当然cmake更强大之处在于，可以跨平台生成对应平台能用的makefile，我们就不用再自己去修改了。
可是cmake根据什么生成makefile呢？它又要根据一个叫CMakeLists.txt文件去生成makefile。
所以使用cmake我们只需要编写CMakeLists.txt就可以了。

6.**nmake**
> nmake是Microsoft Visual Studio中的附带命令，需要安装VS，实际上可以说相当于linux的make

      在Android Studio 2.2及以上,构建原生库的默认工具是CMake
CMake是一个跨平台的构建工具,可以用简单的语句来描述所有平台的安装(编译过程)。能够输出各种各样的makefile或者project文件。CMake并不直接构建出最终的软件,而是产生其他工具的脚本(如makefile),然后再依据这个工具的构建方式使用。
CMake是一个比make更高级的编译配置工具,它可以根据不同的平台、不同的编译器,生成相应的makefile或者vcproj项目,从而达到跨平台的目的。Android Studio利用CMake生成的是ninja, ninja是一个小型的关注速度的构建系统。我们不需要关心ninja的脚本,知道怎么配置CMake就可以了。
CMake其实是一个跨平台的支持产出各种不同的构建脚本的一个工具。
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
文件操作命令：
   ```cmake
   #将message写入filename文件中,会覆盖文件原有内容
file(WRITE filename "message")

#将message写入filename文件中,会追加在文件末尾
file(APPEND filename "message")

#从filename文件中读取内容并存储到var变量中,如果指定了numBytes和offset
#则从offset处开始最多读numBytes个字节,另外如果指定了HEX参数,则内容会以十六进制形式存储在var变量中
file (READ filename var [LIMIT numBytes] [OFFSET offset] [HEX])

#重命名文件
file(RENAME <oldname> <newname>)

#删除文件, 等于rm命令
file (REMOVE [file1...])

#递归的执行删除文件命令,等于rm-r
file (REMOVE RECURSE [file1…])

#根据指定的url下载文件
#timeout超时时间;下载的状态会保存到status中;下载日志会被保存到log; sum指定所下载文件预期的MD5值,如果指定会自动进行比对
#如果不一致,则回一个错误: SHOW PROGRESS,进度信息会以状态信息的形式被打印出来
file(DOWNLOAD url file[TIMEOUT timout][STATUS status][LOG log][EXPECTED_MD5 sum][SHOW_PROGRESS])

#创建目录
file(MAKE DIRECTORY [dirl dir2…])

# 会把path转换为以unix的/开头的cmake风格路径,保存在result中
file(CMAKE_PATH path result)

#它会把cmake风格的路径转换为本地路径风格: windows下用"\",而unix下用"/"
file(TO_CMAKE_PATH path result)

#将会为所有匹配查询表达式的文件生成一个文件list,并将该list存储进交量variable里,如果一个表达式指定了RELATIVE,返回的结果
#将会是相对于给定路径的相对路径,查询表达式例子: *.cxx, *.vt?
#NOTE:按照官方文档的说法,不建议使用file的GLOB指令来收集工程的源文件
file(GLOB variable [RELATIVE path] [globbing expressions]…)
   ```
#####set_directory_properties命令 
  **set_directory_properties(PROPERTIES prop1 value1 prop2 value2)**
 >设置路径的一种,参数propl, prop2代表属性,取值为:
INCLUDE_DIRECTORIES 包含目录
LINK_DIRECTORIES  连接目录
INCLUDE_REGULAR_EXPERSSION 正则表达式
ADDITIONAL_MAKE_CLEAN_FILES 额外清理文件

#####set_property命令
   ```cmake
   set_property(<GLOBAL
DIRECTORY [dir] |
TARGET [target ...] I
SOURCE [src1...] |
TEST [testl ...]|
CACHE [entry1 ...]>
[APPEND]
PROPERTY <name> [value ...])
   ```
   > 在给定的作用域内设置一个命名的属性
第一个参数决定了属性可以影响的作用域：
DIRECTORY：默认当前路径，也可以用[dir]指定路径
TARGET：目标作用域，可以是0个或多个已有目标
SOURCE：源文件作用域，可以是0个或多个源文件
TEST：测试作用域，可以是0个或多个已有的测试
CACHE：必须指定0个或多个cache中已有的条目
   
#####多个源文件处理
   如果源文件很多，把所有文件一个个加入很麻烦，可以使用
aux_source_directory命令或file命令，会查找指定目录下的所有源文
件，然后将结果存进指定变量名。
```cmake
cmake_minimum_required(VERSION 3.4.1)
# 查找当前目录所有源文件 并将名称保存到 DIR_SRCS
变量
#不能查找子目录
aux_source_directory(. DIR_SRCS)
#也可以使用
# file(GLOB DIR_SRCS *.c  *.cpp)

add_library(
native-lib
SHARED
${DIR_SRCS})
```
#####多目录多源文件处理
* 主目录中的CMakeLists.txt中添加add_subdirectory(child）命令，指明本项目包含一个子项目child。并在target_link_libraries
指明本项目需要链接一个名为child的库.
* 子目录child中创建CMakeLists.txt， 这里child编译为共享库。
```cmake
   cmake_minimum_required(VERSION 3.4.1)
aux_source_directory(. DIR_SRCS)
#添加 child 子目录下的cmakelist
add_subdirectory(child)

add_library(
native-lib
SHARED
${DIR_SRCS})
target_link_libraries(native-lib child)
############################
#child目录下的CMakeLists.txt：
cmake_minimum_required(VERSION 3.4.1)
aux_source_directory(. DIR_LIB_SRCS)add_library(
child
SHARED
${DIR_LIB_SRCS})
```
 
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
