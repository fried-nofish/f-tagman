#! TODO: configure the build process for application source

project(ftmapi)

set(LIB_SOURCE_FILES api.h api.cpp)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCE_FILES})
