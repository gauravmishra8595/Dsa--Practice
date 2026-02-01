#include <iostream>
#include <algorithm>
#include <limits.h>
#include<vector>
using namespace std;

class solution{
    public:
    long long findMinDiff(vector<long long> a,long long n, long long m){
        sort(a.begin(),a.end());
        int j=m-1;
        int i= 0;
        int mini=INT32_MAX;
        while (j<a.size())
        {
            int diff =a[j]-a[i];
            mini=min(mini,diff);
            i++;
            j++;
        }
        return mini;
    }

};