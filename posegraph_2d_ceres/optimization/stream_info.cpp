#include "stream_info.h"

namespace ceres{
namespace examples{

std::istream& operator>>(std::istream& input, KeyFrame& keyframe) {
  input >> keyframe.pose_in_map(0) >> keyframe.pose_in_map(0) >>keyframe.pose_in_map(0) ;
  // Normalize the angle between -pi to pi.
  keyframe.pose_in_map(2) = NormalizeAngle(keyframe.pose_in_map(2));
  return input;
}


std::istream& operator>>(std::istream& input, Constraint2d& constraint) {
  input >> constraint.id_begin >> constraint.id_end >> constraint.x >>
      constraint.y >> constraint.yaw_radians >>
      constraint.information(0, 0) >> constraint.information(0, 1) >>
      constraint.information(0, 2) >> constraint.information(1, 1) >>
      constraint.information(1, 2) >> constraint.information(2, 2);

  // Set the lower triangular part of the information matrix.
  constraint.information(1, 0) = constraint.information(0, 1);
  constraint.information(2, 0) = constraint.information(0, 2);
  constraint.information(2, 1) = constraint.information(1, 2);

  // Normalize the angle between -pi to pi.
  constraint.yaw_radians = NormalizeAngle(constraint.yaw_radians);
  return input;
}

} // namespace ceres
} // namespace examples
