// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "ergmito_types.h"
#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

// count_available
std::vector< std::string > count_available(int i);
RcppExport SEXP _ergmito_count_available(SEXP iSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::traits::input_parameter< int >::type i(iSEXP);
    rcpp_result_gen = Rcpp::wrap(count_available(i));
    return rcpp_result_gen;
END_RCPP
}
// count_stats
NumericMatrix count_stats(const ListOf< IntegerMatrix >& X, const std::vector< std::string >& terms, const ListOf< NumericVector >& A);
RcppExport SEXP _ergmito_count_stats(SEXP XSEXP, SEXP termsSEXP, SEXP ASEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::traits::input_parameter< const ListOf< IntegerMatrix >& >::type X(XSEXP);
    Rcpp::traits::input_parameter< const std::vector< std::string >& >::type terms(termsSEXP);
    Rcpp::traits::input_parameter< const ListOf< NumericVector >& >::type A(ASEXP);
    rcpp_result_gen = Rcpp::wrap(count_stats(X, terms, A));
    return rcpp_result_gen;
END_RCPP
}
// geodesic
std::vector< IntegerMatrix > geodesic(const std::vector< arma::imat >& X, bool force);
RcppExport SEXP _ergmito_geodesic(SEXP XSEXP, SEXP forceSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::traits::input_parameter< const std::vector< arma::imat >& >::type X(XSEXP);
    Rcpp::traits::input_parameter< bool >::type force(forceSEXP);
    rcpp_result_gen = Rcpp::wrap(geodesic(X, force));
    return rcpp_result_gen;
END_RCPP
}
// new_ergmito_ptr
SEXP new_ergmito_ptr(const arma::mat& target_stats, const std::vector< arma::rowvec >& stats_weights, const std::vector< arma::mat >& stats_statmat);
RcppExport SEXP _ergmito_new_ergmito_ptr(SEXP target_statsSEXP, SEXP stats_weightsSEXP, SEXP stats_statmatSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::mat& >::type target_stats(target_statsSEXP);
    Rcpp::traits::input_parameter< const std::vector< arma::rowvec >& >::type stats_weights(stats_weightsSEXP);
    Rcpp::traits::input_parameter< const std::vector< arma::mat >& >::type stats_statmat(stats_statmatSEXP);
    rcpp_result_gen = Rcpp::wrap(new_ergmito_ptr(target_stats, stats_weights, stats_statmat));
    return rcpp_result_gen;
END_RCPP
}
// exact_loglik
arma::vec exact_loglik(SEXP ptr, const arma::colvec& params, bool as_prob, int ncores);
RcppExport SEXP _ergmito_exact_loglik(SEXP ptrSEXP, SEXP paramsSEXP, SEXP as_probSEXP, SEXP ncoresSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::traits::input_parameter< SEXP >::type ptr(ptrSEXP);
    Rcpp::traits::input_parameter< const arma::colvec& >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< bool >::type as_prob(as_probSEXP);
    Rcpp::traits::input_parameter< int >::type ncores(ncoresSEXP);
    rcpp_result_gen = Rcpp::wrap(exact_loglik(ptr, params, as_prob, ncores));
    return rcpp_result_gen;
END_RCPP
}
// exact_gradient
arma::vec exact_gradient(SEXP ptr, const arma::colvec& params, bool as_prob, int ncores);
RcppExport SEXP _ergmito_exact_gradient(SEXP ptrSEXP, SEXP paramsSEXP, SEXP as_probSEXP, SEXP ncoresSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::traits::input_parameter< SEXP >::type ptr(ptrSEXP);
    Rcpp::traits::input_parameter< const arma::colvec& >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< bool >::type as_prob(as_probSEXP);
    Rcpp::traits::input_parameter< int >::type ncores(ncoresSEXP);
    rcpp_result_gen = Rcpp::wrap(exact_gradient(ptr, params, as_prob, ncores));
    return rcpp_result_gen;
END_RCPP
}
// exact_hessian
arma::mat exact_hessian(const arma::mat& x, const arma::colvec params, const std::vector< arma::rowvec >& stats_weights, const std::vector< arma::mat >& stats_statmat, int ncores);
RcppExport SEXP _ergmito_exact_hessian(SEXP xSEXP, SEXP paramsSEXP, SEXP stats_weightsSEXP, SEXP stats_statmatSEXP, SEXP ncoresSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::traits::input_parameter< const arma::mat& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const arma::colvec >::type params(paramsSEXP);
    Rcpp::traits::input_parameter< const std::vector< arma::rowvec >& >::type stats_weights(stats_weightsSEXP);
    Rcpp::traits::input_parameter< const std::vector< arma::mat >& >::type stats_statmat(stats_statmatSEXP);
    Rcpp::traits::input_parameter< int >::type ncores(ncoresSEXP);
    rcpp_result_gen = Rcpp::wrap(exact_hessian(x, params, stats_weights, stats_statmat, ncores));
    return rcpp_result_gen;
END_RCPP
}
// induced_submat
std::vector< IntegerMatrix > induced_submat(const std::vector< IntegerMatrix >& nets, const std::vector< IntegerVector >& vs);
RcppExport SEXP _ergmito_induced_submat(SEXP netsSEXP, SEXP vsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector< IntegerMatrix >& >::type nets(netsSEXP);
    Rcpp::traits::input_parameter< const std::vector< IntegerVector >& >::type vs(vsSEXP);
    rcpp_result_gen = Rcpp::wrap(induced_submat(nets, vs));
    return rcpp_result_gen;
END_RCPP
}
// matrix_to_network
ListOf< List > matrix_to_network(const ListOf< IntegerMatrix >& x, const LogicalVector& directed, const LogicalVector& hyper, const LogicalVector& loops, const LogicalVector& multiple, const LogicalVector& bipartite);
RcppExport SEXP _ergmito_matrix_to_network(SEXP xSEXP, SEXP directedSEXP, SEXP hyperSEXP, SEXP loopsSEXP, SEXP multipleSEXP, SEXP bipartiteSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::traits::input_parameter< const ListOf< IntegerMatrix >& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const LogicalVector& >::type directed(directedSEXP);
    Rcpp::traits::input_parameter< const LogicalVector& >::type hyper(hyperSEXP);
    Rcpp::traits::input_parameter< const LogicalVector& >::type loops(loopsSEXP);
    Rcpp::traits::input_parameter< const LogicalVector& >::type multiple(multipleSEXP);
    Rcpp::traits::input_parameter< const LogicalVector& >::type bipartite(bipartiteSEXP);
    rcpp_result_gen = Rcpp::wrap(matrix_to_network(x, directed, hyper, loops, multiple, bipartite));
    return rcpp_result_gen;
END_RCPP
}
// make_sets
vecint make_sets(int n, bool directed);
RcppExport SEXP _ergmito_make_sets(SEXP nSEXP, SEXP directedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< bool >::type directed(directedSEXP);
    rcpp_result_gen = Rcpp::wrap(make_sets(n, directed));
    return rcpp_result_gen;
END_RCPP
}
// powerset
SEXP powerset(int n, bool force, bool directed);
RcppExport SEXP _ergmito_powerset(SEXP nSEXP, SEXP forceSEXP, SEXP directedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< bool >::type force(forceSEXP);
    Rcpp::traits::input_parameter< bool >::type directed(directedSEXP);
    rcpp_result_gen = Rcpp::wrap(powerset(n, force, directed));
    return rcpp_result_gen;
END_RCPP
}
// wrap_powerset
List wrap_powerset(SEXP sets, int from, int to, int n);
RcppExport SEXP _ergmito_wrap_powerset(SEXP setsSEXP, SEXP fromSEXP, SEXP toSEXP, SEXP nSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::traits::input_parameter< SEXP >::type sets(setsSEXP);
    Rcpp::traits::input_parameter< int >::type from(fromSEXP);
    Rcpp::traits::input_parameter< int >::type to(toSEXP);
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_powerset(sets, from, to, n));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_ergmito_count_available", (DL_FUNC) &_ergmito_count_available, 1},
    {"_ergmito_count_stats", (DL_FUNC) &_ergmito_count_stats, 3},
    {"_ergmito_geodesic", (DL_FUNC) &_ergmito_geodesic, 2},
    {"_ergmito_new_ergmito_ptr", (DL_FUNC) &_ergmito_new_ergmito_ptr, 3},
    {"_ergmito_exact_loglik", (DL_FUNC) &_ergmito_exact_loglik, 4},
    {"_ergmito_exact_gradient", (DL_FUNC) &_ergmito_exact_gradient, 4},
    {"_ergmito_exact_hessian", (DL_FUNC) &_ergmito_exact_hessian, 5},
    {"_ergmito_induced_submat", (DL_FUNC) &_ergmito_induced_submat, 2},
    {"_ergmito_matrix_to_network", (DL_FUNC) &_ergmito_matrix_to_network, 6},
    {"_ergmito_make_sets", (DL_FUNC) &_ergmito_make_sets, 2},
    {"_ergmito_powerset", (DL_FUNC) &_ergmito_powerset, 3},
    {"_ergmito_wrap_powerset", (DL_FUNC) &_ergmito_wrap_powerset, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_ergmito(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
