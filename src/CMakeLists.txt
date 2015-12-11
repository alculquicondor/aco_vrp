set(HEADER_FILES ${AcoVrp_SOURCE_DIR}/include)
include_directories(${HEADER_FILES})

set(SOURCE_FILES main.cpp
        Graph.cpp
        ${HEADER_FILES}/Graph.h
        ${HEADER_FILES}/Location.h)
add_executable(acovrp ${SOURCE_FILES})