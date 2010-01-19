project(worldzor)

find_package(SDL)
find_package(OpenGL)
find_package(Boost)

if(NOT SDL_FOUND)
	message(FATAL_ERROR "SDL not found!" )
endif(NOT SDL_FOUND)

if(NOT OPENGL_FOUND)
	message(FATAL_ERROR "OpenGL not found!" )
endif(NOT OPENGL_FOUND)

include_directories(${OPENGL_INCLUDE_DIR} ${SDL_INCLUDE_DIR})

set(SHARED_SOURCES 
	angle
	camera
	engine
	geometry
	texture
	gta_style
	map
	matrix3x3
	matrix4x4
	obj
	vbo
	vector2
	vector3
	vector4
	objects/abstract_object
	states/abstract_state
	states/play_state
	states/test_state
)

set(MAIN_SOURCES main ${SHARED_SOURCES})
if(APPLE)
	set(MAIN_SOURCES ${MAIN_SOURCES} sdl/SDLMain.m)
endif(APPLE)

add_executable(worldzor main ${MAIN_SOURCES})
#add_executable(testzor test ${SHARED_SOURCES})
target_link_libraries(worldzor ${SDL_LIBRARY} ${OPENGL_LIBRARIES})
#target_link_libraries(testzor ${SDL_LIBRARY} ${OPENGL_LIBRARIES})
#add_test(Test testzor)
