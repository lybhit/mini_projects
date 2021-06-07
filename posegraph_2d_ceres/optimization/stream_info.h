#ifndef STREAM_INFO_H
#define STREAM_INFO_H

#include <fstream>

#include "Eigen/Core"
#include "normalize_angle.h"
#include "../keyframe/keyframe.h"
#include "../types.h"

namespace ceres{
namespace examples{

std::istream& operator>>(std::istream& input, KeyFrame& keyframe); 

std::istream& operator>>(std::istream& input, Constraint2d& constraint);

} // namespace ceres
} // namespace examples
#endif
