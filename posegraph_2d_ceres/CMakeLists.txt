cmake_minimum_required( VERSION 2.8 )
project(map_pose_optimize)

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

# 添加cmake模块以使用ceres库

list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )

include_directories(constraint/ keyframe/ /optimization/ )

# 寻找Ceres库并添加它的头文件

find_package( Ceres REQUIRED )
include_directories( ${CERES_INCLUDE_DIRS} )

# OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_DIRS} )


add_library(pose_graph_2d optimization/pose_graph_2d.cc  optimization/stream_info.cpp)

target_link_libraries(pose_graph_2d ${CERES_LIBRARIES})

add_library(constraint constraint/constraint_build.cpp)

add_executable( map_pose_optimize main.cpp )

# 与Ceres和OpenCV链接

target_link_libraries(map_pose_optimize ${OpenCV_LIBS} pose_graph_2d constraint)
