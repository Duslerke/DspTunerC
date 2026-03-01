cmake_minimum_required(VERSION 3.14)
project(DspTunerC)

# dependency management: try finding system PortAudio first
find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(SystemPortAudio QUIET portaudio-2.0)
endif()

# fallback: if not found on the system, pull from GitHub
if(NOT SystemPortAudio_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        portaudio
        GIT_REPOSITORY https://github.com/PortAudio/portaudio.git
        GIT_TAG        master
    )
    FetchContent_MakeAvailable(portaudio)
endif()

# define the Executable
add_executable(tuner main.c)

# ;ink the library to executable
if(SystemPortAudio_FOUND)
    target_link_libraries(tuner PRIVATE ${SystemPortAudio_LIBRARIES})
    target_include_directories(tuner PRIVATE ${SystemPortAudio_INCLUDE_DIRS})
else()
    target_link_libraries(tuner PRIVATE portaudio)
endif()
