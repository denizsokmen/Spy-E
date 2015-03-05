# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (SpyE)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-1c73e35")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(
	external/glfw-3.0.3/include/GLFW/
	external/glm-0.9.4.0/
	external/glew-1.9.0/include/
	include/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	GLFW_303
	GLEW_190
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

add_executable(game 
	src/main.cpp
	src/Shader.cpp
	src/Camera.cpp
	src/Objloader.cpp
	src/Renderable.cpp
	src/VertexBuffer.cpp
	src/Label.cpp
	src/SubMesh.cpp
	src/Input.cpp
	src/Game.cpp
	src/Renderer.cpp
	src/Entity.cpp
	src/World.cpp
	src/Scene.cpp
	src/BoundingBox.cpp
	src/Physics.cpp
	src/PhysicsWorld.cpp
	src/Body.cpp
	src/Timer.cpp
	src/SystemController.cpp
	src/tinyxml2.cpp
	src/Exporter.cpp
	src/TestGameSystem.cpp
	src/Mesh.cpp

	include/Camera.h
	include/Renderable.h
	include/Shader.h
	include/Objloader.h
	include/Mesh.h
	include/VertexBuffer.h
	include/Label.h
	include/SubMesh.h
	include/Input.h
	include/Game.h
	include/Renderer.h
	include/World.h
	include/Entity.h
	include/Scene.h
	include/BoundingBox.h
	include/Body.h
	include/Physics.h
	include/PhysicsWorld.h
	include/Timer.h
	include/System.h
	include/SystemController.h
	include/tinyxml2.h
	include/Exporter.h
	include/TestGameSystem.h
)
target_link_libraries(game
	${ALL_LIBS}
)


# Xcode and Visual working directories
set_target_properties(game PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/" COMPILE_FLAGS "-std=c++11")
create_target_launcher(game WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/")


SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )


if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
add_custom_command(
   TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/game${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/game/"
)


elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

