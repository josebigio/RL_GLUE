
add_subdirectory(approx)
add_subdirectory(obs)

SET( pargo_SRC
	${pargo_SRC}
	${CMAKE_CURRENT_SOURCE_DIR}/Problem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Poll.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/RandomGlobalPoll.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/GlobalFastPoll.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LineSearchPoll.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LocalCSMADPoll.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/BoundsPair.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/SequentialOptimizer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ParallelOptimizer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/CRADLE.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/JiaoPoll.cpp
PARENT_SCOPE )
