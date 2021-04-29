#include <iostream>
using namespace std;

template <class T> class K {
public:
	K(){}

	T& get_obj() { return obj; }
	void swap(T& recieved_obj) // принимаем объект класса по ссылке
	{
		T temp;
		temp = recieved_obj;
		recieved_obj = obj;
		obj = temp;
	}
private:
	T obj;
};

class A {
public:
	A() { var = 0; }
	A(int num) { this->var = num; }
	int get_var() { return var; }
private:
	int var;
};

int main() {
	A a(5);
	K <A> k;

	cout << "a.get_var() = " << a.get_var() << endl;
	cout << "k.get_obj().get_var() = " << k.get_obj().get_var() << endl;
	
	cout << endl;

	k.swap(a);
	cout << "swap: a.get_var() = " << a.get_var() << endl;
	cout << "swap: k.get_obj().get_var() = " << k.get_obj().get_var() << endl;

	return 0;
}