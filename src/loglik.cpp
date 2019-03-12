#include <RcppArmadillo.h>
using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(RcppArmadillo)]]

// Function to compute the normalizing constant
inline double kappa(
    const arma::colvec & params,
    const arma::rowvec & weights,
    const arma::mat    & statmat
) {
  
  return arma::as_scalar(weights * exp(statmat * params));
  
}

// Calculates the likelihood for a given network individually.
inline void exact_logliki(
    const arma::rowvec & x,
    const arma::colvec & params,
    const arma::rowvec & weights,
    const arma::mat    & statmat,
    arma::vec & ans,
    int i,
    bool as_prob = false
) {
  
  if (!as_prob) {
    ans.at(i) = arma::as_scalar(x * params) - 
      log(kappa(params, weights, statmat));
  } else {
    ans.at(i) = exp(arma::as_scalar(x * params))/ 
      kappa(params, weights, statmat);
  }
  
  return;
  
}

//' Vectorized version of loglikelihood function
//' 
//' @param x Matrix of statistic. `nnets * nstats`.
//' @param params Vector of coefficients.
//' @param weights A list of weights matrices (for `statmat`).
//' @param statmat A list of matrices with statistics for each row in `x`.
//' @noRd
// [[Rcpp::export(name = "exact_loglik.")]]
arma::vec exact_loglik(
    const arma::mat & x,
    const arma::colvec & params,
    const std::vector< arma::rowvec > & weights,
    const std::vector< arma::mat > & statmat,
    bool as_prob = false
) {

  arma::vec ans(x.n_rows);
  int n = x.n_rows;
  
  // Checking the sizes
  if (weights.size() != statmat.size())
    stop("The weights and statmat lists must have the same length.");
  
  if (weights.size() > 1u) {
    
    for (int i = 0; i < n; ++i)
      exact_logliki(x.row(i), params, weights.at(i), statmat.at(i), ans, i, as_prob);
    
  } else {
    // In the case that all networks are from the same family, then this becomes
    // a trivial operation.
    ans = x * params - log(kappa(params, weights.at(0), statmat.at(0)));
    
  }
  
  return ans;
  
}


// Calculates the gradient for a given network individually.
inline arma::colvec exact_gradienti(
    const arma::rowvec & x,
    const arma::colvec & params,
    const arma::rowvec & weights,
    const arma::mat    & statmat
) {

  return x.t() - (statmat.t() * (weights.t() % exp(statmat * params)))/kappa(params, weights, statmat);

}

//' Vectorized version of gradient function
//' 
//' @param x Matrix of statistic. `nnets * nstats`.
//' @param params Vector of coefficients.
//' @param weights A list of weights matrices (for `statmat`).
//' @param statmat A list of matrices with statistics for each row in `x`.
//' @noRd
// [[Rcpp::export(name = "exact_gradient.")]]
arma::colvec exact_gradient(
    const arma::mat & x,
    const arma::colvec & params,
    const std::vector< arma::rowvec > & weights,
    const std::vector< arma::mat > & statmat
) {

  // Checking the sizes
  if (weights.size() != statmat.size())
    stop("The weights and statmat lists must have the same length.");

  if (weights.size() > 1u) {
    
    arma::colvec ans(x.n_cols);
    ans.fill(0.0);
    int n = x.n_rows;

    for (int i = 0; i < n; ++i)
      ans += exact_gradienti(x.row(i), params, weights.at(i), statmat.at(i));
    
    return ans;

  } else {
    // In the case that all networks are from the same family, then this becomes
    // a trivial operation.
    return exact_gradienti(x.row(0), params, weights.at(0), statmat.at(0));

  }

  

}



// // [[Rcpp::export]]
// arma::vec exact_gradient(
//     const arma::mat & x,
//     const arma::colvec & params,
//     const std::vector< arma::rowvec > & weights,
//     const std::vector< arma::mat > & statmat,
// ) {
// 
//   arma::vec ans(params.size());
// 
//   ans += x - (weights * exp(statmat * params) % statmat)/kappa(params, weights, statmat) ;
//   // arma::as_scalar(weights * exp(statmat * params))
//   return ans;
// 
// }