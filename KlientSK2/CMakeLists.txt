cmake_minimum_required(VERSION 3.14)
project(KlientSK2)

set(CMAKE_CXX_STANDARD 17)

set(SFML_INCLUDE_DIR "/home/matt/rewieer/Libraries/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "/home/matt/rewieer/Libraries/SFML-2.5.1/lib")
set(SFML_DIR "/home/matt/rewieer/Libraries/SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(KlientSK2 main.cpp Player.cpp Player.h)
target_link_libraries (KlientSK2 sfml-graphics sfml-window sfml-system)