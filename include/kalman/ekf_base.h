//  @file ekf.h
//  @author Yuntian Li (yuntianlee91@hotmail.com)
//  @brief  base class of extended kalman filter
//  @version 0.1
//  @date 2024-05-02
//  
//  @copyright Copyright (c) 2024
//  

#ifndef BAYESIAN_KALMAN_EKF_BASE_H_
#define BAYESIAN_KALMAN_EKF_BASE_H_

#include "kalman/kf_base.h"

namespace bayes_filter{
class EkfBase : public KfBase{
 public:
  // @brief   override ekf one step prediction
  // @param   u : 
  virtual void OneStepPrediction(const VecXd u) override{
    calcStateTransitionMatrix(x_, F_);
    // Eq1. predict prior state estimation
    StateTransitionFcn(x_);
    // Eq2. predict prior estimation covariance
    P_ = F_ * P_ * F_.transpose() + Q_;
  }

  // @brief   override ekf one strp update
  // @param   z : 
  virtual void OneStepUpdate(const VecXd z) override{
    // eq3. calca Kalman gain K
    calcObservationMatrix(x_, H_);
    S_ = H_ * P_ * H_.transpose() + R_;
    K_ = P_ * H_.transpose() * S_.inverse();
    // eq4. update posterior state estimation
    VecXd tmp_z;
    ObservationFcn(x_, tmp_z);
    y_ = z - tmp_z;
    x_ = x_ + K_ * (z - y_);
    // eq5. update posterior estimation covariance
    P_ = P_ - K_ * H_ * P_;
  }
};
} // namespace bayes_filter

#endif