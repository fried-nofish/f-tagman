#! TODO: configure the build process for application source

aux_source_directory(. SOURCE_FILES)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
