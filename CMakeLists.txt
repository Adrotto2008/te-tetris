cmake_minimum_required(VERSION 3.10)
project(te_tetris)

# Forza uso di librerie statiche
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)

# Flags per static linking completo (MinGW)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

# Cartelle
set(SRC_DIR "versions/current/src")
set(INCLUDE_DIR "versions/current/include")
set(MAIN_FILE "versions/current/main.cpp")

# Aggiunge tutti i .cpp in src/
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")

# Include
include_directories(${INCLUDE_DIR})

# Crea eseguibile
add_executable(te_tetris ${MAIN_FILE} ${SRC_FILES})

# Dove mettere l'eseguibile
set_target_properties(te_tetris PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

# Se serve linkare librerie statiche aggiuntive:
# target_link_libraries(te_tetris PRIVATE m pthread)
