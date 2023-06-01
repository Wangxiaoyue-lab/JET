#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

using namespace Rcpp;
using namespace RcppArmadillo;

// [[Rcpp::export]]
List nmf_cpp(NumericMatrix V, int k, int max_iter = 1000) {
  int m = V.nrow();
  int n = V.ncol();

  arma::mat W = arma::abs(arma::mat(V(Range(0, m - 1), Range(0, k - 1))));
  arma::mat H = arma::abs(arma::mat(V(Range(0, k - 1), Range(0, n - 1))));
 
  for (int iter = 0; iter < max_iter; iter++) {
    arma::mat WH = W * H;
    for (int i = 0; i < k; i++) {
    for (int j = 0; j < n; j++) {
      double sum1 = 0;
      double sum2 = 0;
      for (int l = 0; l < m; l++) {
        sum1 += W(l, i) * V(l, j);
        sum2 += W(l, i) * WH(l, j);
      }
      if (sum2 == 0) continue;
        H(i, j) *= sum1 / sum2;
      }
    }

    WH = W * H;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < k; j++) {
        double sum1 = 0;
        double sum2 = 0;
        for (int l = 0; l < n; l++) {
          sum1 += H(j, l) * V(i, l);
          sum2 += H(j, l) * WH(i, l);
        }
        if (sum2 == 0) continue;
        W(i, j) *= sum1 / sum2;
    }
   }
  }

return List::create(Named("W")=Rcpp::wrap(W), Named("H")=Rcpp::wrap(H));
}
