#ifndef KEY_FRAME_H
#define KEY_FRAME_H

#include <Eigen/Dense>
#include <vector>

struct KeyFrame
{
    int id;
    float match_ratio;
    Eigen::Vector3d pose_in_map;
    Eigen::Vector3d pose_in_odom;
    std::vector<Eigen::Vector3f> scan_cloud;
};


#endif
