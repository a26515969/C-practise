多項式運算主要是判斷次方的向次並且將相同向次的係數進行運算的一種模式

**Main**

  		int main()
		{
   		Polynomial a, b, c, d;
		cout << "(1) Input Data\n";
		/*
		a.getdata('A');
		b.getdata('B');
		*/
		
		a.set(1, 1); //1 x^1
		a.set(2,998); //2 x^2
		a.name = 'A';
		b.set(3, 2); //5 x^0
		b.set(1, 8); //3 x^3
		b.name = 'B';
		
在主程式中，我們輸入兩多項式次方以及係數並準備進行計算

		#define N 10000      // preset maximum number of coefficient for a polynomial
		class Polynomial {
		friend ostream& operator <<(ostream& os, Polynomial& s);
		private:
   		float coef[N];    // array of coefficients
   		int deg=0;        // the highest exponential degree of polynomial terms (0 for the zero polynomial)

		//define public member functions
		public:
	    	Polynomial() { 
			for (int i = 0; i < N; i++) coef[i] = 0;
	    	};
	    	char name=' ';
	    	void getdata(char c);           // get polynomial (coeff, order)s data
	    	void set(float a, int b);
	    	int degree();                   // find the deg of a polynomial
	    	float operator()(int x);
	   	float evaluate(int x);
	    	Polynomial differentiate();     // differentiate this polynomial and return it
	    	Polynomial operator+(Polynomial& b);
	    	Polynomial operator-(Polynomial& b);
	    	Polynomial& operator*(Polynomial& b);  // polynomial multiplication
		};

使用 N 來控制次方的極限次

Polynomial這個class是用來表示一個多項式的數學概念。它包含了多項式的係數、次數、名稱以及各種多項式運算，例如加法、減法、乘法、求導數、以及求某個特定值的函數值等等。它可以用來實現多項式的運算，並在程式中方便地表示和操作多項式。


		void Polynomial::set(float a, int b) { // function to set one term (a*x^b)
		    coef[b] = a;
		    if (b > deg) deg = b;
		    
判斷多項式的最高次方，最後如果 b 大於目前的最高次數，就將最高次數更新為 b
