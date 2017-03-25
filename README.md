# virtualFunction
How virtual function works in C++? Some c++ codes and analysis.

##Basic information about virtual function

声明：
    我现在已经忘记了这个代码出自何处了，看着不像我自己写的，应该是学习虚函数的时候下载的其他人的代码。非常感谢贡献代码的那个人，如果您看到，请联系我，我将您加入到这个说明里面。如果您不希望自己的代码被传到github，也请告诉我，我将其删除。

### Simple Model
    Base b
    --------
    | vptr |  ->  | 虚函数表  |
    |  a   |
    |  b   |
    --------
    int ** pVptr = (int **)&b;
    pVptr[0][0] 代表第一个表中的第一个项目（虚函数的地址）
### Object Layout for Mutiple inheritence
摘抄的一段内存布局(http://www.openrce.org/articles/full_view/23)：

    class A
    {
        int a1;
    public:
        virtual int A_virt1();
        virtual int A_virt2();
        static void A_static1();
        void A_simple1();
    };
    class B
    {
        int b1;
        int b2;
    public:
        virtual int B_virt1();
        virtual int B_virt2();
    };
    class C: public A, public B
    {
        int c1;
    public:
        virtual int A_virt2();
        virtual int B_virt2();
    };

MSVC layout

    class A size(8):
    +---
    0 | {vfptr}
    4 | a1
    +---
    A's vftable:
    0 | &A::A_virt1
    4 | &A::A_virt2
    class B size(12):
    +---
    0 | {vfptr}
    4 | b1
    8 | b2
    +---
    B's vftable:
    0 | &B::B_virt1
    4 | &B::B_virt2
    class C size(24):
    +---
    | +--- (base class A)
    0 | | {vfptr}
    4 | | a1
    | +---
    | +--- (base class B)
    8 | | {vfptr}
    12 | | b1
    16 | | b2
    | +---
    20 | c1
    +---
    C's vftable for A:
    0 | &A::A_virt1
    4 | &C::A_virt2
    C's vftable for B:
    0 | &B::B_virt1
    4 | &C::B_virt2

### Diamond inheritance and virtual inheritance are still in question!
### need to be explored. Know how to print the class layout of C++ object.
# Print Class Layout
1. cl [source.cpp] /d1reportSingleClassLayout 
2. Project -> properties -> Configure Property -> C/C++ -> Additional Options
    add "/d1reportSingleClassLayout"