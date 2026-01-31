#include<iostream>
#include<vector>
using namespace std;

int solveMem(vector<int>&weight, vector<int>&value,int index , int capacity,vector<vector<int>>&dp){
    if (index==0)
    {
        if (weight[0]<=capacity)
        {
            return  value[0];
        }else{
            return 0;
        }
    }
    if (dp[index][capacity]!=1)
    {
        return dp[index][capacity];
    }
    

    int include=0;
    if (weight[index]<=capacity)
    {
        include=value[index]+solveMem(weight,value,index-1,capacity-weight[index],dp);
    }
    
    int exclude= 0+solveMem(weight,value,index-1,capacity,dp);

    dp[index][capacity] = max(exclude,include);
    return dp[index][capacity];
};

int knapsnack(vector<int>weight, vector<int>value,int n , int maxWeight){
   vector<vector<int> > dp(n,vector<int>(maxWeight+1,-1));
    return solveMem(weight,value,n-1, maxWeight,dp);
};


// int solve(vector<int>&weight, vector<int>&value,int index , int capacity){
//     if (index==0)
//     {
//         if (weight[0]<=capacity)
//         {
//             return  value[0];
//         }else{
//             return 0;
//         }
//     }
//     int include=0;
//     if (weight[index]<=capacity)
//     {
//         include=value[index]+solve(weight,value,index-1,capacity-weight[index]);
//     }
    
//     int exclude= 0+solve(weight,value,index-1,capacity);

//     int ans = max(exclude,include);
//     return ans;
// };

// int knapsnack(vector<int>weight, vector<int>value,int n , int maxWeight){
//     return solve(weight,value,n-1,maxWeight);
// };

int main() {
    cout << "Knapsack DP working!" << endl;
    return 0;
}