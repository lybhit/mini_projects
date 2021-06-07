#ifndef CERES_EXAMPLES_POSE_GRAPH_2D_TYPES_H_
#define CERES_EXAMPLES_POSE_GRAPH_2D_TYPES_H_

#include "Eigen/Core"

namespace ceres {
namespace examples {

// The state for each vertex in the pose graph.
// struct Pose2d {
//   double x;
//   double y;
//   double yaw_radians;

//   // The name of the data type in the g2o file format.
//   static std::string name() {
//     return "VERTEX_SE2";
//   }
// };


// The constraint between two vertices in the pose graph. The constraint is the
// transformation from vertex id_begin to vertex id_end.
struct Constraint2d {
  int id_begin;
  int id_end;

  double x;
  double y;
  double yaw_radians;

  // The inverse of the covariance matrix for the measurement. The order of the
  // entries are x, y, and yaw.
  Eigen::Matrix3d information;

  // The name of the data type in the g2o file format.
  static std::string name() {
    return "EDGE_SE2";
  }
};


}  // namespace examples
}  // namespace ceres

#endif  // CERES_EXAMPLES_POSE_GRAPH_2D_TYPES_H_
