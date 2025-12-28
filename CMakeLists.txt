cmake_minimum_required(VERSION 3.20)
project(te_tetris LANGUAGES CXX)

# ============================================================
# STANDARD C++
# ============================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# ============================================================
# ZLIB (FetchContent, target moderno)
# ============================================================
FetchContent_Declare(
    zlib
    GIT_REPOSITORY https://github.com/madler/zlib.git
    GIT_TAG v1.3.1
)

set(ZLIB_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(ZLIB_BUILD_STATIC ON  CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(zlib)

# Espone ZLIB::ZLIB come si aspetta FindZLIB / IXWebSocket
if(NOT TARGET ZLIB::ZLIB)
    add_library(ZLIB::ZLIB ALIAS zlibstatic)
endif()

# ============================================================
# nlohmann/json (header-only)
# ============================================================
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

# ============================================================
# cpp-httplib (header-only)
# ============================================================
FetchContent_Declare(
    cpp_httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.15.3
)
FetchContent_MakeAvailable(cpp_httplib)

# ============================================================
# SFML (FetchContent)
# ============================================================

# Disabilita tutto ciò che non serve e il supporto OGG/Vorbis
set(SFML_BUILD_AUDIO ON CACHE BOOL "" FORCE)
set(SFML_BUILD_SYSTEM ON CACHE BOOL "" FORCE)
set(SFML_BUILD_WINDOW OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_GRAPHICS OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SFML_INSTALL OFF CACHE BOOL "" FORCE)
set(SFML_USE_VORBIS OFF CACHE BOOL "" FORCE)
set(SFML_USE_OGG OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(sfml)

# ============================================================
# IXWebSocket (subproject, NO install, NO TLS)
# ============================================================
set(IXWEBSOCKET_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(IXWEBSOCKET_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(IXWEBSOCKET_BUILD_WITH_TLS OFF CACHE BOOL "" FORCE)
set(IXWEBSOCKET_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    ixwebsocket
    GIT_REPOSITORY https://github.com/machinezone/IXWebSocket.git
    GIT_TAG v11.4.5
)
FetchContent_MakeAvailable(ixwebsocket)

# ============================================================
# FILES DEL PROGETTO
# ============================================================
file(GLOB_RECURSE SRC_FILES
    versions/current/src/*.cpp
)

add_executable(te_tetris
    versions/current/main.cpp
    ${SRC_FILES}
)

# ============================================================
# INCLUDE (solo quelli del progetto)
# ============================================================
target_include_directories(te_tetris PRIVATE
    versions/current/include
    ${cpp_httplib_SOURCE_DIR}
)

# ============================================================
# LINK LIBRARIES (modo moderno)
# ============================================================
target_link_libraries(te_tetris PRIVATE
    ixwebsocket
    nlohmann_json::nlohmann_json
    ZLIB::ZLIB
)

# ============================================================
# LINK SFML AL PROGETTO
# ============================================================
target_link_libraries(te_tetris PRIVATE
    sfml-audio
    sfml-system
)

# ============================================================
# STATIC LINKING SOLO SU MinGW
# ============================================================
if(MINGW)
    target_link_options(te_tetris PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
    )

    target_link_libraries(te_tetris PRIVATE
        ws2_32
        winmm
        pthread
    )
endif()

# ============================================================
# OUTPUT
# ============================================================
set_target_properties(te_tetris PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

# ============================================================
# MESSAGGI FINALI
# ============================================================
message(STATUS "===================================")
message(STATUS "✔ te_tetris configurato correttamente")
message(STATUS "✔ ZLIB via FetchContent (ZLIB::ZLIB)")
message(STATUS "✔ IXWebSocket (no TLS, no install)")
message(STATUS "✔ nlohmann/json")
message(STATUS "✔ cpp-httplib")
message(STATUS "===================================")
