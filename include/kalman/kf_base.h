//  @file kf.h
//  @author Yuntian Li (yuntianlee91@hotmail.com)
//  @brief base class of kalman filter
//  @version 0.1
//  @date 2024-05-02
//  
//  @copyright Copyright (c) 2024
//  
#ifndef BAYESIAN_KALMAN_KF_BASE_H_
#define BAYESIAN_KALMAN_KF_BASE_H_

#include "custom_types.h"

namespace bayes_filter{
class KfBase{
 public:
  //  ========================  Func member  ==============================  //
  KfBase() = delete;

  //  @brief Construct a new Kalman Filter object 
  //  @param x : init value of state vector
  //  @param Q : init value of state covariance matrix
  //  @param R : init value of measurement covariance matrix
  explicit KfBase(float dt, VecXd x, MatXd Q, MatXd R) 
      : dt_(dt), x_(x), Q_(Q), R_(R)
  {
    x_dim_ = Q_.cols();
    z_dim_ = R_.cols();
  }
  
  virtual ~KfBase() {};
  
  // @brief   perform one step prediction to propagate state and covariance
  // @return  * void : 
  virtual void OneStepPrediction(const VecXd u){
    // Eq1. predict prior state estimation
    calcStateTransitionMatrix(x_, F_);
    calcControlMatrix(x_, G_);
    x_ = F_ * x_ + G_ * u;
    // Eq2. predict prior estimation covariance
    P_ = F_ * P_ * F_.transpose() + Q_;
  }
  
  // @brief   perform one step udate to correct state and covariance
  // @return  * void : 
  virtual void OneStepUpdate(const VecXd z){
    // eq3. calca Kalman gain K
    calcObservationMatrix(x_, H_);
    S_ = H_ * P_ * H_.transpose() + R_;
    K_ = P_ * H_.transpose() * S_.inverse();
    // eq4. update posterior state estimation
    y_ = z - H_ * x_;
    x_ = x_ + K_ * (z - y_);
    // eq5. update posterior estimation covariance
    P_ = P_ - K_ * H_ * P_;
  }

 protected:
  //  =========================  Data member  =============================  //
  uint8_t x_dim_, z_dim_;   // dim of state and measurement
  float dt_;    // discrete step
  VecXd x_;     // state vector
  VecXd y_;     // innovation vector
  VecXd z_;     // observation vector
  MatXd P_;     // state covariance matrix
  MatXd Q_, R_; // covariance matrix of process and observation
  MatXd F_, G_; // state-transition and control matrix
  MatXd K_;     // optimal gain
  MatXd H_;     // observation matrix
  MatXd S_;     // innovation covariance matrix

  //  ========================  Func member  ==============================  //
  // @brief   propagate current state x00 to prior prediction x01
  // @param   x : state vector
  virtual void StateTransitionFcn(VecXd x) = 0;
  
  // @brief   propagate prior prediction x01 to corresponding observation z01
  // @param   x01 : prior prediction of state
  // @param   z01 : prior prediction of observation
  virtual void ObservationFcn(const VecXd x01, VecXd z01) = 0;

  // @brief   calc state-transition matrix F of state x
  // @param   x : current state
  // @param   F : state-transition matrix F
  virtual void calcStateTransitionMatrix(const VecXd x, MatXd F) = 0;

  // @brief   calc control matrix G of u
  // @param   x : current state
  // @param   G : control matrix
  virtual void calcControlMatrix(const VecXd x, MatXd G) = 0;
  
  // @brief   calc observation matrix H
  // @param   x : current state
  // @param   H : observation matrix
  virtual void calcObservationMatrix(const VecXd x, MatXd H) = 0;
};
} // bayes_filter


#endif