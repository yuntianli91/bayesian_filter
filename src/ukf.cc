#include "filters/ukf.h"

namespace myFilter{

UKF::UKF(double alpha, double beta, double kappa){

}

UKF::~UKF(){
    
}

void UKF::initUKF(MatXd Q_, MatXd R_){
    // check covariance matrix
    if (Q_.cols() != Q_.rows() || R_.cols() != R_.rows()){
        cerr << "Q or R is not square !\n";
        return;
    }
    // get dimensions of state and measurements    
    x_dim_ = Q_.cols();
    m_dim_ = R_.cols();
    // calculate lambda
    lambda_ = alpha_ * alpha_ * (x_dim_ + kappa_) - x_dim_;    
    // calculate weight parameters
    Wm0_ = lambda_ / (x_dim_ + lambda_);
    Ws0_ = Wm0_ + (1. - alpha_ * alpha_ + beta_);

    Wmi_ = 0.5 / (x_dim_ + lambda_);
    Wsi_ = Wmi_;
    // set initialized flag to true
    flag_initiated_ = true;
}


void UKF::oneStepPrediction(){

}

void UKF::oneStepUpdate(){

}

VecXd UKF::calcMean(vector<VecXd> &sigma_points){
    // ------ init temp container ------ //
    int N = sigma_points.size();
    VecXd Mu = VecXd::Zero(N);

    // ------ return result ------//
    return Mu;
}

MatXd UKF::calcCov(vector<VecXd> &sigma_points){
    // ------ init temp container ------ //
    int N = sigma_points.size();
    MatXd Sigma = VecXd::Zero(N, N);
    // ------ return result ------ //
    return Sigma;
}



}