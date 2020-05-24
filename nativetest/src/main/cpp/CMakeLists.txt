cmake_minimum_required(VERSION 3.4.1)

#set(GOOGLETEST_ROOT ~/Library/Android/sdk/ndk-bundle/sources/third_party/googletest/)
set(GOOGLETEST_ROOT ${ANDROID_NDK}/sources/third_party/googletest/)
add_library(gtest STATIC ${GOOGLETEST_ROOT}/src/gtest_main.cc ${GOOGLETEST_ROOT}/src/gtest-all.cc)
target_include_directories(gtest PRIVATE ${GOOGLETEST_ROOT})
target_include_directories(gtest PUBLIC ${GOOGLETEST_ROOT}/include)

add_library( # Sets the name of the library.
             main_unittest

             SHARED

             # Provides a relative path to your source file(s).
             main_test.cpp )

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

include_directories(${GOOGLETEST_ROOT}/include)
include_directories(../../../../app/src/main/cpp/include)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

#add_subdirectory(../../../../app/src/main/cpp, "${CMAKE_CURRENT_BINARY_DIR}/native-lib_build")
#add_subdirectory(lib, ../../../../app/build/intermediates/cmake/debug/obj)
#add_subdirectory(jni)
add_library(native-lib IMPORTED SHARED)
set_target_properties(native-lib PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/jni/lib/${ANDROID_ABI}/libnative-lib.so)
target_link_libraries( # Specifies the target library.
                       main_unittest

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       native-lib
                       gtest )

#add_executable(main_unittest main_test.cpp)
