cmake_minimum_required(VERSION 3.28.3)
project(trading_orchestrator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(config)
add_subdirectory(common)

add_executable(trading_orchestrator main.cpp)
target_link_libraries(trading_orchestrator 
    PRIVATE 
        config 
        common
)