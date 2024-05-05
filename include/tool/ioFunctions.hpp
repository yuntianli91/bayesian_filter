#ifndef IO_FUNCTION_H_
#define IO_FUNCTION_H_
#include "common_headers.h"

using namespace std;

enum FILE_FORMAT{
    IO_CSV = 0,
    IO_TXT = 1,
};

/**
 * @brief write mu and sigma
 * 
 * @param filename - data file name 
 * @param format - data file format, current txt and csv supported
 * @param Mu - all mu, std::vector<VecXd>
 * @param Sigma all sigma, std::vector<MatXd>
 */
void writeFilterResults(string filename, FILE_FORMAT format, vector<VecXd> &Mu, vector<MatXd> &Sigma){
    // check size
    if(Mu.size() != Sigma.size()){
        cout << "Mu size is not equal to Sigma size.\n";
        return;
    }
    // open file    
    ofstream ofsResult(filename);
    if(!ofsResult.is_open()){
        cout << "Failed to open results file.\n";
        return;
    }
    // choose delimeter
    string del;
    switch(format){
        case IO_CSV:
            del = ",";
            break;
        case IO_TXT:
            del = " ";
            break;
        default:
            cout << "Unknown format, use csv as default.\n";
            del = ",";
            break;
    }
    // save data
    for(size_t i = 0; i < Mu.size(); i++){
        // Mu
        ofsResult << Mu[i](0);
        for (size_t j = 1; j < Mu[0].size(); j++){
            ofsResult << del << Mu[i](j);
        }
        // Diag of Sigma
        for (size_t j = 0; j < Mu[0].size(); j++){
            ofsResult << del << Sigma[i](j, j);
        }
        ofsResult << endl;
    }

}


#endif