from itertools import groupby
import json
str_in = input()
#print(str_in)
num =list(map(int, str_in.strip().split()))
n=num[0]
m=num[1]
x=[]
for i in range(n):
    num_temp = input()
    x.append(int(num_temp))
#numcount=0
result=0
flag=0
def get_all_substrings_1(input_string):
  length = len(input_string)
  return [input_string[i:j + 1] for i in range(length) for j in range(i,length)]
lis=get_all_substrings_1(x)
longeststr=[]
lent=0
ans=0
def finalfunc(lis,longeststr,lent,x):
    for substrs in (lis):
        if(abs(substrs.count(2)-substrs.count(1))<=m or substrs.count(1)==0 or substrs.count(2)==0):
            if(lent<len(substrs)):
                longeststr=substrs
                lent=len(substrs)
    x="".join([str(i) for i in x])
    longeststr="".join([str(i) for i in longeststr])
    #print("longeststr is",longeststr)
    global ans
    ans += 1
    stratlocat=x.find(longeststr)
    leftslice=x[:stratlocat]
    rightslice=x[stratlocat+lent:]
    lisf=get_all_substrings_1(list(leftslice))
    lisr=get_all_substrings_1(list(rightslice))
    longeststr = []
    lent=0
    if(leftslice.isdigit()==False and rightslice.isdigit()==False):
        return
    if(leftslice.isdigit()):
        finalfunc(lisf,longeststr,lent,list(leftslice))
    if(rightslice.isdigit()):
        finalfunc(lisr,longeststr,lent,list(rightslice))
if(m==0):
    finalfunc(list(lis),longeststr,lent,x)
    print(ans)
    exit()
"""if (m==0):
    length = len(x)
    final_dic=[x[i:j + 1] for i in range(length) for j in range(i, length)]
    #print(final_dic)
    for elem in final_dic:
        if(elem.count(2)==elem.count(1)):
            xstr=str(x)
            xstr1=""
            for i in range(len(xstr)):
                if(xstr[i]!=',' and xstr[i] !='[' and xstr[i]!=']' ):
                    xstr1+=xstr[i]
            print(xstr1)
            elemstr = str(elem)
            elemstr1 = ""
            for i in range(len(elemstr)):
                if (elemstr[i] != ',' and elemstr[i] != '[' and elemstr[i] != ']'):
                    elemstr1 += elemstr[i]
            print(elemstr1)
            start=xstr1.index(elemstr1)
            for i in range(len(elemstr1)):
                x[i+start]=0
    cutted = [cutted[0] for cutted in groupby(x)]
    print(cutted)
    exit()
"""
def func(x):
    togglepoint = 0
    numof2 = 0
    numof1 = 0
    global result
    for i in range(len(x)):
        #print(togglepoint)
        if (x[i] == 1):
            numof1+=1
        if(x[i]==2):
            numof2+=1
        if (abs(numof1-numof2) > m and numof1!=0 and numof2!=0):
            if(togglepoint==0):
                togglepoint=int(i)
            else:
                continue
        else:
            togglepoint=0
    if(togglepoint):
        nextinput=x[togglepoint:]
    else:
        nextinput=[]
        result+=1
    #print(nextinput)
    if(nextinput.count(2)==0 and nextinput.count(1)==0):
        print(result)
    else:
        result+=1
        func(nextinput)
func(x)
