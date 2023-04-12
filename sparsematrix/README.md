在這份檔案中，我們應用自行撰寫的轉置矩陣程式碼來對稀疏矩陣進行旋轉

**main**

'''C++

	SparseMatrix A, B, C, D;

	ifstream fin;

	if (argc == 1) fin.open("sparse.txt");  // open the default sparsematrix data 
	
	else fin.open(argv[1]);
	
	if (!fin) { // check whether fin is correct or not
	
		cout << "the input file [" << "sparse2.txt" << "] open error\n"; exit(1);
		
	}
	
	else { 
	
		fin >> A >> B>> C >> D;
		
	}
	
	fin.close();
	
	
'''

我們使用四個稀疏矩陣進行運算，在檢查檔案後，我們依序載入A, B, C, D四個矩陣

**標頭檔定義**

'''C++

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

'''


首先，先定義一個MatrixTerm的函數類別，分別儲存行、列、矩陣中非0元素以及定義了兩個 friend 函數：operator<< 和 operator>>，
由於在稀疏矩陣中大部分的元素都是0，為了縮小儲存空間，我們只儲存矩陣中的非0元素。用來組成稀疏矩陣。

'''C++

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

'''

SparseMatrix 建構函式，可以初始化稀疏矩陣的列數、行數和非零元素的數量，預設值分別為0、0和20，
並寫提供矩陣轉置、快速轉置、矩陣加法和矩陣乘法等操作。


**函數定義**


'''C++

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

'''

生成一個新的矩陣，目的是先把bt矩陣所有的元素設置為0。接著遍歷原矩陣中的所有非0元素，將它的行列號進行互換，並且把該元素放入bt矩陣中對應的位置，因此可以得到轉置矩陣bt。
其中while迴圈中的條件可以用來找出bt矩陣中應該放置的位置，而for迴圈中的兩個set()函式可以用來將元素放入bt矩陣中，Terms變量則用來紀錄bt矩陣中元素的數量。


