cmake_minimum_required(VERSION 3.10)
project(lock_nodes_and_connections)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set Qt platform to xcb
add_definitions(-DQT_QPA_PLATFORM=xcb)

# Define whether QtNodes is shared or static
add_definitions(-DNODE_EDITOR_SHARED)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
# If you're using Qt5 instead of Qt6, uncomment the line below and comment the line above
# find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# Explicitly list source files instead of using GLOB_RECURSE
set(SOURCE_FILES
    main.cpp
    DelegateNodeModel.cpp
)

set(HEADER_FILES
    DataFlowModel.hpp
    DelegateNodeModel.hpp
)

add_executable(lock_nodes_and_connections 
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_link_libraries(lock_nodes_and_connections PRIVATE
    Qt::Core
    Qt::Widgets
    QtNodes
)

# Set include directories if needed
# target_include_directories(lock_nodes_and_connections PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
