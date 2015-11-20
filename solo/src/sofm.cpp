/* ************************************************************
// Kohonen's Self-Organizing Neural Network
//
// Kuo-lin Hsu
// August 4, 1995
//
// Modifications to be called by R
// Rhys Whitley
// March 3, 2013
// ************************************************************/

// INCLUDE HEAD FILES
#include "sofm.hh"

// setters
void SOFM::set_eta0(const float new_eta0) {
    eta0 = new_eta0;
}

void SOFM::set_min_coeff(const float new_min_coeff) {
    min_coeff = new_min_coeff;
}

void SOFM::set_fmin0(const float new_fmin) {
    fmin0 = new_fmin;
}

void SOFM::set_NWch(const int new_nwch) {
    NWch = new_nwch;
}
void SOFM::set_seed(const int new_seed) {
    Iseed = new_seed;
}

// getters
float SOFM::get_eta0() const {
    return eta0;
}

float SOFM::get_min_coeff() const {
    return min_coeff;
}

float SOFM::get_fmin0() const {
    return fmin0;
}

int SOFM::get_NWch() const {
    return NWch;
}

int SOFM::get_seed() const {
    return Iseed;
}

// functions
void SOFM::predict_map(
            const Matrix2Df data,
            const int node,
            const int nvar,
            const int nda,
            const int ncyc,
            const float width,
            Matrix3Df &Wi
            ) {


    Matrix2Df nodesum;
    Matrix3Df Wi_old;

    float fmin;

    // assign memory for variables
    alloc_Mat2D( node, node, nodesum );
    alloc_Mat3D( node, node, nvar, Wi );
    alloc_Mat3D( node, node, nvar, Wi_old );

    // used for print results to screen [probably drop]
    dlen = (int)(ncyc/NWch);
    // initializing weight matrix: Wi[i][j][k]
    srand(Iseed);

    for( int k=0; k<nvar; k++ ) {
        for( int i=0; i<node; i++ ) {
            for( int j=0; j<node; j++ ) {
                tmp = ((1.0*rand())/(1.0*RAND_MAX)) * width;
                Wi[i][j][k] = 0.5 + (tmp - width/2.0);
                Wi_old[i][j][k] = Wi[i][j][k];
    }   }   }

    // LEARNING:
    // 1. Summation total of inputs and weights
    // 2. Training points closing to best fited point (within nC neighbor)
    // 3. Lower bounds: LBx,LBy; upper bounds: UBx,UBy

    Nc0 = node / 2;

    // training loop:
    for( int i1=0; i1<ncyc; i1++ ) {

        // start progress bar
        progress_bar(i1, ncyc);

        // setup training coefficient and training neighbours
        cyc_frac = 1.0 - (1.0*i1)/(1.0*ncyc);
        coef = max(eta0*cyc_frac, min_coeff);
        Nc = (int)(Nc0*cyc_frac);

        for( int i2=0; i2<nda; i2++) {
        // find the distance between inputs and weight vector
        // find the point with minimum distance to the weight vector
        // and it's index (indX and indY)
            fmin = fmin0;
            for( int i=0; i<node; i++ ) {
                for( int j=0; j<node; j++ ) {

                    nodesum[i][j] = 0.0;
                    for( int k=0; k<nvar; k++) {
                    // FIND THE DISTANCE BETWEEN INPUTS AND WEIGHT VECTOR
                        tmp = data[i2][k] - Wi[i][j][k];
                        nodesum[i][j] += pow(tmp, 2);
                    }
                    nodesum[i][j] = pow(nodesum[i][j], 0.5);
                    // FIND THE MINIMUM NODE AND ITS INDEX:
                    if(nodesum[i][j] < fmin) {
                        fmin = nodesum[i][j];
                        indX = i;
                        indY = j;
                    }
            }   }

            // find the training upper bounds and lower bounds
            lbX = max(indX - Nc, 0);
            lbY = max(indY - Nc, 0);
            ubX = min(indX + Nc, node - 1);
            ubY = min(indY + Nc, node - 1);

            // training input weights and output weights within
            // neighborhood nC around the best point
            for( int i=lbX; i<ubX+1; i++) {
                // setup weighting factor for points around the best point
                for( int j=lbY; j<ubY+1; j++) {
                    mx1 = abs(i-indX);
                    my1 = abs(j-indY);
                    mxy = max(mx1, my1);
                    WeightingF = 1.0 / (mxy + 1.0);
                    // inputs & input weights
                    for( int k=0; k<nvar; k++) {
                        Wi[i][j][k] = Wi[i][j][k] + WeightingF*coef*(data[i2][k] - Wi[i][j][k]);
            }   }   }

        } // end of [i2] loop

//  // print the distance between two connection weights with NWch iteration:
//        if((i1%NWch) == 0) {
//            tmp = 0;
//            for( int i=0; i<node; i++) {
//                for( int j=0; j<node; j++) {
//                    for( int k=0; k<nvar; k++) {
//
//                        tmp += pow((Wi[i][j][k] - Wi_old[i][j][k]), 2.0);
//                        Wi_old[i][j][k] = Wi[i][j][k];
//            }}}
//            Wdis = pow(tmp, 0.5);
//
//            REAL(C_distN)[m+dlen*0] = (double)i1;
//            REAL(C_distN)[m+dlen*1] = (double)Nc0;
//            REAL(C_distN)[m+dlen*2] = (double)Nc;
//            REAL(C_distN)[m+dlen*3] = (double)eta0;
//            REAL(C_distN)[m+dlen*4] = (double)coef;
//            REAL(C_distN)[m+dlen*5] = (double)Wdis;
//            m++;
//            printf( "  %ld\t  %ld  %ld  %f  %f  %f\n", i1, Nc0, Nc, eta0, coef, Wdis );
//        }

    } // end of [i1] loop

    // By this point sofm will return a 3D matrix containing the weights that describe
    // the clustering of input data. Additionally a report file is return describing
    // convergence and other problems
}

void SOFM::progress_bar(const double x, const double N) {
    // how wide you want the progress meter to be
    int totaldotz = 40;
    double fraction = x/N;
    // part of the progressmeter that's already "full"
    int dotz = round(fraction * totaldotz);

    // create the "meter"
    int ii=0;
    printf("%3.0f%% [",fraction*100);
    // part  that's full already
    for ( ; ii < dotz; ii++) {
        printf("=");
    }
    // remaining part (spaces)
    for ( ; ii < totaldotz; ii++) {
        printf(" ");
    }
    // and back to line begin - do not forget the fflush to avoid output buffering problems!
    printf("]\r");
    fflush(stdout);
}
