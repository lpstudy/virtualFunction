#include <iostream>
using namespace std;

class Base1 {
public:
	virtual void f() { cout << "Base1::f" << endl; }
	virtual void g() { cout << "Base1::g" << endl; }
	virtual void h() { cout << "Base1::h" << endl; }
	virtual void b1() { cout << "Base1::b1" << endl; }
	//int x;  //������ô˱�������ӡBase2��3���麯�����ʱ�򣬾���Ҫ����������ĸ��ֽ�
};

class Base2 {
public:
	virtual void f() { cout << "Base2::f" << endl; }
	virtual void g() { cout << "Base2::g" << endl; }
	virtual void h() { cout << "Base2::h" << endl; }
	virtual void b2() { cout << "Base1::b2" << endl; }
};

class Base3 {
public:
	virtual void f() { cout << "Base3::f" << endl; }
	virtual void g() { cout << "Base3::g" << endl; }
	virtual void h() { cout << "Base3::h" << endl; }
};


class Derive : public Base1, public Base2, public Base3 {
public:
	virtual void f() { cout << "Derive::f" << endl; }
	virtual void g1() { cout << "Derive::g1" << endl; }
	virtual void b1() { cout << "Derive::b1" << endl; }//����base1��b1���� 
};


typedef void(*Fun)(void);

int main()
{
	Fun pFun = NULL;

	Derive d;
	int** pVtab = (int**)&d;

	cout<<"Base1 vtable:"<<endl;
	//Base1's vtable
	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+0);
	pFun = (Fun)pVtab[0][0];
	pFun();

	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+1);
	pFun = (Fun)pVtab[0][1];
	pFun();

	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+2);
	pFun = (Fun)pVtab[0][2];
	pFun();

	//Derive's vtable
	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+3);
	pFun = (Fun)pVtab[0][3];
	pFun();

	//The tail of the vtable
	pFun = (Fun)pVtab[0][4];
	cout<<pFun<<endl;
   

	cout<<"Base2 vtable:"<<endl;
	//ע����ֱ��ʹ��pVtalbe[1]��ʱ����Ҫע�⣬������Ҫ����Base1�е��麯����ռ�õ�4���ֽڣ�����Ҫ����Base1�е����ݱ�����ƫ�ơ�
	//Base2's vtable
	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);
	pFun = (Fun)pVtab[1][0];
	pFun();

	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);
	pFun = (Fun)pVtab[1][1];
	pFun();

	pFun = (Fun)pVtab[1][2];
	pFun();

	//The tail of the vtable
	pFun = (Fun)pVtab[1][3];
	pFun();
	cout<<pFun<<endl;


	cout<<"Base3 vtable:"<<endl;
	//Base3's vtable
	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);
	pFun = (Fun)pVtab[2][0];
	pFun();

	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);
	pFun = (Fun)pVtab[2][1];
	pFun();

	pFun = (Fun)pVtab[2][2];
	pFun();

	//The tail of the vtable
	pFun = (Fun)pVtab[2][3];
	cout<<pFun<<endl;

	return 0;
}