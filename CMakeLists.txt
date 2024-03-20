cmake_minimum_required (VERSION 3.8)

project(PreM)
set(CMAKE_CXX_STANDARD 17)


add_executable(prem
    src/prem.cpp

    src/core/PremStructs/BufferItem.cpp
    src/core/PremStructs/Trie.cpp

    src/interface/BaseWindow.cpp
    src/interface/BufferedWindow.cpp
    src/interface/SimpleWindow.cpp
    src/interface/WindowContainer.cpp

    src/core/args_preprocessor.cpp
    src/core/args_router.cpp

    src/core/config_reader.cpp

    src/core/main_cycle.cpp

    src/core/help_functions.cpp


    src/libs/clipboard/src/clipboard_x11.c
    src/libs/clipboard/src/clipboard_common.c

    )



target_link_libraries(prem ncursesw)

find_package (PkgConfig REQUIRED)

pkg_check_modules (GTK3 REQUIRED gtk+-3.0)
add_definitions (${GTK3_CFLAGS_OTHER})

include_directories (${GTK3_INCLUDE_DIRS})
link_directories (${GTK3_LIBRARY_DIRS})

target_link_libraries(prem ${GTK3_LIBRARIES})


find_package(fmt CONFIG REQUIRED)
target_link_libraries(prem fmt::fmt-header-only)  


target_link_libraries(prem ${CMAKE_SOURCE_DIR}/src/libs/clipboard/libclipboard.so)


set(EXECUTABLE_OUTPUT_PATH "bin")
