#include<iostream>
using namespace std;
class point{
	public:
		point(double x=0.0, double y=0.0){
			this->x=x;
			this->y=y;
		}
		double getx(){return x;}
		void setx(double v){
			x=v;
		}
	private:
		int x;
		int y;
};
int main()
{
	char *s=new char[9];
	delete []s;
}
