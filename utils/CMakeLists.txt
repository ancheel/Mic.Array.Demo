cmake_minimum_required(VERSION 3.5)

# library name
set(APP_NAME Utils)

project(${APP_NAME})
set(CMAKE_CXX_STANDARD 17)


# set header search path
include_directories(.)
# set source files
MESSAGE('!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!')
if (APPLE)
    MESSAGE('--------------------------')
    include_directories(/usr/local/Cellar/portaudio/19.6.0/include)
    link_directories(/usr/local/Cellar/portaudio/19.6.0/lib)
endif ()


# compile to target
add_executable(CatDevices CatDevices.h CatDevices.cpp)
target_link_libraries(CatDevices portaudio)
