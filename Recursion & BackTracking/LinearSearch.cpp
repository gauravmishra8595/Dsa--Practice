#include<iostream>
using namespace std;
bool LinearSearch(int arr[],int size, int k){
    if (size==0)
    {
        return false;
    }
    if (arr[0]==k)
    {
        return true;
    } else{
        bool remainingPart=LinearSearch(arr+1,size-1,k);
        return remainingPart;
    }
}
int main(){
    int arr[5]={23,24,12,29,35};
    int size=5;
    int key=29;
    bool ans=LinearSearch(arr,size,key);

    if(ans){
        cout<<"Present"<<endl;
    }else{
        cout<<"Not present"<<endl;
    }
    return 0;

}