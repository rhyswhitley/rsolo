#ifndef _solo_matrix_H
#define _solo_matrix_H
#define _USE_MATH_DEFINES

#include<vector>

/******************************************************************
   HEAD FILE: MATRIX.h
   THIS IS HEAD FILE OF PROGRAM MATRIX.c
*******************************************************************/
using namespace std;

typedef vector< vector<float> > Matrix2Df;
typedef vector< vector< vector<float> > > Matrix3Df;

void alloc_Mat2D(const int nrow, const int ncol, Matrix2Df &matrix);
void alloc_Mat3D(const int nrow, const int ncol, const int nshelf, Matrix3Df &matrix);

#endif
