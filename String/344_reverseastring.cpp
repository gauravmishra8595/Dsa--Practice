// #include<iostream>
// using namespace std;

// void reverse(char name[],int n){
//     int s=0;
//     int e=n-1;
//     while (s<e)
//     {
//         swap(name[s++],name[e--]);
//     }
    
// }

// int getlength(char name[]){
//     int count=0;
//     for (int i = 0; name[i]!='\0'; i++)
//     {
//         count++;
//     }
//     return count;
// }
// int main(){
//     char name[20];
//     cout<<"Enter your name"<<endl;
//     cin>>name;
//     cout<<"Your name is:";
//     cout<<name<<endl;
//     int len=getlength(name);
//     cout<<"Length:"<<len<<endl;
//     reverse(name,len);
//     cout<<"your name is:";
//     cout<<name<<endl;


//     return 0;
// }

// another method
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size() - 1;
        
        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }
};

int main() {
    Solution sol;

    vector<char> s = {'h', 'e', 'l', 'l', 'o'};

    sol.reverseString(s);

    cout << "Reversed string: ";
    for (char c : s) {
        cout << c << " ";
    }

    return 0;
}