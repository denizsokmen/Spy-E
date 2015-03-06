# - Locate SDL2 library
#
# This module defines:
#  SDL2_LIBRARY, the name of the library to link against
#  SDL2_FOUND, if false, do not try to link to SDL
#  SDL2_INCLUDE_DIR, where to find SDL.h
#  SDL2_VERSION_STRING, human-readable string containing the version of SDL
#
#=============================================================================
# Copyright 2013 Simone Tai <Simone.Tai@gmail.com>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)
#
# If SDL module is implement properly, we only need specity versio argument in find_packege,
# ie. find_package(SDL 2).  If not, we do the check here:
#
find_package(SDL)
if(SDL_FOUND AND SDL_INCLUDE_DIR AND SDL_LIBRARY)
	if(EXISTS "${SDL_INCLUDE_DIR}/SDL_version.h")
		file(STRINGS "${SDL_INCLUDE_DIR}/SDL_version.h" SDL_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_MAJOR_VERSION[ \t]+[0-9]+$")
		string(REGEX REPLACE "^#define[ \t]+SDL_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL_VERSION_MAJOR "${SDL_VERSION_MAJOR_LINE}")
		if(${SDL_VERSION_MAJOR} MATCHES "2")
			set(SDL2_INCLUDE_DIR ${SDL_INCLUDE_DIR})
			set(SDL2_LIBRARY ${SDL_LIBRARY})
			set(SDL2_VERSION_STRING ${SDL_VERSION_STRING})
			set(SDL2_FOUND TRUE)
		endif()
		unset(SDL_VERSION_MAJOR_LINE)
		unset(SDL_VERSION_MAJOR)
	endif()
endif()
