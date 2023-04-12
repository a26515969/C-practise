#include <iostream>
using namespace std;
#ifndef _SPARSE_MATRIX
#define _SPARSE_MATRIX

class SparseMatrix;

class MatrixTerm{
    friend ostream & operator<<(ostream & os, SparseMatrix& m);
    friend istream & operator>>(istream & is, SparseMatrix& m);
    friend class SparseMatrix;
public: 
    void set(int r, int c, int v) {
        row = r, col = c, value = v;
    };
    void set(MatrixTerm& m) {
        row = m.row; col = m.col; value = m.value;
    };
private: int row,col,value;
};


class SparseMatrix
{
   friend ostream & operator<<(ostream & os, SparseMatrix& m);
   friend istream & operator>>(istream & is, SparseMatrix& m);
public:
   SparseMatrix(int ncol = 0, int nrow = 0, int nterm = 20) :
        Rows(nrow), Cols(ncol), Terms(nterm) {
        for (int i = 0; i < Terms; i++) smArray[i].set(0, 0, 0);
    };
   SparseMatrix Transpose();
   SparseMatrix FastTranspose();
   SparseMatrix & operator+(SparseMatrix& b);
   SparseMatrix & operator*(SparseMatrix& b);  // polynomial multiplication
  
   private:
    int Rows, Cols, Terms;  
    MatrixTerm smArray[20];
};

#endif