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

	cout << "�麯�����ַ��" << (int*)(&b) << endl;
	//*(int*)&b �൱��ȡ��vptr��ʵ�ʵ�ֵ�����ֵ�Ǹ�ָ�룩
	int * vptr = (int*) *(int*)&b; //Ҳ���������һЩ
	//vptr[0]�����һ���麯����ַ�� vptr[1]����ڶ����麯����ַ

	cout << "�麯���� �� ��һ��������ַ��" << *(int*)*(int*)(&b) << " "<<vptr[0]<<endl;
	cout << "�麯���� �� �ڶ���������ַ��" << *((int*)*(int*)(&b)+1) << " " <<vptr[1]<< endl;
	cout << "�麯���� �� ������������ַ��" << *((int*)*(int*)(&b)+2) << " " <<vptr[2]<< endl;

	// Invoke the first virtual function 
	pFun = (Fun)*((int*)*(int*)(&b));
	pFun();
	pFun = (Fun)( vptr[1] ); //second virtual function
	pFun(); 
	pFun = (Fun)( vptr[2] ); //third virtual function
	pFun();	

	Derived d;
	cout << "d �麯�����ַ��" << (int*)(&d) << endl;
	cout << "d �麯���� �� ��һ��������ַ��" << *(int*)*(int*)(&d) << endl;
	cout << "d �麯���� �� �ڶ���������ַ��" << *((int*)*(int*)(&d)+1) << endl;
	cout << "d �麯���� �� ������������ַ��" << *((int*)*(int*)(&d)+2) << endl;
	vptr = (int*) *(int*)&d; //Ҳ���������һЩ
	pFun = (Fun)*((int*)*(int*)(&d));
	pFun();
	pFun = (Fun)( vptr[1] ); //second virtual function
	pFun(); 
	pFun = (Fun)( vptr[2] ); //third virtual function
	pFun();
	Base* pd = &d;
	cout << "pd�麯���� �� ��һ��������ַ��" << *(int*)*(int*)(pd) << endl;

	cout<<endl;
	//������Կ�����ǿתʱ������ʵ���Ͻ��������͵Ĳö�����Ӧ�ĸ��ĵ�vptr��
	Base b2;
	cout << "b2�麯���� �� ��һ��������ַ��" << *(int*)*(int*)(&b2) << endl;
	b2=*(Base*)&d;
	cout << "b2�麯���� �� ��һ��������ַ��" << *(int*)*(int*)(&b2) << endl;
}
int main()
{
	test1();
	return 0;
}