jet_path <- getwd()
utils_wilcox_cpp <- function(x, y) {
    library(Rcpp)
    sourceCpp(paste0(jet_path, "/fast_wilcox.cpp"))
    wilcoxon_test(x, y)
}


utils_pca_cpp <- function(data, dims) {
    library(Rcpp)
    library(RcppArmadillo)
    sourceCpp(paste0(jet_path, "/fast_pca.cpp"))
    pca_cpp(data, dims)
}

utils_nmf_cpp <- function(V, k) {
    library(Rcpp)
    library(RcppArmadillo)
    sourceCpp(paste0(jet_path, "/fast_nmf.cpp"))
    nmf_cpp(V, k)
}
