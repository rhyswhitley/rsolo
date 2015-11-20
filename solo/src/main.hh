#ifndef solo_rcpp_main_H
#define solo_rcpp_main_H

#include <Rcpp.h>
#include "sofm.hh"

using namespace Rcpp;

RcppExport SEXP solo_main(const SEXP R_data, const SEXP R_map_settings);

#endif
