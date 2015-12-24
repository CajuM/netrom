set (CMAKE_CXX_STANDARD 11)
set(BIN_DIR ${netrom_SOURCE_DIR}/dist/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/lib)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/dist/bin)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(PythonLibs 3.0 REQUIRED)

string(REGEX REPLACE [^0-9] "" boost_py_ver ${PYTHONLIBS_VERSION_STRING})
math(EXPR boost_py_ver ${boost_py_ver}/10)
find_package(Boost REQUIRED COMPONENTS filesystem system python-py${boost_py_ver})

include_directories(netrom
	${SDL2_INCLUDE_DIR}
	${SDL2_TTF_INCLUDE_DIR}
	${Boost_INCLUDE_DIRS}
	${PYTHON_INCLUDE_DIRS}
	include
)

list(APPEND pynetrom_src
	pynetrom.cpp
)

list(APPEND src
	main.cpp
	Netrom.cpp
	Level.cpp
	GameObject.cpp
	GameObjectList.cpp
	PyScript.cpp
)

add_executable(netrom ${src} ${pynetrom_src})

PYTHON_ADD_MODULE(pynetrom ${pynetrom_src})

target_link_libraries(netrom 
	${SDL2_LIBRARY}
	${SDL2_TTF_LIBRARY}
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
	${Boost_PYTHON-PY34_LIBRARY}
	${PYTHON_LIBRARIES}
)
