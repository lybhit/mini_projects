cmake_minimum_required(VERSION 2.6)
project(glog_test)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
find_package(Gflags)
find_package(Glog)
include_directories(${GFLAGS_INCLUDE_DIRS} ${GLOG_INCLUDE_DIRS})

add_executable(glog_test main.cpp)
target_link_libraries (glog_test glog)


install(TARGETS glog_test RUNTIME DESTINATION bin)
