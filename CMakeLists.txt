cmake_minimum_required(VERSION 3.10)
project(granular_synth)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Add DaisySP
add_subdirectory(DaisySP)
include_directories(DaisySP/source)

include_directories(/usr/include/rtaudio)


add_executable(granular_synth
    src/main.cpp
    src/SynthEngine.cpp
)

target_link_libraries(granular_synth
    DaisySP           # Link DaisySP only here
    pthread
    asound     
    rtaudio       # Linux/RPi audio backend
)