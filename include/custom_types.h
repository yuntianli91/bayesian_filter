//  @file custom_types.h
//  @author Yuntian Li (yuntianlee91@hotmail.com)
//  @brief custom define type
//  @version 0.1
//  @date 2024-05-02
//  
//  @copyright Copyright (c) 2024
//  
#ifndef BAYESIAN_CUSTOM_TYPES_H_
#define BAYESIAN_CUSTOM_TYPES_H_

//  ===========================  header files =============================  //
// ========= std lib ============= //
#include <cstdlib>
#include <cstdio>
// ========= io headers ========== //
#include <fstream>
#include <sstream>
// ========== container ========== //
#include <vector>
#include <map>
#include <queue>
#include <iterator>
#include <string>
// ========== math ========== //
#include <cmath>
#include <random>
// ========== multi thread == //
#include <mutex>
#include <thread>
#include <condition_variable>
// ========== 3rd party ====== //
#include <Eigen/Dense>
#include <fmt/color.h>
#include <fmt/chrono.h>
#include <fmt/ostream.h>
#include <fmt/printf.h>

//  ===========================  data types  ==============================  //
typedef Eigen::Vector3d Vec3d;
typedef Eigen::Matrix<double, 6, 1> Vec6d;
typedef Eigen::VectorXd VecXd;
typedef Eigen::Matrix3d Mat3d;
typedef Eigen::Matrix<double, 6, 6> Mat6d;
typedef Eigen::MatrixXd MatXd;
typedef Eigen::Quaterniond Quatd; 

typedef Eigen::Vector3f Vec3f;
typedef Eigen::Matrix<float, 6, 1> Vec6f;
typedef Eigen::VectorXf VecXf;
typedef Eigen::Matrix3f Mat3f;
typedef Eigen::Matrix<float, 6, 6> Mat6f;
typedef Eigen::MatrixXf MatXf;
typedef Eigen::Quaternionf Quatf;
//  ========================= Constant Parmeters  ========================  //
#endif
