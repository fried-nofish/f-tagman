set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

aux_source_directory(. SOURCE_FILES)
set(RC_FILES ${CMAKE_SOURCE_DIR}/assets/app.qrc)

qt_add_executable(${CMAKE_PROJECT_NAME} MANUAL_FINALIZATION ${SOURCE_FILES} ${RC_FILES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE OFF)
else()
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE ON)
endif()

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Widgets)

qt_finalize_executable(${CMAKE_PROJECT_NAME})
