#include<iostream>
#include <algorithm>
#include<vector>
using namespace std;

class Solution{
    public:
    static bool cmp(pair<int,int> a, pair<int,int>b){
        return a.second <b.second;
    }
    int MaxMeetings(int start[],int end[],int n){
        vector<pair<int,int>>v;
        for (int i = 0; i < n; i++)
        {
            pair<int,int> p = make_pair(start[i],end[i]);
            v.push_back(p);
        }
        sort(v.begin(),v.end(),cmp);
        
        int count=1;
        int ansEnd=v[0].second;

        for (int i = 0; i < n; i++)
        {
            if (v[i].first>ansEnd)
            {
                count++;;
                ansEnd=v[i].second;
            }
            
        }
        return count;
    }

};