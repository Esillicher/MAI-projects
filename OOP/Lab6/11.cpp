#include <iostream>
using namespace std;

class A;

class C{
public:
	C(){}
	~C(){}
	void set_a(A &_a){	//передача ссылки на объект класса А при вызове функции
		cout << "attach A pos: " << &_a << endl;
		a = &_a;
	}
	A* get_a(){
		cout << "C->A  ";
		return a;
	}
	void m(){
		cout << "method of C" << endl;
	};
private:
	A *a;
protected:
};

class A{
public:
	A(){}
	~A(){}
	void set_c(C &_c){	//передача ссылки на объект класса С при вызове функции
		cout << "attach C pos: " << &_c << endl;
		c = &_c;
	}
	C* get_c(){
		cout << "A->C  ";
		return c;
	}
	void m(){
		cout << "method of A" << endl;
	};
private:
	C *c;
protected:
};

int main(){

	A a;
	C c;

	c.set_a(a);// через метод объекта класса C передаётся ссылка на объект класса A при вызове функци
	a.set_c(c);// через метод объекта класса A передаётся ссылка на объект класса С при вызове функци
	// с помощью методов объекты связываются

	a.get_c()->m();// через метод объекта класса A возвращается ссылка на объект класса С и вызывается метод m объекта класса С
	c.get_a()->m();// через метод объекта класса C возвращается ссылка на объект класса A и вызывается метод m объекта класса A

}
