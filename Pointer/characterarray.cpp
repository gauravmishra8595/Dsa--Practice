#include<iostream>
using namespace std;
int main(){
    int arr[5]={1,2,3,4,5};
    char ch[6]="Dubey";
    cout<<arr<<endl;
    cout<<ch<<endl;

    char *c=&ch[0];
    cout<<&ch[0]<<endl;
}