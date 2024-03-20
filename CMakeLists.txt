cmake_minimum_required (VERSION 3.8)

project(PreM)
set(CMAKE_CXX_STANDARD 14)



add_executable(prem
    test.cpp
    src/core/PremStructs/BufferItem.cpp
    src/interface/BaseWindow.cpp
    src/interface/BufferedWindow.cpp
    src/libs/clip/clip.cpp
    src/libs/clip/clip_none.cpp
)

target_link_libraries(prem ncursesw)
