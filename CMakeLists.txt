cmake_minimum_required (VERSION 3.8)

project(PreM)
set(CMAKE_CXX_STANDARD 17)


add_executable(prem
    test.cpp

    src/core/PremStructs/BufferItem.cpp

    src/interface/BaseWindow.cpp
    src/interface/BufferedWindow.cpp
)



target_link_libraries(prem ncursesw)



find_package (PkgConfig REQUIRED)

pkg_check_modules (GTK3 REQUIRED gtk+-3.0)
add_definitions (${GTK3_CFLAGS_OTHER})

include_directories (${GTK3_INCLUDE_DIRS})
link_directories (${GTK3_LIBRARY_DIRS})

target_link_libraries(prem ${GTK3_LIBRARIES})



set(EXECUTABLE_OUTPUT_PATH "bin")
