cmake_minimum_required(VERSION 3.25)
project(te_tetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BUILD_SHARED_LIBS OFF)

include(FetchContent)

# ================== JSON ==================
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

# ================== IXWEBSOCKET ==================
set(USE_ZLIB OFF CACHE BOOL "" FORCE)
set(USE_TLS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    ixwebsocket
    GIT_REPOSITORY https://github.com/machinezone/IXWebSocket.git
    GIT_TAG v11.4.5
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(ixwebsocket)

add_library(ixwebsocket_internal STATIC
    ${ixwebsocket_SOURCE_DIR}/ixwebsocket/IXWebSocket.cpp
    ${ixwebsocket_SOURCE_DIR}/ixwebsocket/IXWebSocketTransport.cpp
    ${ixwebsocket_SOURCE_DIR}/ixwebsocket/IXSocket.cpp
    ${ixwebsocket_SOURCE_DIR}/ixwebsocket/IXNetSystem.cpp
    ${ixwebsocket_SOURCE_DIR}/ixwebsocket/IXDNSLookup.cpp
    ${ixwebsocket_SOURCE_DIR}/ixwebsocket/IXHttp.cpp
    ${ixwebsocket_SOURCE_DIR}/ixwebsocket/IXWebSocketServer.cpp
)

target_include_directories(ixwebsocket_internal PUBLIC
    ${ixwebsocket_SOURCE_DIR}
    ${ixwebsocket_SOURCE_DIR}/ixwebsocket
)

target_compile_definitions(ixwebsocket_internal PUBLIC
    IXWEBSOCKET_USE_ZLIB=0
    IXWEBSOCKET_USE_TLS=0
)

# ================== EXECUTABLE ==================
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    versions/current/src/*.cpp
)

add_executable(te_tetris
    versions/current/main.cpp
    ${SRC_FILES}
)

target_include_directories(te_tetris PRIVATE
    versions/current/include
)

target_link_libraries(te_tetris PRIVATE
    nlohmann_json::nlohmann_json
    ixwebsocket_internal
)

# 🔥 STATICO VERO (SOLO QUI)
if (MINGW)
    target_link_options(te_tetris PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
        -Wl,--whole-archive
        -lwinpthread
        -Wl,--no-whole-archive
    )
endif()

set_target_properties(te_tetris PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
