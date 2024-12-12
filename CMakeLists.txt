cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(slp-parse-cpp)

# find_package(xtensor REQUIRED)

add_executable(${PROJECT_NAME}
src/main.cpp
src/reader.cpp
src/slp.cpp
src/numpy/numpy_writer.cpp
src/events/game_start.cpp
src/events/payloads.cpp
src/events/common.cpp
src/events/frames/frames.cpp
src/events/frames/preframe.cpp
src/events/frames/postframe.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
headers
headers/numpy
headers/events
headers/events/frames
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# target_include_directories(slp-parse-cpp PUBLIC ${xtensor_INCLUDE_DIRS})
# target_link_libraries(slp-parse-cpp PUBLIC xtensor)
# set_property(TARGET slp-parse-cpp PROPERTY CXX_STANDARD 17)
