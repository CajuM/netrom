set (CMAKE_CXX_STANDARD 11)
set(BIN_DIR ${netrom_SOURCE_DIR}/dist/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/bin)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})
include_directories(include)

add_executable(netrom main.cpp Netrom.cpp Level.cpp GameObject.cpp)

target_link_libraries(netrom ${SDL2_LIBRARY})
target_link_libraries(netrom ${SDL2_TTF_LIBRARY})