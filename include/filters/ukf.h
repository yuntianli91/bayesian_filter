#ifndef MYFILTER_UKF_H_
#define MYFILTER_UKF_H_
#include "common_headers.h"

typedef Eigen::VectorXd VecXd;
typedef Eigen::MatrixXd MatXd;

using namespace std;

namespace myFilter{

class UKF{
public:
// ============= member functions ================= //
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    /// 构造函数
    UKF(){}
    explicit UKF(double alpha, double beta, double kappa);
    /// 析构函数
    virtual ~UKF();
    
    /// 虚函数，实现UKF默认的SigmaPoints采样策略
    virtual void generateSigmaPoints(); // 
    
    /// 纯虚函数，实现状态方程
    virtual void propagateFcn() = 0; // = 0声明为纯虚函数
    /// 纯虚函数，实现量测方程
    virtual void updateFcn() = 0; // 
    
    /// 初始化UKF
    void initUKF(VecXd Mu, MatXd Sigma, MatXd Q, MatXd R);
    /// UKF一步预测过程 
    void oneStepPrediction();
    /// UKF一步更新过程
    void oneStepUpdate(VecXd &Z);
    /// 计算加权均值
    VecXd calcMean(vector<VecXd> &sPoints);
    /// 计算加权协方差
    MatXd calcCov(vector<VecXd> &sPoints);
    /// 计算加权互协方差
    MatXd calcCrossCov(vector<VecXd> &sPointsX, vector<VecXd> &sPointsY);

    /// 设置参数
    void setAlpha(double alpha){alpha_ = alpha;}
    void setBeta(double beta){beta_ = beta;}
    void setKappa(double kappa){kappa_ = kappa;}

    /// 获取数据成员
    VecXd getMu(){return curMu_;}
    MatXd getSigma(){return curSigma_;}
protected:
// ============= member variables ================= //
    VecXd curMu_; // current mean
    MatXd curSigma_; // current covariance

    vector<VecXd> sPointsX_; // sigmapoints before propagation
    vector<VecXd> sPointsY_; // sigmapoints after propagation

    double alpha_, beta_, kappa_; // parameters for ukf
    double lambda_; // parameter

    double Wm0_, Wmi_; // weight of mean
    double Ws0_, Wsi_; // weight of covariance

    MatXd Q_, R_; // noise matrices

    int x_dim_, m_dim_; // dimensions of state and measurements 

    bool flag_initiated_ = false; // whether the filter in initialized
};

}
#endif