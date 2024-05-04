//  @file ekf.h
//  @author Yuntian Li (yuntianlee91@hotmail.com)
//  @brief  base class of extended kalman filter
//  @version 0.1
//  @date 2024-05-02
//  
//  @copyright Copyright (c) 2024
//  

#ifndef BAYESIAN_KALMAN_EKF_H_
#define BAYESIAN_KALMAN_EKF_H

#include <fmt/format.h>
#include <eigen3/Eigen/Dense>

class ExtendKalmanFilter{
public:
private:
uint8_t dim_state, dim_meas;  // dims of state and measurements
};


#endif