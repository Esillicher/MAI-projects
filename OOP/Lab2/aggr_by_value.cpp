#include <iostream>
using namespace std;

class A;
class B;
class C;
class D;
class E;
class J;
class K;

class D {
private:
	int d;
public:
	D(){ d = 0; }
	~D(){}
	void m_d(){
		d++;
		cout << "d = " << d << endl;
	}
};

class E {
private:
	int e;
public:
	E(){ e = 0; }
	~E(){}
	void m_e(){
		e++;
		cout << "e = " << e << endl;
	}
};

class K {
private:
	int k;
public:
	K(){ k = 0; }
	~K(){}
	void m_k(){
		k++;
		cout << "k = " << k << endl;
	}
};

class J{
private:
	K k;
public:
	J(){}
	~J(){}
	void m_jk(){
		cout << "j->";
		k.m_k();
	}
	K* get_k(){ return &k; }
};

class C{
private:
	E e;
	J j;
public:
	C(){}
	~C(){}
	void m_ce(){
		cout << "c->";
		e.m_e();
	}
	E* get_e(){ return &e; }
	void m_cj(){
		cout << "c->";
		j.m_jk();
	}
	J* get_j(){ return &j; }
};

class B{
private:
	D d;
public:
	B(){}
	~B(){}
	void m_bd(){
		cout << "b->";
		d.m_d();
	}
	D* get_d(){ return &d; }
};

class A{
private:
	B b;
	C c;
public:
	A(){}
	~A(){}
	void m_ab(){
		cout << "a->";
		b.m_bd();
	}
	B* get_b(){ return &b; }
	void m_ac(){
		cout << "a->";
		c.m_ce();
		c.m_cj();
	}
	C* get_c(){ return &c; }
};

int main(){
	A a;
	J j_out;

	a.m_ab();
	a.m_ac();

	a.get_b()->get_d()->m_d();
	a.get_c()->get_e()->m_e();
	a.get_c()->get_j()->get_k()->m_k();

	cout << endl << "j - not part of C" << endl;
	j_out.m_jk();
	cout << endl << "j - part of C" << endl;
	a.get_c()->get_j()->m_jk();

	return 0;
}