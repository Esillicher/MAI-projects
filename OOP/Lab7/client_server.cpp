#include <iostream>

using namespace std;

class A{
public:
	A(){ a = 2; }
	~A(){}

	int get_a(){ return a; }
private:
	int a;
protected:
};

class B{
public:
	B(){ b = 10; }
	~B(){}
	int get_b(){ return b; }

	// из В обращаемся к А
	void mb(A &a){ // в кач-ве параметра передаётся ссылка на объект класса А
		cout << "client method" << endl;
		cout << "client b=" << b + a.get_a() << endl;
		cout << "server a=" << a.get_a() << endl;
	}
private:
	int b;
protected:
};


int main()
{

	A a;
	B b;
	
	cout << "a=" << a.get_a() << endl;
	cout << "b=" << b.get_b() << endl;

	cout << endl;

	b.mb(a); // обращаемся к серверу


	/*
	char ch;
	cin >> ch;
	return 0;
	*/
}