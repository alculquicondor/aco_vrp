set(HEADER_FILES ${AcoVrp_SOURCE_DIR}/include)
include_directories(${HEADER_FILES})

set(SOURCE_FILES
        Graph.cpp
        ${HEADER_FILES}/Graph.h
        ${HEADER_FILES}/Location.h)

add_executable(example example.cpp ${SOURCE_FILES})

target_link_libraries(example)