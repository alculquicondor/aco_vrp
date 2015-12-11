set(HEADER_FILES ${AcoVrp_SOURCE_DIR}/include)
include_directories(${HEADER_FILES})

set(SOURCE_FILES
        Graph.cpp
        ${HEADER_FILES}/Graph.h
        ${HEADER_FILES}/Location.h)

add_executable(example example.cpp ${SOURCE_FILES})

add_executable(aco_vrp main.cpp
        Game.cpp
        Painter.cpp
        ${HEADER_FILES}/Game.h
        ${HEADER_FILES}/Painter.h
        ${SOURCE_FILES})

target_link_libraries(aco_vrp ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})