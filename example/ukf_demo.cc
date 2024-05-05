#include "common_headers.h"
#include "filters/ukf_1d.h"
#include "utilities/ioFunctions.hpp"
#include <cmath>
#include <matplotlibcpp.h> // matplotlib-cpp


using namespace std;

namespace plt = matplotlibcpp; // matplotlib-cpp

int main(int argc, char ** argv){

    default_random_engine e;
    normal_distribution<double> n(0, 2.5);
    // -------- data generation -------- // 
    int N = 500;
    vector<double> x(N), y(N);

    for(int i = 0; i < N; i++){
        x.at(i) = 25.0;
        y.at(i) = sqrt(25.0) + n(e);
    }
    // cout << x.transpose() << endl;
    // cout << y.transpose() << endl;

    // -------- filter -------- //
    myFilter::UKF_1D myUKF(0.9, 2., 2.);

    Eigen::VectorXd Mu0 = Eigen::VectorXd::Ones(1) * y[0] * y[0];
    Eigen::MatrixXd Sigma0 = Eigen::MatrixXd::Identity(1, 1) * 9;
    Eigen::MatrixXd Q0 = Eigen::MatrixXd::Identity(1, 1) * 0.01;
    Eigen::MatrixXd R0 = Eigen::MatrixXd::Identity(1, 1) * 2;
    // cout << Mu0 << endl << Sigma0 << endl << Q0 << endl << R0 << endl;
    
    myUKF.initUKF(Mu0, Sigma0, Q0, R0);

    vector<VecXd> all_mu;
    vector<MatXd> all_sigma;

    for (int i = 0; i < N; i++){
        myUKF.oneStepPrediction();
        Eigen::VectorXd Zk = Eigen::VectorXd::Ones(1) * y[i];
        myUKF.oneStepUpdate(Zk);

        VecXd mu = myUKF.getMu();
        MatXd Sigma = myUKF.getSigma();
        
        all_mu.emplace_back(mu);
        all_sigma.emplace_back(Sigma);
        
        // cout << i << ": " << mu << endl;
    }

    // writeFilterResults("../output/ukf_1d.csv", IO_CSV, all_mu, all_sigma);    

    // ====================== matplotlib-cpp ================================= //
    vector<double> x_est(N), p_est(N);

    for(int i = 0; i < N; i++){
        x_est.at(i) = all_mu[i](0);
        p_est.at(i) = all_sigma[i](0, 0);         
    }
    // -------------------------------
    plt::figure();
    
    plt::named_plot("true", x, "-b");
    plt::named_plot("obs", y, "-g");
    // 设置属性
    std::map<string, string> keywords;
    keywords.insert(make_pair("Color","tomato"));
    keywords.insert(make_pair("ls","--"));

    plt::named_plot("est", x_est, "--r");
    plt::grid(true);
    plt::legend();
    // -----------------------------
    plt::figure();
    plt::named_plot("P", p_est, "-b");
    plt::legend();
    plt::grid(true);
    // -----------------------------
    plt::show();
    // ============================================================ //


    return 0;

}

