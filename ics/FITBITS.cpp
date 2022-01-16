#include<stdio.h>
int FitBits(int x,int n)
{
	int c=33+~n;
	int t=(x<<c)>>c;
    return !(x^t);
}
int main()
{
	int x=0x00005674;
	int y=0xffff7834;
	int z=0x0f0f0f32;
	//printf("%0x",x^y);
	//不要忘了^表示亦或，xor；
    printf("%d",FitBits(x,16));
	printf("%d",FitBits(z,3)); 
}
