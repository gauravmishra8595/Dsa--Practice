#include<iostream>
#include <vector>
#include<limits.h>
using namespace std;


// int solve(int n, int x, int y, int z){
//     if (n==0)
//     {
//         return 0;
//     }
//     if (n<0)
//     {
//         return INT16_MIN;
//     }
    

//     int a =solve(n-x, x,y,z)+1;
//     int b =solve(n-y, x,y,z)+1;
//     int c =solve(n-z, x,y,z)+1;

//     int ans= max(a, max(b,c));
    
//     return ans;
// };

// int cutsegments(int n, int x, int y,int z ){
//     int ans=solve(n,x,y,z);
//     if (ans<0)
//     {
//         return 0;
//     }else{
//         return ans;
//     }
    
// }

int solveMem(int n, int x, int y, int z,vector<int>& dp){
    if (n==0)
    {
        return 0;
    }
    if (n<0)
    {
        return INT32_MIN;
    }

    if (dp[n]!=-1)
    {
        return dp[n];
    }
    
    

    int a =solveMem(n-x, x,y,z,dp)+1;
    int b =solveMem(n-y, x,y,z,dp)+1;
    int c =solveMem(n-z, x,y,z,dp)+1;

    dp[n]= max(a, max(b,c));
    
    return dp[n];
};

int cutsegments(int n, int x, int y,int z ){
   vector<int> dp(n+1,-1);
   int ans=solveMem(n,x,y,z,dp);
   return ans;
    
}