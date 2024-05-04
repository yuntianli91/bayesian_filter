//  @file kf.h
//  @author Yuntian Li (yuntianlee91@hotmail.com)
//  @brief base class of kalman filter
//  @version 0.1
//  @date 2024-05-02
//  
//  @copyright Copyright (c) 2024
//  
#ifndef BAYESIAN_KALMAN_KF_H_
#define BAYESIAN_KALMAN_KF_H

#include "custom_types.h"

class KalmanFilter{
 public:
  //  ========================  Func member  ==============================  //
  KalmanFilter() = delete;
  //  @brief Construct a new Kalman Filter object 
  //  @param x : init value of state vector
  //  @param Q : init value of state covariance matrix
  //  @param R : init value of measurement covariance matrix
  explicit KalmanFilter(VecXd x, MatXd Q, MatXd R);
  virtual ~KalmanFilter() {};
  //  @brief  状态一步预测方程，纯虚函数，需要根据实际需求重写。
  virtual void OneStePrediction() = 0;
  //  @brief  量测一步更新方程，纯虚函数，需要根据实际需求重写。
  virtual void OneStepUpdate() = 0;

 private:
  //  =========================  Data member  =============================  //
  uint8_t x_dim_, z_dim_;    // dim of state and measurement
  VecXd x_, z_;   // state vector and measurement vector
  MatXd Q_, R_;
  //  ========================  Func member  ==============================  //

};


#endif