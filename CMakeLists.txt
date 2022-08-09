cmake_minimum_required(VERSION 3.11)

project(Project
		DESCRIPTION "Filters"
		LANGUAGES CXX)
		
set(ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(COMMON_HEADER_PATH ${ROOT_PATH}/include)

# Configure
set(ENABLE_TEST_CODE 1)
set(DATA_PATH ${ROOT_PATH}/python/data)
set(DATA_OUTPUT_PATH ${DATA_PATH}/output)

configure_file(configure.h.in ${COMMON_HEADER_PATH}/configure.h @ONLY)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT_PATH}/bld)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ROOT_PATH}/bld)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ROOT_PATH}/bld)

add_subdirectory(math)
add_subdirectory(filter)
add_subdirectory(example)

