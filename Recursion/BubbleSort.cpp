#include <iostream>
using namespace std;
void sortarry(int *arr, int n){

    if (n==0 || n==1)
    {
        return ; 
    }

    for (int  i = 0; i < n-1; i++)
    {
        if (arr[i]>arr[i+1])
        {
            swap(arr[i],arr[i+1]);
        }
        
    }
    
     sortarry(arr, n-1);
}

int main(){
    int arr[5]={2,5,7,12,3};
    sortarry(arr,5);
    for (int i = 0; i < 5; i++)
    {
        cout<<arr[i]<<" ";
    }
    

}