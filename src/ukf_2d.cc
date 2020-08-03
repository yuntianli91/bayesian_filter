#include "filters/ukf_2d.h"

namespace myFilter{

UKF_2D::UKF_2D(double alpha, double beta, double kappa){
    alpha_ = alpha;
    beta_ = beta;
    kappa_ = kappa;
}

void UKF_2D::propagateFcn(){
    VecXd tmp = VecXd::Zero(x_dim_);

    Eigen::Matrix2d F;
    F << 1., 0.05, 0., 1.;

    for(auto it : sPointsX_){
        tmp = F * it;
        sPointsY_.emplace_back(tmp);
    }
}

void UKF_2D::updateFcn(){
    VecXd tmp = VecXd::Zero(m_dim_);
    
    for(auto it: sPointsX_){
        tmp(0) = sqrt(it(0));
        sPointsY_.emplace_back(tmp);
    }
}

}