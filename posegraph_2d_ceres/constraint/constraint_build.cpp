#include "constraint/constraint_build.h"

ConstraintBuild::ConstraintBuild(){}
ConstraintBuild::~ConstraintBuild(){}

void ConstraintBuild::computeConstraint(std::vector<KeyFrame> KeyFrames){
    assert(KeyFrames.size() >= CONTRAINT_STRIP );
    int length = KeyFrames.size();

    for(int i = 0; i < length - CONTRAINT_STRIP; i++)
    {
        for(int j = i+1; j < i + CONTRAINT_STRIP; j++)
        {
            Constraint2d constraint; 
            constraint.id_begin = KeyFrames[i].id;
            constraint.id_end = KeyFrames[j].id;
            Eigen::Vector3f relative_trans.head<2> = RotationMatrix2D(KeyFrames[i].pose_in_odom(3)).transpose() * 
            (KeyFrames[i].pose_in_odom.head<2>() - KeyFrames[j].pose_in_odom.head<2>());
            
            relative_trans(3) = ceres::examples::NormalizeAngle(KeyFrames[j].pose_in_odom(2) - KeyFrames[i].pose_in_odom(2));
            constraints_.emplace(constraint);

        }

    }
}
const std::vector<Constraint2d>& ConstraintBuild::getConstraints() const
{
  return constraints_;
}
