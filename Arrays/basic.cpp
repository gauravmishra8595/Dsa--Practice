#include<iostream>
using namespace std;
int main(){
    int number[15];
    cout<<"Value at 10 index"<<number[9]<<endl;
    cout<<endl<<"everything is fine"<<endl<<endl;

    int third[15]={1,3};
    int n =15;
    cout<<"printing the array"<<endl;
    for(int i=0; i<n;i++){
        cout<<third[i]<<" ";
    }

     int fourth[10]={0};
    n =10;
    cout<<"printing the array"<<endl;
    for(int i=0; i<n;i++){
        cout<<fourth[i]<<" ";
    }
     int fifth[11]={1};
    n =11;
    cout<<"printing the array"<<endl;
    for(int i=0; i<n;i++){
        cout<<fifth[i]<<" ";
    }
    return 0;
}