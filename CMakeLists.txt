cmake_minimum_required (VERSION 2.8)
project (instantreplay)
set(CMAKE_BUILD_TYPE Release)

#Qt
set(CMAKE_INCLUDE_CURRENT_DIR on)
set(CMAKE_AUTOMOC on)

find_package(Qt5Widgets)

set(OBS_INCLUDE "/usr/include/obs" CACHE PATH "OBS Include Dir")
set(OBS_LIB "/usr/lib" CACHE PATH "OBS Lib Dir")

math(EXPR BITS "8*${CMAKE_SIZEOF_VOID_P}")
set(PLUGIN_DIRECTORY "${CMAKE_BINARY_DIR}/build/instantreplay")
set(PLUGIN_BIN_DIRECTORY "${PLUGIN_DIRECTORY}/bin/${BITS}bit")
set(PLUGIN_DATA_DIRECTORY "${PLUGIN_DIRECTORY}/data")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_BIN_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PLUGIN_BIN_DIRECTORY})

# setting up plugin build
#file(COPY ${CMAKE_SOURCE_DIR}/data/locale DESTINATION ${PLUGIN_DATA_DIRECTORY})

# compilation
set(CMAKE_C_FLAGS "-Wall ${CMAKE_C_FLAGS} -std=gnu99")
set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${OBS_INCLUDE} obs-frontend-api)
link_directories(${OBS_LIB})

set(PLUGIN_SOURCES
    audio_io_state.cpp
    InstantReplay_callout.cpp
    InstantReplay.cpp
    module-entrance.cpp
)

add_library(instantreplay MODULE ${PLUGIN_SOURCES})
target_link_libraries(instantreplay obs Qt5::Widgets Qt5::Gui Qt5::Core)

# install
install(DIRECTORY ${PLUGIN_DIRECTORY} DESTINATION $ENV{HOME}/.config/obs-studio/plugins USE_SOURCE_PERMISSIONS)
