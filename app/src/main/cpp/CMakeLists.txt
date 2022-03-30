# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("live")

include_directories(${CMAKE_SOURCE_DIR}/live)
include_directories(${CMAKE_SOURCE_DIR}/live/BasicUsageEnvironment)
include_directories(${CMAKE_SOURCE_DIR}/live/BasicUsageEnvironment/include)
include_directories(${CMAKE_SOURCE_DIR}/live/groupsock)
include_directories(${CMAKE_SOURCE_DIR}/live/groupsock/include)
include_directories(${CMAKE_SOURCE_DIR}/live/liveMedia)
include_directories(${CMAKE_SOURCE_DIR}/live/liveMedia/include)
include_directories(${CMAKE_SOURCE_DIR}/live/UsageEnvironment)
include_directories(${CMAKE_SOURCE_DIR}/live/UsageEnvironment/include)
include_directories(${CMAKE_SOURCE_DIR}/live/testProgs)

include_directories(${CMAKE_SOURCE_DIR}/openssl/${ANDROID_ABI}/include)

add_library(ssl SHARED IMPORTED)
set_target_properties(ssl PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/openssl/${ANDROID_ABI}/libssl.1.1.so)

add_library(crypto SHARED IMPORTED)
set_target_properties(crypto PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/openssl/${ANDROID_ABI}/libcrypto.1.1.so)

file(GLOB_RECURSE live-src
        live/BasicUsageEnvironment/*.cpp
        live/groupsock/*.cpp
        live/groupsock/*.c
        live/UsageEnvironment/*.cpp
        live/liveMedia/*.c
        live/liveMedia/*.cpp
        live/testProgs/testRTSPClient.cpp
        native-lib.cpp
        )


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        live

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${live-src})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        live
        ssl
        crypto
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})