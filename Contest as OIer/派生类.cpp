#include<iostream>
using namespace std;
class A{
public:
    A(int x,int y):x(x),y(y){}
    void show(){print();}  //基类成员可以直接调用protected成员
protected:
    void print()
    {cout<<"x point:"<<x<<endl<<"y point:"<<y<<endl;}
private:
    int x;
    int y;
};
class B:public A{
public:
    B(int x,int y,int z):A(x,y),z(z){}
    void output() 
    {print();   //子类成员可以直接调用基类protected成员
    cout<<"z point:"<<z<<endl;}
private:
    int z;
    void another(){print();} //当然，非public成员也能访问基类protected成员
};
int main()
{
    A a(2,3);
    B b(4,5,6);
    //a.print();//不可以，基类对象不能调用自身protected成员
    a.show();//可以，基类对象调用public成员，间接调用protected成员
    //b.print();//不可以，子类对象不能调用基类protected成员
    b.output(); //可以，子类对象调用自身public成员，该成员函数内部调用了基类保护成员print()
    return 0;
}
