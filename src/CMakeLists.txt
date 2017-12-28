include(FindPkgConfig)

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

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -rdynamic -Wall -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -rdynamic -Wall -Werror")

find_package(Boost REQUIRED COMPONENTS filesystem system)
if(NOT Boost_FILESYSTEM_FOUND)
	message(FATAL_ERROR "Need boost-filesystem")
endif()
if(NOT Boost_SYSTEM_FOUND)
	message(FATAL_ERROR "Need boost-system")
endif()

pkg_search_module(LUA REQUIRED luajit>=2.1)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)
pkg_search_module(SDL2 REQUIRED sdl2)


include_directories(
	${SDL2_INCLUDE_DIR}
	${SDL2_TTF_INCLUDE_DIR}
	${Boost_INCLUDE_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${LUA_INCLUDE_DIRS}
	${CMAKE_BINARY_DIR}
)


add_executable(netrom ${src})

target_link_libraries(netrom
	${SDL2_LIBRARIES}
	${SDL2_TTF_LIBRARIES}
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
        ${LUA_LIBRARIES}
)
