cmake_minimum_required(VERSION 3.12)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

project(
	f-tagman
	VERSION 0.1.0
	DESCRIPTION "tag manager for native resources"
	HOMEPAGE_URL "https://github.com/NWPU-SRB-FishGroup/f-tagman"
	LANGUAGES C CXX
)

option(BUILD_test "build test programs" ON)

add_subdirectory(src)

if (BUILD_test)
	add_subdirectory(test)
endif()
