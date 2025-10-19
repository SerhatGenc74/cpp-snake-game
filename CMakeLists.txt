cmake_minimum_required(VERSION 3.5)

project(OYUN CXX)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


#add all executables
file(GLOB_RECURSE SOURCE 
    src/*.h
    src/*.cpp
    )

    
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

#include directories
set (INC_DIRECTORIES
    ${PROJECT_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIRS} 
    ${SDL2_IMAGE_INCLUDE_DIRS} 
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

    
    
set(SDL_LIBRARIES ${SDL2_LIBRARIES} SDL2_image)

add_executable(${PROJECT_NAME}  ${SOURCE}) 
include_directories(${PROJECT_NAME}  ${INC_DIRECTORIES})
target_link_libraries(${PROJECT_NAME}  ${SDL_LIBRARIES})