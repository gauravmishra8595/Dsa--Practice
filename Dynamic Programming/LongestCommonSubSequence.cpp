#include<iostream>
using namespace std;

class Solution{
    public:
    int solve(int n, int a[], int curr,int prev){
        if (curr==n)
        {
            return 0;
        }
        int take=0;
        if (prev=-1||a[curr]>a[prev])
        {
            take=1+solve(n, a, curr+1,curr);
        }
        
        int notTAke=0+solve(n,a,curr+1,prev);
        return max(take,notTAke);
    }

    int longestSubsequence(int n, int a[]){
        return solve(0,a,0,-1);
    }
};