#include<iostream>
#include<queue>
using namespace std;
 int main(){
    queue<string> q;
     q.push("Ayushi");
    q.push("Gaurav");
    q.push("Dubey");
    cout<<"Size before pop"<<q.size()<<endl;
    cout<<"First Element"<<q.front()<<endl;
    q.pop();
    cout<<"size after pop"<<q.size()<<endl;
    cout<<"first element"<<q.front()<<endl;
}