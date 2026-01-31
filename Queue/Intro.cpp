#include<iostream>
#include<queue>
using namespace std;
int main(){
    deque<int> d;
     d.push_front(29);
    d.push_back(49);
    cout<<d.front()<<endl;
    cout<<d.back()<<endl;

    d.pop_front();
    d.pop_back();
    if (d.empty())
    {
        cout<<"d is empty"<<endl;
    }else{
        cout<<"d is not empty"<<endl;
    }
    
    queue<int> q;
    q.push(29);
    q.push(30);
    q.push(45);
    cout<<"the size of queue: "<<q.size()<<endl;
    q.pop();
    cout<<"the font of Queue:"<<q.front()<<endl;
    q.pop();
    q.pop();

    cout<<"the size of queue:"<<q.size()<<endl;

    if (q.empty())
    {
        cout<<"queue is empty"<<endl;
    }else{
        cout<<"queue is not empty"<<endl;
    }
    


}