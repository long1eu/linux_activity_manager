cmake_minimum_required(VERSION 3.5)
project(activity_manager)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-lncurses")

add_executable(
        activity_manager
        main.cpp
        src/Process.h
        src/ProcessParser.h
        src/ProcessContainer.h
        src/SysInfo.h
        src/constants.h
        src/Util.h src/Process.cpp src/ProcessParser.cpp src/ProcessContainer.cpp src/SysInfo.cpp src/Util.cpp)

target_link_libraries(${PROJECT_NAME} ncurses)