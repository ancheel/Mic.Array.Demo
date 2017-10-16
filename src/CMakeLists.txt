cmake_minimum_required(VERSION 3.5)

# library name
set(APP_NAME Mic.Array.Demo)

project(${APP_NAME})
set(CMAKE_CXX_STANDARD 17)


# set header search path
include_directories(. /usr/local/include)
# set source files
file(GLOB_RECURSE FILES_SOURCES *.cpp *.cc *.c)
file(GLOB_RECURSE FILES_INCLUDE *.hpp *.h)


link_directories(/usr/local/lib)



# compile to target
add_executable(${APP_NAME} ${FILES_INCLUDE} ${FILES_SOURCES})
target_link_libraries(${APP_NAME}
        matrix_creator_hal
        wiringPi
        wiringPiDev
        )
