cmake_minimum_required(VERSION 3.14)

set(This SBH)
project(${This} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# option(BULID_TEST "Bulid tests" OFF)


# enable_testing()
# add_subdirectory(googletest)

set(Headers
    Dna.hpp
    Graph.hpp
    DnaGraph.hpp
    DnaException.hpp
    DnaGraphException.hpp
    Edge.hpp
    Helper.hpp
    Ant.hpp
    Settings.hpp
    Aco.hpp
    Timer.hpp
) 

set(Sources
    main.cpp
    Dna.cpp
    DnaGraph.cpp
    Edge.cpp
    Ant.cpp
    Aco.cpp
)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -lpthread")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(Boost 1.69)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(SBH.out ${Sources} ${Headers})
endif()

# if(BUILD_TEST)
#     add_library(${This} STATIC ${Sources} ${Headers})
#     add_subdirectory(test)
# endif()