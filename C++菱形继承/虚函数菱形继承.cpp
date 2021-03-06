#include <iostream>
using namespace std;

class B
{
public:
	int ib;
	char cb;
public:
	B():ib(0),cb('B') {}

	virtual void f() { cout << "B::f()" << endl;}
	virtual void Bf() { cout << "B::Bf()" << endl;}
};
class B1 :  public B
{
public:
	int ib1;
	char cb1;
public:
	B1():ib1(11),cb1('1') {}

	virtual void f() { cout << "B1::f()" << endl;}
	virtual void f1() { cout << "B1::f1()" << endl;}
	virtual void Bf1() { cout << "B1::Bf1()" << endl;}

};
class B2:  public B
{
public:
	int ib2;
	char cb2;
public:
	B2():ib2(12),cb2('2') {}

	virtual void f() { cout << "B2::f()" << endl;}
	virtual void f2() { cout << "B2::f2()" << endl;}
	virtual void Bf2() { cout << "B2::Bf2()" << endl;}

};

//B1: f, f1, bf1,bf
//B2: f, f2, bf2, bf
//D:  f, f1, f2, df
//对象D包含两个虚表，虚表1是和B1共用的，虚表2是B2的
//派生类D覆盖了哪一个基类的函数，就放到哪一个函数的虚表中
//派生类D独有的例如Df，则放到B1的虚表中。
class D : public B1, public B2
{
public:
	int id;
	char cd;
public:
	D():id(100),cd('D') {}

	virtual void f() { cout << "D::f()" << endl;}
	virtual void f1() { cout << "D::f1()" << endl;}
	virtual void f2() { cout << "D::f2()" << endl;}
	virtual void Df() { cout << "D::Df()" << endl;}

};

int main()
{
	typedef void(*Fun)(void);
	int** pVtab = NULL;
	Fun pFun = NULL;

	D d;
	pVtab = (int**)&d;
	cout << "[0] D::B1::_vptr->" << endl;
	pFun = (Fun)pVtab[0][0];
	cout << "     [0] ";    pFun();
	pFun = (Fun)pVtab[0][1];
	cout << "     [1] ";    pFun();
	pFun = (Fun)pVtab[0][2];
	cout << "     [2] ";    pFun();
	pFun = (Fun)pVtab[0][3];
	cout << "     [3] ";    pFun();
	pFun = (Fun)pVtab[0][4];
	cout << "     [4] ";    pFun();
	pFun = (Fun)pVtab[0][5];
	cout << "     [5] 0x" << pFun << endl;

	cout << "[1] B::ib = " << (int)pVtab[1] << endl;
	cout << "[2] B::cb = " << (char)pVtab[2] << endl;
	cout << "[3] B1::ib1 = " << (int)pVtab[3] << endl;
	cout << "[4] B1::cb1 = " << (char)pVtab[4] << endl;

	cout << "[5] D::B2::_vptr->" << endl;
	pFun = (Fun)pVtab[5][0];
	cout << "     [0] ";    pFun();
	pFun = (Fun)pVtab[5][1];
	cout << "     [1] ";    pFun();
	pFun = (Fun)pVtab[5][2];
	cout << "     [2] ";    pFun();
	pFun = (Fun)pVtab[5][3];
	cout << "     [3] ";    pFun();
	pFun = (Fun)pVtab[5][4];
	cout << "     [4] 0x" << pFun << endl;

	cout << "[6] B::ib = " << (int)pVtab[6] << endl;
	cout << "[7] B::cb = " << (char)pVtab[7] << endl;   
	cout << "[8] B2::ib2 = " << (int)pVtab[8] << endl;
	cout << "[9] B2::cb2 = " << (char)pVtab[9] << endl;

	cout << "[10] D::id = " << (int)pVtab[10] << endl;
	cout << "[11] D::cd = " << (char)pVtab[11] << endl;
	return 0;
}