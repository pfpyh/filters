cmake_minimum_required(VERSION 3.11)

project(libfilter)
		
set(CURRENT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set( PROJECT_INCLUDE_PATH
	 ${ROOT_PATH}/math/include
	 ${CURRENT_PATH}/include )
	 
set( PROJECT_DEPENDENCIES 
	 libmath )

file( GLOB_RECURSE PROJECT_SOURCE_FILES
	  ${CURRENT_PATH}/*.h
	  ${CURRENT_PATH}/*.hpp
	  ${CURRENT_PATH}/*.cpp )

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_definitions(-D__ENABLE_TEST_CODE__)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_FILES})

target_link_libraries( ${PROJECT_NAME}
					   ${PROJECT_DEPENDENCIES} )

target_include_directories( ${PROJECT_NAME}
							PRIVATE
							${PROJECT_INCLUDE_PATH} )
