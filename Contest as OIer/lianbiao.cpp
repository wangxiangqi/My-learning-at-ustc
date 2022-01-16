#include<iostream>
using namespace std;
struct elem
{
	char data;
	elem* next;
};
class slist
{
	public:
		slist():h(0) {}
		~slist():{release();}
	private:
		elem *h;
};
void prepend(char *c)
{
	elem *temp=new elem;
	temp->next=h;
	temp->data=c;
	h=temp;//«∞÷√¡¥±Ì 
}
int main()
{
	
}
