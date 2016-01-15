if(MSVC AND NOT "${MSVC_VERSION}" LESS 1400)
	add_definitions( "/MP" )
endif()


add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
	-DSDL_STATIC
)



list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-1c73e35")





### GLFW ###


include_directories(
		glew-1.13.0/include/
	
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	-lGL -lGLU -lXrandr -lXext -lX11 -lrt
	${CMAKE_DL_LIBS}
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	${CMAKE_DL_LIBS}
)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")


### GLEW ###

set(GLEW_SOURCE
		glew-1.13.0/src/glew.c
)

set(GLEW_HEADERS
)



add_library( GLEW_190 STATIC
	${GLEW_SOURCE}
	${GLEW_INCLUDE}
)


target_link_libraries(GLEW_190
	${OPENGL_LIBRARY}
	${EXTRA_LIBS}
)


### SDL ###
set(DIRECTX OFF)
add_subdirectory(SDL2-2.0.4)

set(LIBTYPE SHARED)
add_subdirectory(openal-soft-1.17.1)


find_package(SDL2_image REQUIRED)



