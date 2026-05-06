cmake_minimum_required(VERSION 3.10)
project(ColAndreasWizardCLI)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-write-strings -pthread")
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

set(SOURCES
	src/main.cpp
	src/BuildManager.cpp
	src/ColManager.cpp
	src/ImgManager.cpp
	src/Reporter.cpp
)

add_executable(wizard ${SOURCES})

if(NOT WIN32)
	target_link_libraries(wizard pthread)
endif()