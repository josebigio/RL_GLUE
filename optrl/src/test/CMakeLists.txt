
add_subdirectory(problems)

SET( test_SRC ${test_SRC}
	${CMAKE_CURRENT_SOURCE_DIR}/mainTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LineSearchPollTest.cpp
PARENT_SCOPE)
