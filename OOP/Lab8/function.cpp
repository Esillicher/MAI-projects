#include <iostream>
using namespace std;

template <class T> void swp(T& x, T& y)
{
	T temp;
	temp = x;
	x = y;
	y = temp;
}

class A {
public:
	int var1, var2;
	A(){ var1 = 0; };
	A(int a, int b, double c)
	{
		this->var1 = a; this->var2 = b; this->var3 = c;
	}
	double get_var3(){ return var3; }
private:
	double var3;
};

int main() {
	int n = 10, k = 20;
	cout << "n = " << n << ", k = " << k << endl << endl;
	
	swp(n, k);
	cout << "after swap: " << endl << "n = " << n << ", k = " << k << endl << endl;

	A a1(10, 100, 101.1);
	A a2(20, 200, 202.2);
	cout << "a1.var1 = " << a1.var1 << ", a1.var2 = " << a1.var2 << ", a1.var3 = " << a1.get_var3() << endl;
	cout << "a2.var1 = " << a2.var1 << ", a2.var2 = " << a2.var2 << ", a2.var3 = " << a2.get_var3() << endl;

	swp(a1, a2);
	cout << endl << "after swap:" << endl;
	cout << "a1.var1 = " << a1.var1 << ", a1.var2 = " << a1.var2 << ", a1.var3 = " << a1.get_var3() << endl;
	cout << "a2.var1 = " << a2.var1 << ", a2.var2 = " << a2.var2 << ", a2.var3 = " << a2.get_var3() << endl;

	return 0;
}