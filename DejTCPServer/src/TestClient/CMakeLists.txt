#############################################################################
# Set the properties of the executable
#############################################################################
# Set the target name
set(TARGET_NAME "TestClient")


# Set the header path location
set(HEADER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../include/TestClient")

#############################################################################
# Include the required libraries need to be linked to the executable
############################################################################
IF (WIN32)	
	add_definitions(-DWIN32; -D_CRT_SECURE_NO_WARNINGS)	
	set(DEPS_DIR $ENV{DEPENDENCY_DIR})        
	set(BOOST_DIR "${DEPS_DIR}/boost/1.55.0")	
	include_directories(${BOOST_DIR}/include; ${BOOST_DIR})
	link_directories(${BOOST_DIR}/stage/lib)
	set(EXECUTABLE_SOURCE "${CMAKE_CURRENT_BINARY_DIR}")
	set(EXECUTABLE_DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/../../../bin/win")
	set(EXECUTABLE_NAME "${TARGET_NAME}.exe")		
ELSE()	
	set(BOOST_DIR "/media/alex/alex_store/alex/boost_1_61_0/")
	include_directories(${BOOST_DIR})
	link_directories(${BOOST_DIR}/stage/lib)
	set(EXECUTABLE_SOURCE "${CMAKE_CURRENT_BINARY_DIR}")
	set(EXECUTABLE_DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/../../../bin/linux")
	set(EXECUTABLE_NAME "${TARGET_NAME}")
	set(BOOST_LIB boost_system;boost_thread)
ENDIF(WIN32)



# Check for build type and set the executable name
#you have to pass arg -DCMAKE_BUILD_TYPE=Release for a release build, by default it creates debug 
IF (CMAKE_BUILD_TYPE MATCHES "Release" )
	set(out_folder "Release")
ELSE()
	set(out_folder "Debug")
ENDIF (CMAKE_BUILD_TYPE MATCHES "Debug" )

IF (DO_PRE_POST_BUILD_COPY MATCHES "True" )
	add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD  COMMAND ${CMAKE_COMMAND} -E remove ${EXECUTABLE_DESTINATION}/${EXECUTABLE_NAME} COMMENT "${TARGET_NAME} executable (${EXECUTABLE_NAME}) deleted from the bin folder")
ENDIF (DO_PRE_POST_BUILD_COPY MATCHES "True" )

#############################################################################
# Create the executable and link all the dependencies
#############################################################################
# Set the header files
set(TCPSERVER_HEADER   
	${HEADER_PATH}/TCPClient.h
	${HEADER_PATH}/BThread.h
)

# Set the source files
set(TCPSERVER_SOURCE
    ClientMain.cpp
	TCPClient.cpp
	BThread.cpp
)

# Create the executable for ORTControl
add_executable(${TARGET_NAME} ${TCPSERVER_HEADER} ${TCPSERVER_SOURCE} )

# Link the required libraries to the executable
target_link_libraries(${TARGET_NAME} ${BOOST_LIB})

#############################################################################
# COPY the generated executable to the destination after the build process
#############################################################################

IF (DO_PRE_POST_BUILD_COPY MATCHES "True" )
	IF (WIN32)
		add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EXECUTABLE_SOURCE}/${out_folder}/${EXECUTABLE_NAME} ${EXECUTABLE_DESTINATION}/ COMMENT "${TARGET_NAME} executable (${EXECUTABLE_NAME}) added to the win folder" )
	ELSE()
		add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EXECUTABLE_SOURCE}/${EXECUTABLE_NAME} ${EXECUTABLE_DESTINATION}/ COMMENT "${TARGET_NAME} executable (${EXECUTABLE_NAME}) added to the bin folder" )
	ENDIF()
ENDIF (DO_PRE_POST_BUILD_COPY MATCHES "True" )