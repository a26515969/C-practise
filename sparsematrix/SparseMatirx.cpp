#include <fstream>
#include <iomanip>
#include "SparseMatrix.h"

char compare(int a, int b) {
	if (a > b) return '>';
	else if (a < b) return '<';
	else if (a == b) return '=';
};


SparseMatrix SparseMatrix::Transpose()
{  
	SparseMatrix bt(this->Cols, this->Rows, this->Terms);  
	for (int i = 0; i < this->Terms; i++) {
		int j = 0;//表示第幾個非0元素
		while (j < bt.Terms && bt.smArray[j].col < this->smArray[i].row) {
			j++;
		}
		//if (j < bt.Terms && bt.smArray[j].col == this->smArray[i].row) {
			//bt.smArray[j].value += this->smArray[i].value;
		//}
		//else {
			for (int k = bt.Terms - 1; k >= j; k--) {
				bt.smArray[k + 1].set(bt.smArray[k]);
			}
			bt.smArray[j].set(this->smArray[i].col, this->smArray[i].row, this->smArray[i].value);
			bt.Terms++;
		//}
	}
	
	return bt; // or return *b 
}

// Fast Transpose
SparseMatrix SparseMatrix::FastTranspose()
{//  O(terms + cols) time complexity	
	SparseMatrix b(Cols, Rows, Terms);
	
	if (Terms > 0) {
		int* rowTerms = new int[Cols];
		int* startingPos = new int[Cols];
		for (int i = 0; i < Cols; i++) rowTerms[i] = 0;
		for (int i = 0; i < Terms; i++) rowTerms[smArray[i].col]++;
		startingPos[0] = 0;
		for (int i = 1; i < Cols; i++) startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		for (int i = 0; i < Terms; i++) {
			int j = startingPos[smArray[i].col];
			b.smArray[j].row = smArray[i].col;
			b.smArray[j].col = smArray[i].row;
			b.smArray[j].value = smArray[i].value;
			startingPos[smArray[i].col]++;
		}
		delete[] rowTerms;
		delete[] startingPos;
	}

	return b;
}


istream& operator>>(istream& is, SparseMatrix& m)
// read in a matrix and set up its linked representation.
// An auxiliary array head is used
{
	is >> m.Rows >> m.Cols >> m.Terms; // matrix dimensions
	is.clear(); is.ignore(100, '\n');
	int CurrentA = 0;
	for (int i = 0; i < m.Terms; i++)
	{
		is >> m.smArray[i].row >> m.smArray[i].col >> m.smArray[i].value;
		is.clear(); is.ignore(100, '\n');
	}
	return is;
}

ostream& operator<<(ostream& os, SparseMatrix& m)
{   if(m.Rows)
	if (m.Rows*m.Cols<30) {
		int i, j;
		int** A = new int* [m.Rows];
		for (i = 0; i < m.Rows; i++)
			A[i] = new int[m.Cols];

		for (i = 0; i < m.Rows; i++)
			for (j = 0; j < m.Cols; j++)
				A[i][j] = 0;
		MatrixTerm* p = m.smArray;
		for (i = 0; i < m.Terms; i++)
			A[p[i].row][p[i].col] = p[i].value;
		for (i = 0; i < m.Rows; i++) {
			for (j = 0; j < m.Cols; j++)
				os << setw(4) << A[i][j];
			os << endl;
		}
		os << endl;
	}
	else {
		for (int i = 0; i < m.Terms; i++)
			os << "(" << setw(4)<<m.smArray[i].row << "," <<setw(4)<< m.smArray[i].col << "," <<setw(4)<< m.smArray[i].value << ")" << endl;
		os << endl;
	}
	return os;
}





SparseMatrix &SparseMatrix::operator*(SparseMatrix &b)
{
	SparseMatrix bt = b.Transpose();    
	SparseMatrix *c = new SparseMatrix(this->Rows, b.Cols, 0);
	int sum = 0;

	// iterate through each row of the first matrix
	if (Terms * bt.Terms != 0) { // 先判斷兩個矩陣是否為空矩陣
		int index = 0;
		int rowBegin = 0;
		int sum = 0;

		this->smArray[Terms].row = this->Rows;  // 表示尾部元素的行列號為矩陣行列號
		bt.smArray[bt.Terms].row = bt.Rows;

		for (int i = 0; i < this->Terms;) {
			int row = this->smArray[i].row;
			for (int j = 0; j < b.Terms;) {
				int col = b.smArray[j].row;
				int sum = 0;
				for (int k = i; k < this->Terms && this->smArray[k].row == row; k++) {
					for (; j < b.Terms && b.smArray[j].row == col; j++) {
						if (this->smArray[k].col == b.smArray[j].col) {
							sum += this->smArray[k].value * b.smArray[j].value;
						}
						else if (this->smArray[k].col < b.smArray[j].col) {
							continue;
						}
						else {
							break;
						}
					}
				}
				if (sum != 0) {
					c->smArray[c->Terms].set(row, col, sum);
					c->Terms++;
				}
				while (j < b.Terms && b.smArray[j].row == col) {
					j++;
				}
			}
			while (i < this->Terms && this->smArray[i].row == row) {
				i++;
			}
		}
		
	}

	
	return *c;
}

SparseMatrix& SparseMatrix::operator+(SparseMatrix& b)
{
	SparseMatrix *c=new SparseMatrix(this->Rows, this->Cols, this->Terms);
	
	int i = 0, j = 0, k = 0;

	while (i < Terms && j < b.Terms) {
		if (smArray[i].row < b.smArray[j].row ||
			(smArray[i].row == b.smArray[j].row && smArray[i].col < b.smArray[j].col)) {
			c->smArray[k++] = smArray[i++];
		}
		else if (smArray[i].row == b.smArray[j].row && smArray[i].col == b.smArray[j].col) {
			if (smArray[i].value + b.smArray[j].value != 0) {
				c->smArray[k].row = smArray[i].row;
				c->smArray[k].col = smArray[i].col;
				c->smArray[k++].value = smArray[i++].value + b.smArray[j++].value;
			}
			else {
				i++;
				j++;
			}
		}
		else {
			c->smArray[k++] = b.smArray[j++];
		}
	}

	// copy remaining elements from the first matrix
	for (; i < Terms; i++) {
		c->smArray[k++] = smArray[i];
	}

	// copy remaining elements from the second matrix
	for (; j < b.Terms; j++) {
		c->smArray[k++] = b.smArray[j];
	}

	c->Terms = k;
	return *c;
}