#include "constraint_build.h"


namespace ceres{
namespace examples{
    
ConstraintBuild::ConstraintBuild(){}
ConstraintBuild::~ConstraintBuild(){}


void ConstraintBuild::computeConstraint(const std::vector<KeyFrame>& keyframes){

    assert(keyframes.size() >= CONTRAINT_STRIP );
    int length = keyframes.size();

    for(int i = 0; i < length - CONTRAINT_STRIP; i++)
    {
        for(int j = i+1; j < i + CONTRAINT_STRIP; j++)
        {
            Constraint2d constraint; 
            constraint.id_begin = keyframes[i].id;
            constraint.id_end = keyframes[j].id;
            std::cout << "constraint id_begin = " << constraint.id_begin << ", " << 
                         "constraint id_end = " << constraint.id_end << std::endl;
            Eigen::Vector3d relative_trans;
            relative_trans.head<2>() = ceres::examples::RotationMatrix2D(keyframes[i].pose_in_odom(2)).transpose() * (keyframes[j].pose_in_odom.head<2>() - keyframes[i].pose_in_odom.head<2>());
            
            relative_trans(2) = ceres::examples::NormalizeAngle(keyframes[j].pose_in_odom(2) - keyframes[i].pose_in_odom(2));
            
            std::cout << "relative_trans = " << relative_trans << std::endl;
            constraint.x = relative_trans(0);
            constraint.y = relative_trans(1);
            constraint.yaw_radians = relative_trans(2);
            
            constraint.information = Eigen::Matrix3d::Identity();
            
            constraints_.emplace_back(constraint);

        }

    }
}


const std::vector<Constraint2d>& ConstraintBuild::getConstraints() const
{
    std::cout << "constraints size = " << constraints_.size() << std::endl; 
    return constraints_;
}

}// namespace examples 
}// namespace ceres
