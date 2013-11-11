PROJECT(agt-cradle)

cmake_minimum_required(VERSION 2.6)

include_directories($ENV{RL_INCLUDE} $ENV{PARGO_INCLUDE})
link_directories($ENV{RL_LIB} $ENV{PARGO_LIB})

 SET(agt_SRC)


add_subdirectory(src)


add_executable(agent ${agt_SRC})

target_link_libraries(agent rlutils rlagent rlgluenetdev pargo)



