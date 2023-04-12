#include "Polynomial.h"
#include <iomanip>
void Polynomial::getdata(char c) {
  float coef;
  int exp;
    name = c;
    while(cin >> coef) {
        cin >> exp;
        set(coef, exp);
    }
    cin.clear();
    cin.ignore(100, '\n');
    cout << setw(4)<< ' '<< "Polynomial " << c << ": " << *this << endl;
};

Polynomial Polynomial::operator+(Polynomial& b)
{
    Polynomial c;
    for (int i = 0; i <= this->deg; i++) c.coef[i] += this->coef[i];
    for (int i = 0; i <= b.deg; i++) c.coef[i] += b.coef[i];
    c.deg = c.degree();
    return c;
}
Polynomial Polynomial::operator-(Polynomial& b)
{
    Polynomial C;
    for (int i = 0; i <= this->deg; i++) C.coef[i] -= this->coef[i];
    for (int i = 0; i <= b.deg; i++) C.coef[i] -= b.coef[i];
    C.deg = C.degree();
   
    return C;
}

Polynomial& Polynomial::operator*(Polynomial& b)  // polynomial multiplication
{
    Polynomial d;
    for (int i = 0; i <= this->deg; i++) {
        for (int j = 0; j <= b.deg; j++) {
            d.coef[i + j] += this->coef[i] * b.coef[j];
        }
    }
    d.deg = d.degree();
    return d;
}

Polynomial Polynomial::differentiate()
{
    Polynomial deriv;  // = new Polynomial ( 0, deg - 1 );
    deriv.deg = deg - 1;
    for (int i = 0; i <= deg - 1; i++) {
        deriv.coef[i] = (i + 1) * coef[i + 1];
    }
    
    return deriv;
}
 // using C(2) instead of C.evaluate(2)
 // to evaluate the polynomial when x=2
float Polynomial ::operator()(int x ) {
    
    float p = 0;
    for (int i = deg; i >= 0; i--) {
        p = p * x + coef[i];
    }
    return p;
    
}

// use Horner's method to compute and return the polynomial evaluated at x
// wiki: https://en.wikipedia.org/wiki/Horner%27s_method
// https://www.youtube.com/watch?v=RGrmEWj38bsc
// return the polynomial evaluation with value x
   // or 
float Polynomial::evaluate(int x) {
    
    return operator()(2);
}
// this function perform cout << poly operation
ostream& operator <<(ostream& os, Polynomial& s) {
    os << "(";
    for (int i = N-1; i >= 0; i--) {
        if (s.coef[i] != 0) {
            if (s.coef[i] > 0) os << "+";
            os << s.coef[i] << "x^" << i ;
        }
    }
    os << ")";
    return os;
}

void Polynomial::set(float a, int b) { // function to set one term (a*x^b)
    coef[b] = a;
    if (b > deg) deg = b;
}
int Polynomial::degree() {  // find the highest degree of this polynomial
    int d = 0;
    for (int i = N - 1; i >= 0; i--) 
        if (coef[i] != 0) { d = i; i = -1; };
    return d;
}