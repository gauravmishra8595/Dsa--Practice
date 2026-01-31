#include<iostream>
#include<stack>
#include<queue>
using namespace std;

queue<int> rev(queue<int> q){
    stack<int> s;
    while (!q.empty())
    {
        int elemenmt=q.front();
        q.pop();
        s.push(elemenmt);
    }
    while (!s.empty())
    {
        int element=s.top();
        s.pop();
        q.push(element);
    }
    
}