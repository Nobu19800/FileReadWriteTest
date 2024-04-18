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


install(TARGETS FileWriteTextTest COMPONENT component)
install(TARGETS FileReadTextTest COMPONENT component)
install(TARGETS FileWriteBinaryTest COMPONENT component)
install(TARGETS FileReadBinaryTest COMPONENT component)

if(UNIX)
	include(GNUInstallDirs)
	install(FILES startFileReadWriteTest 
		DESTINATION ${CMAKE_INSTALL_BINDIR} 
		COMPONENT component 
		PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ  WORLD_READ WORLD_EXECUTE)
endif(UNIX)