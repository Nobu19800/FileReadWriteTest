cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(FileReadWriteTest VERSION 1.0)

add_library(FileReadWriteTestUtil STATIC FileReadWriteTestUtil.cpp FileReadWriteTestUtil.h)

add_executable(FileWriteTextTest FileWriteTextTest.cpp)
target_link_libraries(FileWriteTextTest FileReadWriteTestUtil)

add_executable(FileReadTextTest FileReadTextTest.cpp)
target_link_libraries(FileReadTextTest FileReadWriteTestUtil)

add_executable(FileWriteBinaryTest FileWriteBinaryTest.cpp)
target_link_libraries(FileWriteBinaryTest FileReadWriteTestUtil)

add_executable(FileReadBinaryTest FileReadBinaryTest.cpp)
target_link_libraries(FileReadBinaryTest FileReadWriteTestUtil)