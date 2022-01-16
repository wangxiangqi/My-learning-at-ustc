/* product of wangxiangqi*/
/*
Nim is a 2-player game featuring several piles of stones.
 Players alternate turns, and on his/her turn, 
 a player¡¯s move consists of removing one or more stones from any single pile. 
 Play ends when all the stones have been removed,
 at which point the last player to have moved is declared the winner.
 Given a position in Nim, your task is to determine how many winning moves
  there are in that position.

A position in Nim is called ¡°losing¡± if the first player to move 
from that position would lose if both sides played perfectly. 
A ¡°winning move,¡± then, is a move that leaves the game in a losing position. 
There is a famous theorem that classifies all losing positions. 
Suppose a Nim position contains n piles having k1, k2, ¡­, kn stones respectively; 
in such a position, there are k1 + k2 + ¡­ + kn possible moves. We write each ki in binary (base 2). Then, the Nim position is losing if and only if, among all the ki¡¯s, there are an even number of 1¡¯s in each digit position. In other words, the Nim position is losing if and only if the xor of the ki¡¯s is 0.

Consider the position with three piles given by k1 = 7, k2 = 11, and k3 = 13.
 In binary, these values are as follows:
*/
/* POJ2975 ZOJ3067 Nim */

#include <iostream>
#include <cstdio>

using namespace std;

const int N = 1000;
int a[N];
//Bouton Theorem
int main()
{
    int n;
    while(~scanf("%d", &n) && n) {
        int sum = 0, cnt = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            sum ^= a[i];
        }

        for(int i = 0; i < n; i++)
            if((sum ^ a[i]) < a[i]) cnt++;

        printf("%d\n", cnt);
    }

    return 0;
}

