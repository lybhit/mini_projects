#ifndef POSE_GRAPH_2D_H
#define POSE_GRAPH_2D_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "angle_local_parameterization.h"
#include "ceres/ceres.h"
#include "gflags/gflags.h"
#include "glog/logging.h"
#include "pose_graph_2d_error_term.h"
#include "../types.h"
#include "../keyframe/keyframe.h"
#include "../constraint/constraint_build.h"
#include "stream_info.h"


namespace ceres {
namespace examples {
  
void BuildOptimizationProblem(const std::vector<Constraint2d>& constraints,
                              std::map<int, KeyFrame>* keyframes,
                              ceres::Problem* problem);

 
bool SolveOptimizationProblem(ceres::Problem* problem); 

bool OutputPoses(const std::string& filename, const std::map<int, KeyFrame>& keyframes);

} //namespace examples
} //namespace ceres


#endif
