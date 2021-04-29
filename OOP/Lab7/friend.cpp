#include <iostream>

using namespace std;

class B;

class A{
public:
	int get_a(){
		cout << "A construct: a=" << a << endl;
		return a;
	}

private:
	friend int main();// позволяет с main вызывать скрытый конструктор
	friend class B; // говорит о том, что на переменные можно сослаться из класса В, даже если они скрытые

	int a;
	A(){ a = -10; } // скрытый конструктор
protected:
};

class B{
public:
	B(){ b = 100; }
	B(A *a0) : b(a0->a){ // инициализирует значение b по значению а класса А
		cout << "B construc with A: a=" << b << endl;
	}

	int get_b(){ 
		cout << "B construct: b=" << b << endl;
		return b; 
	}
	
private:
	int b;
protected:
};

int main()
{

	A *a;
	B *b;

	a = new A;
	b = new B;

	a->get_a();
	b->get_b();

	cout << endl;

	B b1(new A);


	/*
	char ch;
	cin >> ch;
	return 0;
	*/
}
