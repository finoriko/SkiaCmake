# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.


set(SKIA_DIR ${CMAKE_SOURCE_DIR}/src/main/jniLibs)

include_directories(
${CMAKE_SOURCE_DIR}/src/main/cpp/include
${CMAKE_SOURCE_DIR}/src/main/cpp/include/android
${CMAKE_SOURCE_DIR}/src/main/cpp/include/c
${CMAKE_SOURCE_DIR}/src/main/cpp/include/codec
${CMAKE_SOURCE_DIR}/src/main/cpp/include/config
${CMAKE_SOURCE_DIR}/src/main/cpp/include/core
${CMAKE_SOURCE_DIR}/src/main/cpp/include/effects
${CMAKE_SOURCE_DIR}/src/main/cpp/include/encode
${CMAKE_SOURCE_DIR}/src/main/cpp/include/gpu
${CMAKE_SOURCE_DIR}/src/main/cpp/include/pathops
${CMAKE_SOURCE_DIR}/src/main/cpp/include/ports
${CMAKE_SOURCE_DIR}/src/main/cpp/include/private
${CMAKE_SOURCE_DIR}/src/main/cpp/include/svg
${CMAKE_SOURCE_DIR}/src/main/cpp/include/utils
${CMAKE_SOURCE_DIR}/src/main/cpp/include/views
)


add_library(lib_arcore SHARED IMPORTED)
set_target_properties(lib_arcore PROPERTIES IMPORTED_LOCATION
    ${SKIA_DIR}/${ANDROID_ABI}/libarcore.so)

add_library(lib_skottie_android SHARED IMPORTED)
set_target_properties(lib_skottie_android PROPERTIES IMPORTED_LOCATION
    ${SKIA_DIR}/${ANDROID_ABI}/libskottie_android.so)

add_library(lib_skqp_app SHARED IMPORTED)
set_target_properties(lib_skqp_app PROPERTIES IMPORTED_LOCATION
    ${SKIA_DIR}/${ANDROID_ABI}/libskqp_app.so)

add_library(lib_viewer SHARED IMPORTED)
set_target_properties(lib_viewer PROPERTIES IMPORTED_LOCATION
    ${SKIA_DIR}/${ANDROID_ABI}/libviewer.so)


add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib
                       jnigraphics

                       lib_arcore
                       lib_skottie_android
                       lib_skqp_app
                       lib_viewer

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )