#ifndef solo_sofm_RCPP_H
#define solo_sofm_RCPP_H
#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include "MATRIX.hh"

using namespace std;

class SOFM {

private:
    float   eta0, min_coeff, fmin0,
            coef, tmp, WeightingF, Wdis, cyc_frac;

    int     Nc0, Nc, lbX, lbY, ubX, ubY, indX, indY,
            mx1, my1, mxy, dlen, NWch, Iseed;

//    // time-steps at which to print out progress
//    const int Nwcyc[50] = {
//                    0, 1, 2, 3, 15, 50, 75, 100, 125, 150,
//                    175, 200, 225, 250, 275, 300, 325, 350, 375, 400,
//                    425, 450, 475, 500, 550, 600, 650, 700, 750, 800,
//                    850, 900, 950, 1000, 1050, 1100, 1150, 1200, 1250, 1300,
//                    1400, 1500, 1600, 1700, 1800, 2000, 2500, 3000, 3500, 3999 };
public:

    // constructor
    SOFM() {
        eta0 = 0.5;
        fmin0 = 1.0e10;
        min_coeff = 0.02;
        NWch = 20;
        Iseed = 1111;
    };

    // getters
    int get_NWch() const;
    int get_seed() const;
    float get_eta0() const;
    float get_fmin0() const;
    float get_min_coeff() const;

    // setters
    void set_NWch(const int new_nwch);
    void set_seed(const int new_seed);
    void set_eta0(const float new_eta0);
    void set_fmin0(const float new_fmin);
    void set_min_coeff(const float new_min_coeff);

    //functions
    void predict_map(
            const Matrix2Df data,
            const int node,
            const int nvar,
            const int nda,
            const int ncyc,
            const float width,
            Matrix3Df &Wi
            );

    void progress_bar(const double x, const double N);

    // destructor
    ~SOFM(){};
};
#endif
