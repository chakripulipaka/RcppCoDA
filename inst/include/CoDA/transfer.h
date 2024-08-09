#ifndef CODA__TRANSFER__H
#define CODA__TRANSFER__H

#include "RcppEigen.h"
#include "contrast.h"

namespace coda {
    template <typename TX, typename TV1, typename TV2>
    Eigen::MatrixXd ilr2ilr(Eigen::MatrixBase<TX>& X, 
                            Eigen::MatrixBase<TV1>& V1, 
                            Eigen::MatrixBase<TV2>& V2){
        MatrixXd V = iiTransfer(V1, V2);
        MatrixXd Y = linForm(X, V);
        return Y;
    }
    
    template <typename TX, typename TV1>
    Eigen::MatrixXd ilr2clr(Eigen::MatrixBase<TX>& X, 
                            Eigen::MatrixBase<TV1>& V1){
        MatrixXd V = icTransfer(V1);
        MatrixXd Y = linForm(X, V);
        return Y;
    }
    
    template <typename TX, typename TV2>
    Eigen::MatrixXd clr2ilr(Eigen::MatrixBase<TX>& X, 
                            Eigen::MatrixBase<TV2>& V2){
        MatrixXd V = ciTransfer(V2);
        MatrixXd Y = linForm(X, V);
        return Y;
    }
    
    template <typename TX>
    Eigen::MatrixXd alr2clr(Eigen::MatrixBase<TX>& X, int d1){
        MatrixXd V = acTransfer(d1, X.rows()+1);
        MatrixXd Y = linForm(X, V);
        return Y;
    }
    
    template <typename TX>
    Eigen::MatrixXd clr2alr(Eigen::MatrixBase<TX>& X, int d2){
        MatrixXd V = caTransfer(d2, X.rows());
        MatrixXd Y = linForm(X, V);
        return Y;
    }
    
    template <typename TX>
    Eigen::MatrixXd alr2alr(Eigen::MatrixBase<TX>& X, int d1, int d2){
        MatrixXd V = aaTransfer(d1, d2, X.rows()+1);
        MatrixXd Y = linForm(X, V);
        return Y;
    }
    
    template <typename TX, typename TV>
    Eigen::MatrixXd ilr2alr(Eigen::MatrixBase<TX>& X, 
                            Eigen::MatrixBase<TV>& V1, int d2){
        MatrixXd V = iaTransfer(V1, d2, X.rows()+1);
        MatrixXd Y = linForm(X, V);
        return Y;
    }
    
    template <typename TX, typename TV>
    Eigen::MatrixXd alr2ilr(Eigen::MatrixBase<TX>& X,int d1, Eigen::MatrixBase<TV>& V2){
        MatrixXd V = aiTransfer(d1, V2, X.rows()+1);
        MatrixXd Y = linForm(X, V);
        return Y;
    }
}