cmake_minimum_required(VERSION 3.20)
project(te_tetris LANGUAGES CXX)

# ============================================================
# Standard C++
# ============================================================
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

# ============================================================
# Opzioni globali / variabili progetto
# ============================================================
set(SFML_VERSION "2.6.1")  # Cambia se usi una versione diversa

# ============================================================
# FetchContent per dipendenze esterne
# ============================================================
include(FetchContent)

# ZLIB
FetchContent_Declare(
    zlib
    GIT_REPOSITORY https://github.com/madler/zlib.git
    GIT_TAG        v1.3.1
)
set(ZLIB_BUILD_SHARED OFF  CACHE BOOL "" FORCE)
set(ZLIB_BUILD_STATIC ON   CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(zlib)

if(NOT TARGET ZLIB::ZLIB)
    add_library(ZLIB::ZLIB ALIAS zlibstatic)
endif()

# nlohmann/json (header-only)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

# cpp-httplib (header-only)
FetchContent_Declare(
    cpp_httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG        v0.15.3
)
FetchContent_MakeAvailable(cpp_httplib)

# IXWebSocket (no TLS, no tests, no examples)
set(IXWEBSOCKET_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(IXWEBSOCKET_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(IXWEBSOCKET_BUILD_WITH_TLS OFF CACHE BOOL "" FORCE)
set(IXWEBSOCKET_INSTALL        OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    ixwebsocket
    GIT_REPOSITORY https://github.com/machinezone/IXWebSocket.git
    GIT_TAG        v11.4.5
)
FetchContent_MakeAvailable(ixwebsocket)

# SFML (FetchContent)
set(SFML_BUILD_AUDIO       ON  CACHE BOOL "" FORCE)
set(SFML_BUILD_GRAPHICS    ON  CACHE BOOL "" FORCE)
set(SFML_BUILD_WINDOW      ON  CACHE BOOL "" FORCE)
set(SFML_BUILD_SYSTEM      ON  CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK     OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES    OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC         OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TEST_SUITE  OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        ${SFML_VERSION}
)
FetchContent_MakeAvailable(sfml)

# ============================================================
# File sorgente del progetto
# ============================================================
file(GLOB_RECURSE SRC_FILES
    versions/current/src/*.cpp
)

add_executable(te_tetris
    versions/current/main.cpp
    ${SRC_FILES}
)

# ============================================================
# Include directories
# ============================================================
target_include_directories(te_tetris PRIVATE
    versions/current/include
    ${cpp_httplib_SOURCE_DIR}
)

# ============================================================
# SFML - FetchContent (link diretto ai target)
# ============================================================
target_link_libraries(te_tetris PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)

# ============================================================
# Altre librerie del progetto
# ============================================================
target_link_libraries(te_tetris PRIVATE
    ixwebsocket
    nlohmann_json::nlohmann_json
    ZLIB::ZLIB
)

# ============================================================
# Dipendenze Linux / POSIX obbligatorie per linking statico
# ============================================================
if(UNIX AND NOT APPLE)
    target_link_libraries(te_tetris PRIVATE
        pthread
        dl
        m
        rt
        udev               # spesso necessario per input su Linux
    )
endif()

if(WIN32)
    target_link_libraries(te_tetris PRIVATE
        xinput9_1_0
    )
endif()

if(MINGW)
    get_filename_component(MINGW_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(SFML_OPENAL_DLL "${sfml_SOURCE_DIR}/extlibs/bin/x64/openal32.dll")
    else()
        set(SFML_OPENAL_DLL "${sfml_SOURCE_DIR}/extlibs/bin/x86/openal32.dll")
    endif()

    set(RUNTIME_DLLS
        "${MINGW_BIN_DIR}/libwinpthread-1.dll"
        "${MINGW_BIN_DIR}/libgcc_s_seh-1.dll"
        "${MINGW_BIN_DIR}/libstdc++-6.dll"
        "${SFML_OPENAL_DLL}"
    )

    foreach(dll IN LISTS RUNTIME_DLLS)
        if(EXISTS "${dll}")
            add_custom_command(TARGET te_tetris POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        "${dll}"
                        "$<TARGET_FILE_DIR:te_tetris>"
            )
        else()
            message(WARNING "Runtime DLL non trovato: ${dll}")
        endif()
    endforeach()
endif()

# ============================================================
# Output eseguibile
# ============================================================
set_target_properties(te_tetris PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

# ============================================================
# Messaggi finali
# ============================================================
message(STATUS "======================================")
message(STATUS " te_tetris configurato")
message(STATUS " C++${CMAKE_CXX_STANDARD}")
message(STATUS " ZLIB        → FetchContent")
message(STATUS " json        → nlohmann_json")
message(STATUS " httplib     → cpp-httplib")
message(STATUS " WebSocket   → ixwebsocket (no TLS)")
message(STATUS " SFML        → ${SFML_VERSION} (FetchContent)")
message(STATUS " Output → ${CMAKE_SOURCE_DIR}/bin")
message(STATUS "======================================")
