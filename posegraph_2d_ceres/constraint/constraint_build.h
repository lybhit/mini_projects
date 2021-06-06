#ifndef CONSTRAINT_BUILD_H
#define CONSTRAINT_BUILD_H

#include "KeyFrame/KeyFrame.h"
#include "./types.h"

#define CONTRAINT_STRIP 5

class ConstraintBuild{
  public:
    ConstraintBuild();
    ~ConstraintBuild();

    ConstraintBuild(const ConstraintBuild&) = delete;
    ConstraintBuild& operator=(const ConstraintBuild&) = delete;

    void computeConstraint(std::vector<KeyFrame> KeyFrames);

    const std::vector<Constraint2d>& getConstraints() const;


  private:
    std::vector<Constraint2d> constraints_;


};
#endif