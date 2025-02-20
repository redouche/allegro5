cmake_minimum_required(VERSION 3.10)
project(allegro5 C)

set(CMAKE_C_STANDARD 99)

add_executable(allegro5 main.c)

IF(WIN32)
    target_link_libraries(allegro5 -lmingw32 -lallegro-5.0.10-monolith-md-debug)
ELSE()
    INCLUDE_DIRECTORIES(/usr/local/Cellar/allegro/5.2.8.0/include)
    LINK_DIRECTORIES(/usr/local/Cellar/allegro/5.2.8.0/lib)
    file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.2.8.0/lib/*.dylib")
    message("LIBRARIES = ${LIBRARIES}")
    TARGET_LINK_LIBRARIES(allegro5 ${LIBRARIES})
ENDIF(WIN32)
