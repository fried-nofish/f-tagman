set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

aux_source_directory(. SOURCE_FILES)
set(RC_FILES ${CMAKE_SOURCE_DIR}/assets/app.qrc)

qt_add_executable(${CMAKE_PROJECT_NAME} WIN32 ${SOURCE_FILES} ${RC_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Widgets)
