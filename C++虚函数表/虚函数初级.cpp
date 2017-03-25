#include <iostream>
using namespace std;


class Base {
public:
	virtual void f() { cout << "Base::f" << endl; }
	virtual void g() { cout << "Base::g" << endl; }
	virtual void h() { cout << "Base::h" << endl; }

};


class Derived : public Base{
public:
	virtual void f() {cout <<"Derived::f"<<endl;}
};

void test1()
{
	typedef void(*Fun)(void);

	Base b;

	Fun pFun = NULL;

	cout << "虚函数表地址：" << (int*)(&b) << endl;
	//*(int*)&b 相当于取得vptr的实际的值（这个值是个指针）
	int * vptr = (int*) *(int*)&b; //也许会更好理解一些
	//vptr[0]代表第一个虚函数地址， vptr[1]代表第二个虚函数地址

	cout << "虚函数表 — 第一个函数地址：" << *(int*)*(int*)(&b) << " "<<vptr[0]<<endl;
	cout << "虚函数表 — 第二个函数地址：" << *((int*)*(int*)(&b)+1) << " " <<vptr[1]<< endl;
	cout << "虚函数表 — 第三个函数地址：" << *((int*)*(int*)(&b)+2) << " " <<vptr[2]<< endl;

	// Invoke the first virtual function 
	pFun = (Fun)*((int*)*(int*)(&b));
	pFun();
	pFun = (Fun)( vptr[1] ); //second virtual function
	pFun(); 
	pFun = (Fun)( vptr[2] ); //third virtual function
	pFun();	

	Derived d;
	cout << "d 虚函数表地址：" << (int*)(&d) << endl;
	cout << "d 虚函数表 — 第一个函数地址：" << *(int*)*(int*)(&d) << endl;
	cout << "d 虚函数表 — 第二个函数地址：" << *((int*)*(int*)(&d)+1) << endl;
	cout << "d 虚函数表 — 第三个函数地址：" << *((int*)*(int*)(&d)+2) << endl;
	vptr = (int*) *(int*)&d; //也许会更好理解一些
	pFun = (Fun)*((int*)*(int*)(&d));
	pFun();
	pFun = (Fun)( vptr[1] ); //second virtual function
	pFun(); 
	pFun = (Fun)( vptr[2] ); //third virtual function
	pFun();
	Base* pd = &d;
	cout << "pd虚函数表 — 第一个函数地址：" << *(int*)*(int*)(pd) << endl;

	cout<<endl;
	//这里可以看出，强转时编译器实际上进行了类型的裁定，相应的更改的vptr。
	Base b2;
	cout << "b2虚函数表 — 第一个函数地址：" << *(int*)*(int*)(&b2) << endl;
	b2=*(Base*)&d;
	cout << "b2虚函数表 — 第一个函数地址：" << *(int*)*(int*)(&b2) << endl;
}
int main()
{
	test1();
	return 0;
}