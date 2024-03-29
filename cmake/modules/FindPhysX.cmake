# - Find the PhysX includes and libraries.
# The following variables are set if PhysX is found.  If Boost is not
# found, PHYSX_FOUND is set to false.
#  PHYSX_FOUND        - True when the PhysX include directory is found.
#  PHYSX_INCLUDE_DIRS - the path to where the boost include files are.
#  PHYSX_LIBRARY_DIRS - The path to where the boost library files are.
#  PHYSX_LIB_DIAGNOSTIC_DEFINITIONS - Only set if using Windows.

# ----------------------------------------------------------------------------
# If you have installed PhysX in a non-standard location or you have
# just staged PhysX files using bjam then you have three
# options. In the following comments, it is assumed that <Your Path>
# points to the root directory of the include directory of PhysX. e.g
# If you have put PhysX in C:\development\PhysX then <Your Path> is
# "C:/development/PhysX" and in this directory there will be two

# 1) After CMake runs, set PHYSX_INCLUDE_DIR to <Your Path>/include/boost<-version>
# 2) Use CMAKE_INCLUDE_PATH to set a path to <Your Path>/include. This will allow FIND_PATH()
#    to locate PHYSX_INCLUDE_DIR by utilizing the PATH_SUFFIXES option. e.g.
#    SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "<Your Path>/include")
# 3) Set an environment variable called ${PHYSX_ROOT} that points to the root of where you have
#    installed Boost, e.g. <Your Path>. It is assumed that there is at least a subdirectory called
#    include in this path.
#
# Note:
#  1) If you are just using the boost headers, then you do not need to use
#     PHYSX_LIBRARY_DIRS in your CMakeLists.txt file.
#  2) If Boost has not been installed, then when setting PHYSX_LIBRARY_DIRS
#     the script will look for /lib first and, if this fails, then for /stage/lib.
#
# Usage:
# In your CMakeLists.txt file do something like this:
# ...
# # PhysX
# FIND_PACKAGE(PhysX)
# ...
# INCLUDE_DIRECTORIES(${PHYSX_INCLUDES})
# TARGET_LINK_LIBRARIES(libname ${PHYSX_LIBRARIES})
#
# In Windows, we make the assumption that, if the Boost files are installed, the default directory
# will be C:\boost.


set(PHYSX_INCLUDE_PATH_DESCRIPTION "The Base directory containing the PhysX include files. E.g /usr/include/PhysX/2.8.0 or C:/Program\ Files/Ageia\ Technologies/SDK/2.8.0")

set(PhysX_DIR_MESSAGE "Set the PHYSX_INCLUDE_DIR cmake cache entry to the ${PHYSX_INCLUDE_PATH_DESCRIPTION}")

set(PhysX_DIR_SEARCH $ENV{PHYSX_INC})

set(VERSION_SUFFIX_FOR_PATH
   v2.8.4_win
   v2.8.3_win
)

# Add in some path suffixes. These will have to be updated whenever a new Boost version comes out.

set(PhysX_DIR_SEARCH
  ${PhysX_DIR_SEARCH}
  ${DELTA3D_EXT_DIR}/inc
  /usr/include/PhysX
  "C:\\Program Files (x86)\\NVIDIA Corporation\\NVIDIA PhysX SDK"
  "C:\\Program Files\\NVIDIA Corporation\\NVIDIA PhysX SDK"
)

#
# Look for an installation.
#
find_path(PHYSX_DIR NAMES SDKs PATH_SUFFIXES ${VERSION_SUFFIX_FOR_PATH} PATHS

  # Look in other places.
  ${PhysX_DIR_SEARCH}

  # Help the user find it if we cannot.
  DOC "The ${PHYSX_INCLUDE_PATH_DESCRIPTION}"
)

find_path(PHYSX_COOKING_INCLUDE_DIR NAMES NxCooking.h PATH_SUFFIXES Cooking/include Cooking/Include
  PATHS

  # Look in other places.
  ${PHYSX_DIR}/SDKs

  # Help the user find it if we cannot.
  DOC "The SDKs directory should contain PhysX Cooking library includes"
)

find_path(PHYSX_FOUNDATION_INCLUDE_DIR NAMES Nx.h PATH_SUFFIXES Foundation/include Foundation/Include
  PATHS

  # Look in other places.
  ${PHYSX_DIR}/SDKs

  # Help the user find it if we cannot.
  DOC "The SDKs directory should contain PhysX Foundation library includes"
)

find_path(PHYSX_CHARACTER_INCLUDE_DIR NAMES NxCharacter.h PATH_SUFFIXES NxCharacter/include NxCharacter/Include
  PATHS

  # Look in other places.
  ${PHYSX_DIR}/SDKs

  # Help the user find it if we cannot.
  DOC "The SDKs directory should contain PhysX NxCharacter library includes"
)

