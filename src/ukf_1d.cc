#include "filters/ukf_1d.h"

namespace myFilter{

UKF_1D::UKF_1D(double alpha, double beta, double kappa){
    alpha_ = alpha;
    beta_ = beta;
    kappa_ = kappa;
}

void UKF_1D::propagateFcn(){
    VecXd tmp = VecXd::Zero(x_dim_);

    for(auto it : sPointsX_){
        tmp = it;
        sPointsY_.emplace_back(tmp);
    }
}

void UKF_1D::updateFcn(){
    VecXd tmp = VecXd::Zero(x_dim_);
    
    for(auto it: sPointsX_){
        tmp(0) = sqrt(it(0));
        sPointsY_.emplace_back(tmp);
    }
}

}