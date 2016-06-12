set (CMAKE_CXX_STANDARD 11)

list(APPEND src
	main.cpp
	Netrom.cpp
	Level.cpp
	GameObject.cpp
	UIElement.cpp
	MsgBox.cpp
	GlyphMat.cpp
	Scene.cpp
	LuaScript.cpp
	LuaBindings.cpp
	Event.cpp
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++0x")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++0x")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(LuaJIT REQUIRED)


include_directories(
	${SDL2_INCLUDE_DIR}
	${SDL2_TTF_INCLUDE_DIR}
	${PYTHON_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${LUAJIT_INCLUDE_DIR}
	${CMAKE_BINARY_DIR}
)


add_executable(netrom ${src})

target_link_libraries(netrom 
	${SDL2_LIBRARY}
	${SDL2_TTF_LIBRARY}
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
        ${LUAJIT_LIBRARIES}
)
