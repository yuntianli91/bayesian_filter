#include "filters/ukf.h"

namespace myFilter{

UKF::UKF(double alpha, double beta, double kappa){
    alpha_ = alpha;
    beta_ = beta;
    kappa_ = kappa;
}

UKF::~UKF(){
    
}

void UKF::initUKF(VecXd Mu, MatXd Sigma, MatXd Q, MatXd R)
{
    // check covariance matrix
    if (Q.cols() != Q.rows() || R.cols() != R.rows()){
        cerr << "Q or R is not square !\n";
        exit(1);
    }

    if (Sigma.cols() != Sigma.rows()){
        cerr << "Sigma is not square !\n";
        exit(1);
    }

    if(Mu.size() != Sigma.cols() || Mu.size() != Q.cols() 
        || Q.cols() != Sigma.cols())
    {
        cerr << "Mu, Sigma or Q size is wrong ! Their size are:\n"
            << "Mu: " << Mu.size() << ", "
            << "Sigma: " << Sigma.rows() << " x " << Sigma.cols() << ", "
            << "Q: " << Q.rows() << " x " << Q.cols() << endl;
        exit(1);
    }

    // set variables
    curMu_ = Mu;
    curSigma_ = Sigma;
    Q_ = Q;
    R_ = R;
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

void UKF::generateSigmaPoints(){
    VecXd tmp = VecXd::Zero(x_dim_);

    MatXd S_sqrt;
    // Cholsky分解
    // if(x_dim_ == 1){
    //     S_sqrt = MatXd::Zero(1, 1);
    //     S_sqrt(0, 0) = sqrt(curSigma_(0, 0));
    // }
    // else{
    //     S_sqrt = curSigma_.llt().matrixL();
    // }
    // 0
    S_sqrt = curSigma_.llt().matrixL();
   
    tmp = curMu_;
    sPointsX_.emplace_back(tmp);
    // 1 ~ n & n+1 ~ 2n
    for(int i = 0; i < x_dim_; i++){
        tmp = curMu_ + sqrt(x_dim_ + lambda_) * S_sqrt.col(i);
        sPointsX_.emplace_back(tmp);
    }

    for(int i = 0; i < x_dim_; i++){
        tmp = curMu_ - sqrt(x_dim_ + lambda_) * S_sqrt.col(i);
        sPointsX_.emplace_back(tmp);
    }
}


void UKF::oneStepPrediction(){
    if(!flag_initiated_){
        cerr << "Please call init() to initiate filter first !\n";
        return;
    }
    // clear containers
    sPointsX_.clear();
    sPointsY_.clear();
    // generate sigma points
    generateSigmaPoints();
    // propogate sigma points by f(x)
    propagateFcn();
    // compute predicted mean and covariance
    curMu_ = calcMean(sPointsY_);
    // cout << "MU_P: " << curMu_.transpose() << endl;
    curSigma_ = calcCov(sPointsY_) + Q_;
}

void UKF::oneStepUpdate(VecXd &Z){
    if(!flag_initiated_){
        cerr << "Please call init() to initiate filter first !\n";
        return;
    }
    // clear containers
    sPointsX_.clear();
    sPointsY_.clear();
    // generate sigma points
    generateSigmaPoints();
    // propagate sigma points by h(x)
    updateFcn();
    // compute tmp predicted mean and covariance
    VecXd M_tmp = calcMean(sPointsY_); // mu_k
    MatXd S_tmp = calcCov(sPointsY_) + R_; // S_k
    MatXd C_tmp = calcCrossCov(sPointsX_, sPointsY_); // C_k
    // compute estimation state
    MatXd K = C_tmp * S_tmp.inverse();
    curMu_ += K * (Z - M_tmp);
    curSigma_ -= K * S_tmp * K.transpose();
    // cout << "MU_U: " << curMu_.transpose() << endl;
}

VecXd UKF::calcMean(vector<VecXd> &sPoints){
    if(sPoints.size() != 2 * x_dim_ + 1){
        cerr << "Error size of sigma points.\n";
        exit(1);
    }
    // ------ init temp container ------ //
    VecXd Mu = VecXd::Zero(x_dim_);
    // ------ calculate weighted mean ------ //
    for (int i = 0; i < sPoints.size(); i++){
        if(i==0){
            Mu += Wm0_ * sPoints[i];
        }
        else{
            Mu += Wmi_ * sPoints[i];
        }
    }
    // ------ return result ------//
    return Mu;
}

MatXd UKF::calcCov(vector<VecXd> &sPoints){
    if(sPoints.size() != 2 * x_dim_ + 1){
        cerr << "Error size of sigma points.\n";
        exit(1);
    }
    // ------ init temp container ------ //
    VecXd Mu = VecXd::Zero(x_dim_);
    MatXd Sigma = MatXd::Zero(x_dim_, x_dim_);
    // ------ calc mean first ------ //
    Mu = calcMean(sPoints);
    // ------ calculate weighted covariance ------ //
    for(int i = 0; i < sPoints.size(); i++){
        VecXd delta = sPoints[i] - Mu;// delta = x - mu
        
        if (i==0){
            Sigma += Ws0_ * delta * delta.transpose(); 
        }
        else{
            Sigma += Wsi_ * delta * delta.transpose(); 
        }
    }
    // ------ return result ------ //
    return Sigma;
}

MatXd UKF::calcCrossCov(vector<VecXd> &sPointsX, vector<VecXd> &sPointsY){
    if(sPointsX.size() != 2 * x_dim_ + 1 || sPointsY.size() != 2 * x_dim_ + 1){
        cerr << "Error size of sigma points.\n";
        exit(1);
    }
    // ------ init temp container ------ //
    int dim_x = sPointsX[0].size();
    int dim_y = sPointsY[0].size();

    VecXd Mu_x = VecXd::Zero(dim_x);
    VecXd Mu_y = VecXd::Zero(dim_y);

    MatXd Sigma = MatXd::Zero(dim_x, dim_y);
    // ------ calc mean first ------ //
    Mu_x = sPointsX[0];
    Mu_y = calcMean(sPointsY);
    // ------ calculate weighted covariance ------ //
    for(int i = 0; i < sPointsX.size(); i++){
        VecXd delta_x = sPointsX[i] - Mu_x;// delta = x - mu
        VecXd delta_y = sPointsY[i] - Mu_y; // delta = x - mu
        
        if (i==0){
            Sigma += Ws0_ * delta_x * delta_y.transpose(); 
        }
        else{
            Sigma += Wsi_ * delta_x * delta_y.transpose(); 
        }
    }
    // ------ return result ------ //
    return Sigma;
}

}