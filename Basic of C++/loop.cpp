#include<iostream>
using namespace std;

// int main(){
//     int n;
//     cin>>n;
//     int i= 1;
//     int sum =0;
//     while(i<=n){
//         sum=sum+i;
//         i=i+1;
//     }
//     cout<<"value of sum is:"<<sum<<endl;
// }

int main(){
    // int n;
    // cin>>n;
    // int i=2;
    // while(i<n){
    //     if(n%i==0){
    //         cout<<"not a prime"<<endl;
    //     }
    //     i=i+1;
    // }
    int  n =10;
    int a =0;
    int b=1;
    for (int i = 0; i <= n; i++)
    {
        int nextNumber = a+b;
        cout<<nextNumber<<" ";
        a=b;
        b=nextNumber;
    }
    
}