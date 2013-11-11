PROJECT(caspurboys)

cmake_minimum_required(VERSION 2.6)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


set(pargo_SRC)

add_subdirectory(src)

set(LIBRARIES_TO_LINK)

find_package(MPI)

if(MPI_FOUND AND USE_MPI)
	include_directories(${MPI_INCLUDE_PATH})

	set(CMAKE_CXX_COMPILER "mpicxx")
	set(CMAKE_C_COMPILER "mpic")

	list(APPEND pargo_SRC src/MPIOptimizer.cpp)

	list(APPEND LIBRARIES_TO_LINK  ${MPI_CXX_LIBRARIES})

	message(STATUS "Compiling with MPIC, disable through -DUSE_MPI=0 on cmake's command line if not intended")
else(MPI_FOUND AND USE_MPI)
	message(STATUS "Compiling WITHOUT MPIC, enable through -DUSE_MPI=1 on cmake's command line if not intended")
endif(MPI_FOUND AND USE_MPI)


set(LIBRARIES_TO_LINK ${LIBRARIES_TO_LINK} pthread)


add_library(pargo SHARED ${pargo_SRC})
target_link_libraries(pargo ${LIBRARIES_TO_LINK})

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/src/test/cmake)
find_package(CppUnit )


if(CPPUNIT_FOUND)
	include_directories(${CPPUNIT_INCLUDE_DIR})
	link_directories(${CMAKE_CURRENT_BINARY_DIR})

	set(test_SRC)
	add_subdirectory(src/test)

	add_executable(test_pargo ${test_SRC})

	target_link_libraries(test_pargo ${CPPUNIT_LIBRARY} pargo)
endif(CPPUNIT_FOUND)
