cmake_minimum_required(VERSION 3.8)

project(Template_OpenGL_Glew_Glfw)

set(CMAKE_CXX_STANDARD 11)

##### LIBRARIES #####

#set path of the FindXXX.cmake files
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

#find the library files using the FindXXX.cmake files
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)

#find includes in corresponding build directories
#i don't remember why that is
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

#add library include directories
include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} )

#set library path for mac
if(UNIX)
    set(ALL_LIBRARIES ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${GLFW_LIBRARY})
endif(UNIX)

#set flags for windows
if(WIN32)
    #should compile but hasn't been tested with those libraries
    #if doesn't compile check for wrong flag or wrong order
    set(ALL_LIBRARIES mingw32 glfw32 glew32s opengl32 )
endif(WIN32)

##### SOURCES #####

include_directories(include)

#set name of the directory containing all the sources files
set(SRC_DIRECTORY Project)

#get all header files
file(GLOB_RECURSE HEADER_FILES ${SRC_DIRECTORY}/*.hpp)

#get all source files
file(GLOB_RECURSE SRC_FILES ${SRC_DIRECTORY}/*.cpp)

#get all shader files
file(GLOB_RECURSE SHADER_FILES ${SRC_DIRECTORY}/*.glsl)

#set name of main file
set(MAIN ${SRC_DIRECTORY}/main.cpp)

##### CREATE MAKEFILE #####

#set name of the executable
set(OUTPUT executable)

#compile all the file stored in the variables
add_executable(${OUTPUT} ${MAIN} ${SRC_FILES} ${HEADER_FILES} ${SHADER_FILES} )

#link the libraries (the library variable is set in the main cmakelist.txt)
target_link_libraries(${OUTPUT} ${ALL_LIBRARIES})

#copy files to the executable directory
#file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#file(COPY textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

##### DEBUG #####

#if all files grey in CLion and red cross on build (or debug not found) -> build, click "build" in error popup, click ok -> let it do its thing -> try to build again
#if findXXX.cmake not included error -> look up a def of said file on the internet and include in CMake folder
#if lib not found through findXXX.cmake -> install said lib
#if '% error -> delete build files in cmake-build-debug folder
#if "Could not find cmake module file: CMakeDetermineProjectCompiler.cmake" check that project name in cmake hasn't got a space
