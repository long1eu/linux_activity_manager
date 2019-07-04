cmake_minimum_required(VERSION 3.5)
project(activity_manager)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-lncurses")

add_executable(
        activity_manager
        main.cpp
        Process.h
        ProcessParser.h
        ProcessContainer.h
        SysInfo.h
        constants.h
        util.h)

target_link_libraries(${PROJECT_NAME} ncurses)