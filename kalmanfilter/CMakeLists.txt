set(PROJECT_NAME KalmanFilter)
set(CURRENT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

project(${PROJECT_NAME})

set( PROJECT_INCLUDE_PATH
	 ${CURRENT_PATH}
	 ${CURRENT_PATH}/include )
	 
set( PROJECT_DEPENDENCIES )

file( GLOB_RECURSE PROJECT_SOURCE_FILES
	  ${CURRENT_PATH}/*.h
	  ${CURRENT_PATH}/*.hpp
	  ${CURRENT_PATH}/*.cpp )

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

target_include_directories( ${PROJECT_NAME}
							PRIVATE
							${PROJECT_INCLUDE_PATH} )
							
# target_link_libraries( ${PROJECT_NAME}
					   # ${PROJECT_DEPENDENCIES} )

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)