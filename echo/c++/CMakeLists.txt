
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

IF(DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ELSE()
    SET(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ENDIF()

project(EchoServer)

# The version number.
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)

set(TARGETNAME ${PROJECT_NAME}_${CMAKE_BUILD_TYPE}_${VERSION_MAJOR}_${VERSION_MINOR})

add_definitions( -DLinux )
#add_definitions( -DWindows )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# boost
add_definitions( -DBOOST_ALL_DYN_LINK )
#set(Boost_ADDITIONAL_VERSIONS "1.49")
set(Boost_DEBUG OFF)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_MULTITHREADED ON)
find_package( Boost 1.54.0 REQUIRED COMPONENTS system filesystem thread date_time chrono )
LINK_DIRECTORIES ( ${Boost_LIBRARY_DIRS} )
INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIRS})

# mine
include_directories(./)

file(GLOB SRCS *.cpp)


add_executable (${TARGETNAME}
    ${SRCS}
)

target_link_libraries (${TARGETNAME}
    ${Boost_LIBRARIES}
)

