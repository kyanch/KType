cmake_minimum_required(VERSION 3.11)
project(ktype)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_subdirectory(lib/wxwidgets)
# set(wxWidgets_LIBRARIES wx::net wx::core wx::base)
find_package(wxWidgets REQUIRED COMPONENTS net core base richtext)
if(wxWidgets_USE_FILE)
    include(${wxWidgets_USE_FILE})
endif()

file(GLOB ktype_SOURCES src/src/* )

add_executable(ktype ${ktype_SOURCES})
target_include_directories(ktype PRIVATE src/include)
target_link_libraries(ktype ${wxWidgets_LIBRARIES})