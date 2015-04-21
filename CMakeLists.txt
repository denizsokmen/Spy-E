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


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-1c73e35")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

message("${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}  ${CMAKE_MODULE_PATH}")

find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)


if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(
	external/glm-0.9.4.0/
	external/glew-1.9.0/include/
	external/SDL2-2.0.3/include/
	external/openal-soft-1.16.0/include/
	include/
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	GLEW_190
	SDL2
	SDL2main
	${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
	openal
	
)

add_definitions(
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

add_library(engine STATIC
	src/graphics/Shader.cpp
	src/resource/ObjLoader.cpp
	src/graphics/Renderable.cpp
	src/graphics/VertexBuffer.cpp
	src/graphics/SubMesh.cpp
	src/graphics/Renderer.cpp
	src/graphics/Mesh.cpp
	src/graphics/Material.cpp

	src/world/Camera.cpp
	src/world/Entity.cpp
	src/world/World.cpp
	src/world/Scene.cpp
	src/world/WorldExporter.cpp
	src/world/EntityLoader.cpp

	src/physics/BoundingBox.cpp
	src/physics/Physics.cpp
	src/physics/PhysicsWorld.cpp
	src/physics/Body.cpp
	src/logic/Timer.cpp
	src/logic/SystemController.cpp
	src/logic/Game.cpp

	src/world/WorldLoader.cpp

	src/input/Input.cpp
	src/input/Device.cpp
	src/input/Keyboard.cpp
	src/input/ButtonHandler.cpp
	src/input/KeyboardButtonHandler.cpp
	src/input/MouseButtonHandler.cpp
	src/input/Mouse.cpp

	src/sound/Sounds.cpp
	include/sound/Sounds.h

	include/graphics/Renderable.h
	include/graphics/Shader.h
	include/resource/ObjLoader.h
	include/graphics/Mesh.h
	include/graphics/VertexBuffer.h
	include/graphics/SubMesh.h
	include/graphics/Renderer.h
	include/graphics/Texture.h
	include/graphics/Material.h

	include/input/Input.h
	include/input/Keyboard.h
	include/input/Device.h
	include/input/ButtonHandler.h
	include/input/KeyboardButtonHandler.h
	include/input/MouseButtonHandler.h
	include/input/Mouse.h
	
	include/world/World.h
	include/world/Entity.h
	include/world/Scene.h
	include/world/Camera.h
	include/world/WorldExporter.h
	include/world/EntityLoader.h

	include/physics/BoundingBox.h
	include/physics/Body.h
	include/physics/Physics.h
	include/physics/PhysicsWorld.h

	include/logic/Timer.h
	include/logic/System.h
	include/logic/SystemController.h
	include/logic/Game.h

	include/utils/rapidxml.hpp
	include/utils/rapidxml_iterators.hpp
	include/utils/rapidxml_print.hpp
	include/utils/rapidxml_utils.hpp
	include/world/WorldLoader.h

	src/graphics/Texture.cpp

	src/graphics/Material.cpp
	src/graphics/Drawer.cpp

	include/graphics/Drawer.h
	src/graphics/Drawable.cpp
	include/graphics/Drawable.h
	include/Constants.h
	src/physics/Face.cpp
	include/physics/Face.h

	include/utils/XMLLoader.h
	src/graphics/ui/View.cpp
	include/graphics/ui/View.h
	src/graphics/ui/Image.cpp
	include/graphics/ui/Image.h
	include/graphics/ui/Primitives.h
	src/graphics/ui/Button.cpp
	include/graphics/ui/Button.h
	src/graphics/ui/Label.cpp
	include/graphics/ui/Label.h
	src/graphics/ui/GUI.cpp
	include/graphics/ui/GUI.h
    src/graphics/ui/TextView.cpp
    include/graphics/ui/TextView.h 
    src/graphics/ui/Font.cpp 
    include/graphics/ui/Font.h
    tests/ui/TestGUI.cpp 
    tests/ui/TestGUI.h
    src/graphics/Skybox.cpp
    include/graphics/Skybox.h
    src/graphics/ui/Menu.cpp
    include/graphics/ui/Menu.h
    include/resource/ResourceManager.h
    src/resource/ResourceManager.cpp
    include/resource/tiny_obj_loader.h
    src/resource/tiny_obj_loader.cpp

    include/utils/MemoryPool.h include/utils/MemoryPool.tcc  src/resource/ObjLoader2.cpp include/resource/ObjLoader2.h)


target_link_libraries(engine
	${ALL_LIBS}
)

add_executable(testphysics
    tests/physics/TestPhysics.cpp
	tests/physics/TestPhysics.h
)

target_link_libraries(testphysics engine)

add_executable(testworldeditor
    tests/worldeditor/TestWorldEditor.cpp
    tests/worldeditor/TestWorldEditor.h
)

target_link_libraries(testworldeditor engine)

add_executable(testscene
	tests/scene/TestGameSystem.cpp
	tests/scene/TestGameSystem.h
)

target_link_libraries(testscene engine)


add_executable(testGUI
	tests/ui/TestGUI.cpp
	tests/ui/TestGUI.h
)

target_link_libraries(testGUI engine)

add_executable(easteregg
	tests/easteregg/EasterEgg.cpp
	tests/easteregg/EasterEgg.h
include/utils/FileOperations.h)

target_link_libraries(easteregg engine)


add_executable(testmenu
	tests/ui/TestMenu.cpp
	tests/ui/TestMenu.h
)

target_link_libraries(testmenu engine)

add_executable(testsound
    tests/sound/TestSound.cpp
    tests/sound/TestSound.h
)

target_link_libraries(testsound engine)

add_executable(game
	game/main.cpp
game/SpyE.cpp game/SpyE.h game/InputState.cpp game/InputState.h
game/MainMenu.cpp game/MainMenu.h game/Player.cpp game/Player.h game/Enemy.cpp game/Enemy.h game/GameEntity.cpp game/GameEntity.h)

target_link_libraries(game engine)


# Xcode and Visual working directories
set_target_properties(engine PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/" COMPILE_FLAGS "-std=c++11")
create_target_launcher(testscene WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
create_target_launcher(testworldeditor WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
create_target_launcher(testphysics WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
create_target_launcher(testGUI WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
create_target_launcher(testsound WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")

SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )


if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
add_custom_command(
   TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/game${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/game/"
)


elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

