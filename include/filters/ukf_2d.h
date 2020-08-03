#ifndef MYFILTER_UKF_2D_H_
#define MYFILTER_UKF_2D_H_

#include "common_headers.h"
#include "filters/ukf.h"

namespace myFilter{

class UKF_2D : public UKF{
public:
    explicit UKF_2D(double alpha, double beta, double kappa);

    /// 基类状态方程的实现，本例中为常值
    void propagateFcn(); 
    /// 基类量测方程的实现，本例中为正弦
    void updateFcn();  
};

}

#endif