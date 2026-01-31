#include <iostream>
using namespace std;
int binarySearch(int arr[], int size, int key){
    int start =0;
    int end= size-1;
    int mid = start+ (end-start)/2;
    while (start<=end)
    {
        if(arr[mid]==key){
            return mid;
        }
        if(key>arr[mid]){
            start =mid+1;
        }
        else{
            end= mid -1;
        }
        mid=start+ (end-start)/2;
    }
    return -1;
}

int main(){
    int even[10]={2,4,6,8,10,12,14,16,18,20};
    int odd[5]={3,6,9,12,15};
    int evenindex= binarySearch(even,10,18);
    int oddindex= binarySearch(odd,5,15);

    cout<<"Index of 18 is:"<< evenindex <<endl;
    cout<<"Index of 15 is:"<< oddindex <<endl;
    return 0; 

}