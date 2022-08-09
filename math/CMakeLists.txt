cmake_minimum_required(VERSION 3.11)

project(libmath)
		
set(CURRENT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set( PROJECT_INCLUDE_PATH
     ${COMMON_HEADER_PATH}
	 ${CURRENT_PATH}/include )

file( GLOB_RECURSE PROJECT_SOURCE_FILES
	  ${CURRENT_PATH}/*.h
	  ${CURRENT_PATH}/*.hpp
	  ${CURRENT_PATH}/*.cpp )

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_definitions(-D__ENABLE_TEST_CODE__)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_FILES})

target_include_directories( ${PROJECT_NAME}
							PRIVATE
							${PROJECT_INCLUDE_PATH} )
