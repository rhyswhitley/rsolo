/*************************************************************************************************
 * Matrix creator using std library vector type. This replaces old array allocation
 *
 * Author: Rhys Whitley
 * Date: 30 October 2015
*************************************************************************************************/

#include "MATRIX.hh"

void alloc_Mat2D(const int nrow, const int ncol, Matrix2Df &matrix) {

    matrix.resize(nrow);

    for(int i = 0; i < nrow; i++) {
        matrix[i].resize(ncol, 0.f);
    }
}

void alloc_Mat3D(const int nrow, const int ncol, const int nshelf, Matrix3Df &matrix) {

    matrix.resize(nrow);

    for(int i = 0; i < nrow; i++) {
        matrix[i].resize(ncol);

        for(int j = 0; j < ncol; j++) {
            matrix[i][j].resize(nshelf, 0.f);
        }
    }

}
