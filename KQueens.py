str_in = input()
#print(str_in)
num =list(map(int, str_in.strip().split()))
#print(num)
n=int(num[0])
m=int(num[1])
K=int(num[2])
#keyboard=[[0 for _ in range(m)] for _ in range(n)]
#利用conflict数组优化复杂度
vertical=[0 for _ in range(10086)]
horizon=[0 for _ in range(10086)]
squarch=[0 for _ in range(10086)]
duijich=[0 for _ in range(10086)]
#print(keyboard)
while K>=1:
    K = K - 1
    num_temp=input()
    num_temp=list(map(int,num_temp.strip().split()))
    i=int(num_temp[0])
    #print(i)
    j=int(num_temp[1])
    #print(j)
    if horizon[i - 1] != 1:
        horizon[i - 1] = 1
        #for l in range(m):
        #    keyboard[i-1][l]=1 #horizontal
    if vertical[j - 1] != 1:
        vertical[j - 1] = 1
        #for o in range(n):
        #    keyboard[o][j-1]=1 #vertical
    #print(keyboard)
    if squarch[i-j]!=1:
        squarch[i-j]=1
        #sqar=max(-i,-j)
        #while (sqar<min(horiz,vertic)):
        #    keyboard[i+sqar][j+sqar]=1
        #    sqar=sqar+1
            #print(keyboard)
    if duijich[i+j-2]!=1:
        duijich[i+j-2]=1
        #sqar=max(-j+1,-vertic)
        #while (sqar<min(horiz+1,i)):
        #    keyboard[i-sqar-1][j+sqar-1]=1
        #    sqar=sqar+1
    #print(keyboard)
countn=0
"""
print(horizon)
print(vertical)
print(squarch)
print(duijich)
"""
for i in range(n):
    for j in range(m):
        if(horizon[i]!=1 and vertical[j]!=1 and squarch[i-j]!=1 and duijich[i+j]!=1):
            #print("point",i,j)
            countn=countn+1
print(countn)
#print(keyboard)