#include<iostream>
using namespace std;
int main(){
    // int n;
    // cout<<"Enter value of n:"<<endl;
    // cin>>n;
    // int i=1;
    // while (i<=n)
    // {
    //  int j= 1;
    //  while (j<=n)
    //  {
    //     cout<<n-j+1;
    //     j=j+1;
    //  }
    //  cout<<endl;
    //  i =i+1;
    // }
    int n;
    cout<<"enter value of n:"<<endl;
    cin>>n;
    // int i=1;
    // int count =1;
    // while (i<=n)
    // {
    //     int j=1;
    //     while (j<=n)
    //     {
    //        cout<<count<<" ";
    //        count=count+1;
    //        j=j+1;
    //     }
    //     cout<<endl;
    //     i=i+1;
    // }
//     int row=1;
//     while(row<=n){
//         int col = 1;
//         while (col<=row)
//         {
//             cout<<"*";
//             col= col+1;
//         }
//         cout<<endl;
//         row=row+1;
//     }
// int row=1;
// while (row<=n)
// {
//     int col =1;
//     while (col<=n)
//     {
//         char ch ='A' + row - 1;
//         cout<< ch;
//         col =col+1;
//     }
//     cout<<endl;
//     row=row+1;    
// }
//     int row=1;
// while (row<=n)
// {
//     int col =1;
//     while (col<=n)
//     {
//         char ch ='A' + col- row;
//         cout<< ch;
//         col =col+1;
//     }
//     cout<<endl;
//     row=row+1;    
// }

//   int row=1;
// while (row<=n)
// {
//     int col =1;
//     while (col<=n)
//     {
//         char ch ='A' + col+ row-2;
//         cout<< ch;
//         col =col+1;
//     }
//     cout<<endl;
//     row=row+1;    
// }
int row =1;
while (row<=n)
{
    int space= n- row;
    while (space)
    {
        cout<<" ";
        space = space -1;
    }
    int col= 1;
    while (col<=row)
    {
        cout<<"*";
        col=col+1;
    }
    cout<<endl;
    row=row+1;

}


}