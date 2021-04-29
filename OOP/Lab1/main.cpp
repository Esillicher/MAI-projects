#include <iostream>
using namespace std;

// агрегация по ссылке. 15 вариант

class B;
class C;
class D;
class E;
class J;
class K;

class A{//объект связывается конструктором
public:
	A(B &b, C &c){	//передача по ссылке, от него берётся адрес и работаем с ним, а не с копией
		this->b = &b;	//this - указатель на объект от которого вызывается метод или который создаётся конструктором
		this->c = &c;
	}
	~A(){}
	B * ma(){//доступ через метод к объекту, B * - метод возвращает указатель на объект типа В
		return b; 
	};
	C * ma1(){//доступ через метод к объекту
		return c;
	};
private:
	B *b;
	C *c;
};

class B{//объект связывается конструктором
public:
	B(D &d) {
		this->d = &d;
	}
	~B(){}
	D *d;
	void mb(){
		cout << " method of B " << endl;
	}
};

class C{//объект связывается по переменной
public:
	C(){}
	E *e;//доступ через переменную к объекту
	J *j;
	void mc(){
		cout << " method of C " << endl;
	}
};

class D{
public:
	D(){}
	~D(){}
	void md(){
		cout << " method of D " << endl;
	}
private:
};

class E{
public:
	E(){}
	~E(){}
	void me(){
		cout << " method of E " << endl;
	}
};

class J{//объект связывается функцией
public:
	J(){}
	~J(){}
	void m_j1(){
		cout << " method of J " << endl;
	}
	void Link(K &k){ this->k = &k; }
	K * mj(){ return k; }//доступ через метод к объекту
private:
	K *k;//доступ через переменную к объекту
};

class K{
public:
	K(){}
	~K(){}
	void mk(){
		cout << " variant link K" << endl;
	}
};

void main(){

	C c;// 3 вариант, объявление объекта
	D d;
	E e;
	J j;// 4 вариант, объявление объекта
	c.e = &e;// 3 вариант связи
	c.j = &j;
	K k;
	j.Link(k);// 4 вариант связи 
	B b(d);// 2 вариант связи
	A a(b, c);// 1 вариант связи

	cout << "method of A" << endl;
	cout << "a->b";
	a.ma()->mb();// 1
	cout << "a->c";
	a.ma1()->mc();// 1


	cout << "b->d";
	b.d->md();// 2
	

	cout << "c->e";
	c.e->me();// 3
	cout << "c->j";
	c.j->m_j1();// 3

	cout << "j->k";
	j.mj()->mk();// 4




}
