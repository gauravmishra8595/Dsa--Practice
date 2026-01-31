#include<iostream>
#include<stack>
using namespace std;
int main(){
    stack<string>s;
    s.push("Ayushi");
    s.push("Gaurav");
    s.push("Dubey");
    cout<<"Top element:"<<s.top()<<endl;
    s.pop();
    cout<<"Top element:"<<s.size()<<endl;
    cout<<"Empty or not "<<s.empty()<<endl;
}