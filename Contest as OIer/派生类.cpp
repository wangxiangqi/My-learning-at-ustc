#include<iostream>
using namespace std;
class A{
public:
    A(int x,int y):x(x),y(y){}
    void show(){print();}  //�����Ա����ֱ�ӵ���protected��Ա
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
    {print();   //�����Ա����ֱ�ӵ��û���protected��Ա
    cout<<"z point:"<<z<<endl;}
private:
    int z;
    void another(){print();} //��Ȼ����public��ԱҲ�ܷ��ʻ���protected��Ա
};
int main()
{
    A a(2,3);
    B b(4,5,6);
    //a.print();//�����ԣ���������ܵ�������protected��Ա
    a.show();//���ԣ�����������public��Ա����ӵ���protected��Ա
    //b.print();//�����ԣ���������ܵ��û���protected��Ա
    b.output(); //���ԣ���������������public��Ա���ó�Ա�����ڲ������˻��ౣ����Աprint()
    return 0;
}
