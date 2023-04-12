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
