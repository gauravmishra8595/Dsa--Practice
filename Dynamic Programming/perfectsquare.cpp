#include<iostream>
using namespace std;

class solution{
    public:
    int slove(int n){
        if (n==0)
        {
            return 0;
        }
        int ans=n;
        for (int i = 0; i < n; i++)
        {
            ans=min(ans,1+slove(n-i*i));
        }
        return ans;
    }

    int Minsquares(int n){
        return slove(n);
    }
};
