cmake_minimum_required(VERSION 3.5)

# library name
set(APP_NAME Mic.Array.Demo)

project(${APP_NAME})
set(CMAKE_CXX_STANDARD 14)


# set source files
file(GLOB_RECURSE FILES_SOURCES *.cpp *.cc *.c)
file(GLOB_RECURSE FILES_INCLUDE *.hpp *.h)




if(${Platform} STREQUAL "RK3229_Linux_BR")
    message("RK3229_Linux_BR")
else(${Platform} STREQUAL "RK3229_Linux_BR")
    # local build
    include_directories(. /usr/local/include)
    link_directories(/usr/local/lib)

    if(${Platform} STREQUAL "RPi_MATRIX_Creator")
        message("RPi_MATRIX_Creator")
    else(${Platform} STREQUAL "RPi_MATRIX_Creator")
    endif(${Platform} STREQUAL "RPi_MATRIX_Creator")
endif(${Platform} STREQUAL "RK3229_Linux_BR")


# compile to target
add_executable(${APP_NAME} ${FILES_INCLUDE} ${FILES_SOURCES})
if(RPI3_MATRIX_CREATOR)
    target_link_libraries(${APP_NAME}
        matrix_creator_hal
        wiringPi
        wiringPiDev
	portaudio
        )
endif(RPI3_MATRIX_CREATOR)
