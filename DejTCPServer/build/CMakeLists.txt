
#############################################################################
# Set the minimum version requried for the build process
#############################################################################
cmake_minimum_required(VERSION 2.8)


#############################################################################
# The name of the project is ORTControl. CMAKE Files in this projectcan
# refer to the root source directory of the project as  ${ORTCONTROL_SOURCE_DIR},
# include directories of the project as ${ORTCONTROL_HEADER_DIR}
# and to the root binary directory of the project as ${ORTCONTROL_BINARY_DIR}
#############################################################################
project(DegTCPServer)


#############################################################################
# Automatic Discovery of Include Directories
#############################################################################
SET(CMAKE_VERBOSE_MAKEFILE ON)


#############################################################################
# Set the Compiler required
#############################################################################
set(CMAKE_CXX_COMPILER "g++")

#############################################################################
# Set the Compilations flags based on release or debug version
# By default set it for release mode.
# In Addition, set the Compilations flags and parser errors efficeiently
#############################################################################
set(CMAKE_CXX_FLAGS "-O3 -g3 -DNDEBUG ")

IF (CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE MATCHES "DEBUG" OR CMAKE_BUILD_TYPE MATCHES "debug")
set(CMAKE_CXX_FLAGS " -O0 -g3 -D_DEBUG ")
ENDIF (CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE MATCHES "DEBUG" OR CMAKE_BUILD_TYPE MATCHES "debug")

IF (WIN32)
	set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -W4 -D_WINDOWS -D_REENTRANT /EHsc")
ELSE()
	set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -Wall -D_LINUX -D_UNICODE -D_REENTRANT ")
ENDIF()

# Parse Errors More Efficiently
IF(CMAKE_COMPILER_IS_GNUCC)
   SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -c -fmessage-length=0")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

IF(CMAKE_COMPILER_IS_GNUCXX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0 -Wfatal-errors -Wno-reorder")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

# Copy the library and executables to the bin folder only when variable is set to "True" 
set(DO_PRE_POST_BUILD_COPY "True")


#############################################################################
# Set the source and header directory path
#############################################################################
set(DEGTCPSERVER_SOURCE_DIR "./../src")
set(DEGTCPSERVER_HEADER_DIR "./../include")


#############################################################################
# Include the common header files and required libraries
#############################################################################
include_directories(${DEGTCPSERVER_HEADER_DIR})


#############################################################################
# Add the directories that are required for the build process (static library)
#############################################################################

#############################################################################
# Create the executables
#############################################################################
#Set the names of all executable projects 
set(EXECUTALBE_DIRS "TCPServer" "TestClient") 

#disable the ZERO_CHECK proj
#set(CMAKE_SUPPRESS_REGENERATION true)

# Incldue all the source directories for building the executable files
foreach( EXECUTABLE_DIR ${EXECUTALBE_DIRS} )

    add_subdirectory("${DEGTCPSERVER_SOURCE_DIR}/${EXECUTABLE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/out/${EXECUTABLE_DIR}" )

endforeach( EXECUTABLE_DIR ${EXECUTABLE_DIRS} )

