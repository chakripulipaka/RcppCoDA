#ifndef CODA__CODAMATH__H
#define CODA__CODAMATH__H

#include <RcppEigen.h>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::Map;
using Eigen::MatrixBase;
using Eigen::SparseMatrix;


// Convention here is that samples are columns and parts are rows
// This is notably different than how Driver was originally implemented. Sorry
// for any confusion.

namespace coda {

  //' Closure divide each column by column sum
  //' @param X matrix
  //' @return matrix of same dimension as X
  template <typename T>
  Eigen::MatrixXd clo(Eigen::DenseBase<T>& X){
    VectorXd s = X.colwise().sum();
    int c = X.cols();
    MatrixXd Y(X.rows(), X.cols());
    for (int i=0; i<c; i++) Y.col(i) = X.col(i)/s(i);
    return Y;
  }

  //' Center opteration - subtract each column by column mean
  //' @param X matrix
  //' @return matrix of same dimension as X
  template <typename T>
  Eigen::MatrixXd center(Eigen::DenseBase<T>& X){
    VectorXd n = X.colwise().mean();
    X.rowwise() -= n.transpose();
    return X;
  }

  //' Linear form Y=VX
  //' @param X data (D x N)
  //' @param V (P X D, e.g., transfer Contrast matrix)
  //' @details Calculates
  //'     
  //'   Y = V * X
  //'
  //' @return Eigen::MatrixXd
  //' @name linForm
  template <typename TX, typename TV>
  Eigen::MatrixXd linForm(Eigen::MatrixBase<TX>& X,
                              Eigen::MatrixBase<TV>& V){
    int D = X.rows();
    int N = X.cols();
    if (X.rows() != V.cols()) throw
    std::invalid_argument("X.rows() >= V1.cols()");

    return V*X;

  }
  
} /* End coda Namespace */

#endif 
