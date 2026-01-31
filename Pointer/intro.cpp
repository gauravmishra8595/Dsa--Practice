#include<iostream>
using namespace std;
int main(){
    // int num=5;
    // cout<<num<<endl;
    // cout<<"address of num is:"<< &num <<endl;
    // int *ptr=&num;
    // cout<<"Value is :"<<*ptr<<endl;

    // double d =4.3;
    // double *p2=&d;
    // cout<<"address is:"<<p2<<endl;
    // cout<<"value is:"<<*p2<<endl;
    // int i= 5;
    // int *q=&i;
    // cout<<q<<endl;
    // cout<<*q<<endl;
    // int *p=0;
    // p=&i;
    //   cout<<p<<endl;
    // cout<<*p<<endl;
    int num=5;
    int a=num;
    cout<<" a before "<<num<<endl;
    a++;
     cout<<"a after"<<num<<endl;
    cout<<num<<endl;
    int *p=&num;
    cout<<"before "<<num<<endl;
    (*p)++;
    cout<<"after"<<num<<endl;

    int *q=p;
    cout<<p<<"-"<<q<<endl;
    cout<<*q<<"-"<<*q<<endl;

    int i=3;
    int *t=&i;
    // cout<<(*t)++<<endl;
    *t=*t +1;
    cout<<*t<<endl;
    cout<<"before t"<<t<<endl;
    t=t+1;
      cout<<"after t"<<t<<endl;
    return 0;
}