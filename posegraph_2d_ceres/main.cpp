#include <iostream>
#include <opencv2/core/core.hpp>
#include <ceres/ceres.h>
#include <chrono>
#include <stdlib.h>
#include <time.h>

#include "keyframe/keyframe.h"
#include "constraint/constraint_build.h"
#include "optimization/pose_graph_2d.h"

using namespace ceres::examples;

int main(int argc, char** argv)
{
    google::InitGoogleLogging(argv[0]);
    
    int N = 20;                          // 数据点
    double w_sigma = 0.01;                 // 噪声Sigma值
    cv::RNG rng;                        // OpenCV随机数产生器
    
    srand((unsigned)time(NULL));
    std::vector<KeyFrame> keyframes;
    
    for(int i = 0; i < N; i++)
    {
      KeyFrame kf;
      kf.id = i;
      kf.match_ratio = rand() / (float)RAND_MAX;
      std::cout << "index = " << i << ' ' << "ratio = " << kf.match_ratio << std::endl;
      kf.pose_in_odom = Eigen::Vector3d(i * 0.5, i * 0.3, i * 0.1);
      
      std::cout << "index = " << i << std::endl;
      std::cout << "pose_in_odom = " << kf.pose_in_odom(0) << kf.pose_in_odom(1) << kf.pose_in_odom(2)<< std::endl;
      
      if(kf.match_ratio > 0.6)
      {
       kf.pose_in_map = kf.pose_in_odom; 
      }else{
        kf.pose_in_map = Eigen::Vector3d(i * 0.5, i * 0.3, i * 0.1) + Eigen::Vector3d(rng.gaussian(w_sigma), rng.gaussian(w_sigma),rng.gaussian(w_sigma));
      }
      std::cout << "pose_in_map = " << kf.pose_in_map(0) << kf.pose_in_map(1) << kf.pose_in_map(2)<< std::endl;
      
      keyframes.emplace_back(kf);
    }
    
    
    std::map<int, KeyFrame> keyframe_data;
    for(int i =0; i < N; i++)
    {
      keyframe_data[keyframes[i].id] = keyframes[i];
    }
    
    ceres::examples::OutputPoses("keyframes_origin.txt", keyframe_data);
    
    ceres::examples::ConstraintBuild constraint_build;
    constraint_build.computeConstraint(keyframes);
    
    
    ceres::Problem problem;
    
    ceres::examples::BuildOptimizationProblem(constraint_build.getConstraints(), &keyframe_data, &problem);
    ceres::examples::SolveOptimizationProblem(&problem);
    
    ceres::examples::OutputPoses("keyframes_optimize.txt", keyframe_data);
    
    std::cout << "ok, it's right to do the problem." << std::endl;
    
    return 0;
    
}
