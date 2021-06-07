#ifndef CONSTRAINT_BUILD_H
#define CONSTRAINT_BUILD_H

#include "../keyframe/keyframe.h"
#include "../types.h"
#include "../optimization/pose_graph_2d_error_term.h"
#include "../optimization/normalize_angle.h"

#include <vector>

#define CONTRAINT_STRIP 5


namespace ceres{
namespace examples{

class ConstraintBuild{
  public:
    ConstraintBuild();
    ~ConstraintBuild();

    ConstraintBuild(const ConstraintBuild&) = delete;
    ConstraintBuild& operator=(const ConstraintBuild&) = delete;

    void computeConstraint(const std::vector<KeyFrame>& keyframes);

    const std::vector<Constraint2d>& getConstraints() const;


  private:
    std::vector<Constraint2d> constraints_;

};

}// namespace examples 
}// namespace ceres

#endif