find_path(PHYSX_PHYSICS_INCLUDE_DIR NAMES NxActor.h PATH_SUFFIXES Physics/include Physics/Include
  PATHS

  # Look in other places.
  ${PHYSX_DIR}/SDKs

  # Help the user find it if we cannot.
  DOC "The SDKs directory should contain PhysX Physics library includes"
)

find_path(PHYSX_LOADER_INCLUDE_DIR NAMES PhysXLoader.h PATH_SUFFIXES PhysXLoader/include PhysXLoader/Include
  PATHS

  # Look in other places.
  ${PHYSX_DIR}/SDKs

  # Help the user find it if we cannot.
  DOC "The SDKs directory should contain PhysX PhysXLoader library includes"
)

set(PHYSX_INCLUDES ${PHYSX_LOADER_INCLUDE_DIR} ${PHYSX_PHYSICS_INCLUDE_DIR}
   ${PHYSX_CHARACTER_INCLUDE_DIR} ${PHYSX_FOUNDATION_INCLUDE_DIR} ${PHYSX_LOADER_INCLUDE_DIR}
   ${PHYSX_COOKING_INCLUDE_DIR})

set(PHYSX_LIB_DIR_SEARCH $ENV{PHYSX_LIB})

set(PHYSX_LIB_DIR_SEARCH
    ${PHYSX_LIB_DIR_SEARCH}
    ${DELTA_DIR}/ext/lib
    /usr/lib/PhysX
)
if(CMAKE_CL_64)
    set(PHYSX_LIB_DIR_SEARCH
        ${PHYSX_LIB_DIR_SEARCH}
        ${PHYSX_DIR}/SDKS/lib/win64
    )
else()
    set(PHYSX_LIB_DIR_SEARCH
        ${PHYSX_LIB_DIR_SEARCH}
        ${PHYSX_DIR}/SDKS/lib/win32
    )
endif()

if(NOT WIN32)
    FIND_FILE(PHYSX_LIBRARY_DIR NAMES ${VERSION_SUFFIX_FOR_PATH} PATHS
        # Look in other places.
        ${PHYSX_LIB_DIR_SEARCH}

        # Help the user find it if we cannot.
        DOC "Set PHYSX_LIB_DIR_SEARCH to set the base path to search for PhysX versions."
    )
else()
   set(PHYSX_LIBRARY_DIR ${PHYSX_LIB_DIR_SEARCH})
endif()


macro(find_physx_library MYLIBRARY MYLIBRARYNAME)
    if(CMAKE_CL_64)
        set(MYLIBNAME "${MYLIBRARYNAME}64")
    else()
        set(MYLIBNAME "${MYLIBRARYNAME}")
    endif()
    find_library(${MYLIBRARY}
        NAMES ${MYLIBNAME}
        PATHS
        ${PHYSX_LIBRARY_DIR}
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/lib
        /usr/lib
        /sw/lib
        /opt/local/lib
        /opt/csw/lib
        /opt/lib
        /usr/freeware/lib64
    )
endmacro()

set(PHYSX_LIBCHARACTER_LIST NxCharacter)
#set(PHYSX_LIBEXTENSIONS_LIST NxExtensions)
set(PHYSX_LIBCOOKING_LIST PhysXCooking)
set(PHYSX_LIBCORE_LIST PhysXCore)
set(PHYSX_LIBLOADER_LIST PhysXLoader)

find_physx_library(PHYSX_CHARACTER_LIBRARY "${PHYSX_LIBCHARACTER_LIST}")
#find_physx_library(PHYSX_EXTENSIONS_LIBRARY "${PHYSX_LIBEXTENSIONS_LIST}")cha
find_physx_library(PHYSX_COOKING_LIBRARY "${PHYSX_LIBCOOKING_LIST}")
find_physx_library(PHYSX_LOADER_LIBRARY "${PHYSX_LIBLOADER_LIST}")
find_physx_library(PHYSX_CORE_LIBRARY "${PHYSX_LIBCORE_LIST}")

set(PHYSX_LIBRARIES ${PHYSX_COOKING_LIBRARY} ${PHYSX_CHARACTER_LIBRARY} ${PHYSX_CORE_LIBRARY} ${PHYSX_EXTENSIONS_LIBRARY} ${PHYSX_LOADER_LIBRARY})

if(${CMAKE_SYSTEM} MATCHES "Linux")
    ADD_DEFINITIONS(-DLINUX -DNX_DISABLE_FLUIDS)
endif()

set(PHYSX_FOUND "NO")
if(PHYSX_INCLUDES AND PHYSX_LIBRARIES)
   set(PHYSX_FOUND "YES")
endif(PHYSX_INCLUDES AND PHYSX_LIBRARIES)

