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
#include "types.h"
#include "keyframe/keyframe.h"

DEFINE_string(input, "", "The pose graph definition filename in g2o format.");

namespace ceres {
namespace examples {

// Constructs the nonlinear least squares optimization problem from the pose
// graph constraints.
void BuildOptimizationProblem(const std::vector<Constraint2d>& constraints,
                              std::map<int, KeyFrame>* keyframes,
                              ceres::Problem* problem) {
  CHECK(keyframes!= NULL);
  CHECK(problem != NULL);
  if (constraints.empty()) {
    LOG(INFO) << "No constraints, no problem to optimize.";
    return;
  }

  ceres::LossFunction* loss_function = NULL;
  ceres::LocalParameterization* angle_local_parameterization =
      AngleLocalParameterization::Create();

  for (std::vector<Constraint2d>::const_iterator constraints_iter =
           constraints.begin();
       constraints_iter != constraints.end(); ++constraints_iter) {
    const Constraint2d& constraint = *constraints_iter;

    std::map<int, KeyFrame>::iterator keyframe_begin_iter =
        keyframes->find(constraint.id_begin);
    CHECK(keyframe_begin_iter != KeyFrames->end())
        << "keyframe with ID: " << constraint.id_begin << " not found.";
    std::map<int, KeyFrame>::iterator keyframe_end_iter =
        keyframes->find(constraint.id_end);
    CHECK(keyframe_end_iter != KeyFrames->end())
        << "keyframe with ID: " << constraint.id_end << " not found.";

    const Eigen::Matrix3d sqrt_information =
        constraint.information.llt().matrixL();
    // Ceres will take ownership of the pointer.
    ceres::CostFunction* cost_function = PoseGraph2dErrorTerm::Create(
        constraint.x, constraint.y, constraint.yaw_radians, sqrt_information);
    problem->AddResidualBlock(
        cost_function, loss_function, &keyframe_begin_iter->second.pose_in_map(0),
        &keyframe_begin_iter->pose_in_map(1), &keyframe_begin_iter->second.pose_in_map(2),
        &keyframe_end_iter->second.pose_in_map(0), &keyframe_end_iter->second.pose_in_map(1),
        &keyframe_end_iter->second.pose_in_map(2));

    problem->SetParameterization(&keyframe_begin_iter->second.pose_in_map(2),
                                angle_local_parameterization);
    problem->SetParameterization(&keyframe_end_iter->second.pose_in_map(2),
                                angle_local_parameterization);

    if(&keyframe_begin_iter->second.match_ratio > 0.6)
    {
        problem->SetParameterBlockConstant(&keyframe_begin_iter->second.pose_in_map(0));
        problem->SetParameterBlockConstant(&keyframe_begin_iter->second.pose_in_map(1));
        problem->SetParameterBlockConstant(&keyframe_begin_iter->second.pose_in_map(2));
    }
  }

}

// Returns true if the solve was successful.
bool SolveOptimizationProblem(ceres::Problem* problem) {
  CHECK(problem != NULL);

  ceres::Solver::Options options;
  options.max_num_iterations = 100;
  options.linear_solver_type = ceres::SPARSE_NORMAL_CHOLESKY;

  ceres::Solver::Summary summary;
  ceres::Solve(options, problem, &summary);

  std::cout << summary.FullReport() << '\n';

  return summary.IsSolutionUsable();
}

// Output the poses to the file with format: ID x y yaw_radians.
bool OutputPoses(const std::string& filename,
                 const std::map<int, KeyFrame>& keyframes) {
  std::fstream outfile;
  outfile.open(filename.c_str(), std::istream::out);
  if (!outfile) {
    std::cerr << "Error opening the file: " << filename << '\n';
    return false;
  }
  for (std::map<int, KeyFrame>::const_iterator keyframes_iter = keyframes.begin();
       keyframes_iter != keyframes.end(); ++keyframes_iter) {
    const std::map<int, KeyFrame>::value_type& pair = *keyframes_iter;
    outfile <<  pair.first << " " << pair.second.pose_in_map(0) << " " << pair.second.pose_in_map(1)
            << ' ' << pair.second.pose_in_map(2) << '\n';
  }
  return true;
}

}  // namespace examples
}  // namespace ceres

// int main(int argc, char** argv) {
//   google::InitGoogleLogging(argv[0]);
//   CERES_GFLAGS_NAMESPACE::ParseCommandLineFlags(&argc, &argv, true);

//   CHECK(FLAGS_input != "") << "Need to specify the filename to read.";

//   std::map<int, ceres::examples::Pose2d> poses;
//   std::vector<ceres::examples::Constraint2d> constraints;

//   CHECK(ceres::examples::ReadG2oFile(FLAGS_input, &poses, &constraints))
//       << "Error reading the file: " << FLAGS_input;

//   std::cout << "Number of poses: " << poses.size() << '\n';
//   std::cout << "Number of constraints: " << constraints.size() << '\n';

//   CHECK(ceres::examples::OutputPoses("poses_original.txt", poses))
//       << "Error outputting to poses_original.txt";

//   ceres::Problem problem;
//   ceres::examples::BuildOptimizationProblem(constraints, &poses, &problem);

//   CHECK(ceres::examples::SolveOptimizationProblem(&problem))
//       << "The solve was not successful, exiting.";

//   CHECK(ceres::examples::OutputPoses("poses_optimized.txt", poses))
//       << "Error outputting to poses_original.txt";

//   return 0;
// }
