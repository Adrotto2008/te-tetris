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
set(SFML_ROOT    "/home/arklight/nextcloud-data/data/arklight/files/programmazione/c++/te_tetris/te_tetris/coso/SFML/build")
set(SFML_BUILD_DIR "${SFML_ROOT}")

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
    ${SFML_ROOT}/../include
)

# ============================================================
# SFML - Tentativo 1: find_package (se hai buildato SFML con CMake modern)
# ============================================================
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML ${SFML_VERSION} COMPONENTS system window graphics audio QUIET
    PATHS ${SFML_BUILD_DIR} ${SFML_ROOT} NO_DEFAULT_PATH)

if(SFML_FOUND)
    message(STATUS "→ SFML trovato tramite find_package!")
    target_link_libraries(te_tetris PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
        SFML::Audio
    )
else()
    # ============================================================
    # SFML - Tentativo 2: linking manuale (fallback)
    # ============================================================
    message(WARNING "SFML non trovato con find_package → linking manuale")

    if(NOT EXISTS "${SFML_BUILD_DIR}/lib")
        message(FATAL_ERROR
            "Cartella SFML/lib non trovata!\n"
            "Percorso cercato: ${SFML_BUILD_DIR}/lib\n"
            "Ricompila SFML statico con:\n"
            "  cmake .. -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release\n"
            "  make -j$(nproc)"
        )
    endif()

    set(SFML_LIB_DIR "${SFML_BUILD_DIR}/lib")

    set(SFML_STATIC_LIBS
        "${SFML_LIB_DIR}/libsfml-audio-s.a"
        "${SFML_LIB_DIR}/libsfml-graphics-s.a"
        "${SFML_LIB_DIR}/libsfml-window-s.a"
        "${SFML_LIB_DIR}/libsfml-system-s.a"
    )

    # Dipendenze audio (statiche - tipiche su Ubuntu/Debian)
    set(AUDIO_DEPS
        /usr/lib/x86_64-linux-gnu/libFLAC.a
        /usr/lib/x86_64-linux-gnu/libvorbisfile.a
        /usr/lib/x86_64-linux-gnu/libvorbis.a
        /usr/lib/x86_64-linux-gnu/libvorbisenc.a
        /usr/lib/x86_64-linux-gnu/libogg.a
    )

    target_link_libraries(te_tetris PRIVATE
        ${SFML_STATIC_LIBS}
        ${AUDIO_DEPS}
    )
endif()

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
message(STATUS " SFML        → ${SFML_VERSION} statico")
if(SFML_FOUND)
    message(STATUS "   → tramite find_package")
else()
    message(STATUS "   → linking manuale da ${SFML_LIB_DIR}")
endif()
message(STATUS " Output → ${CMAKE_SOURCE_DIR}/bin")
message(STATUS "======================================")
