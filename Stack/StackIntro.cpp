#include<iostream>
#include <stack>
using namespace std;

class Stack{
    public:
    int *arr;
    int size;
    int top;

    Stack(int size){
        this->size=size;
        arr=new int[size];
        top=-1;
    }

    void push(int element){
        if (size-top>1)
        {
            top++;
            arr[top]=element;
        }else{
            cout<<"stack Overflow"<<endl;
        }

    }

    void pop(){
        if (top>=0)
        {
            top--;
        }else{
            cout<<"Stack underflow"<<endl;
        }
    }

    int peek(){
        if (top>=0 )
        {
            return arr[top];
        }else{
            cout<<"Stack is empty"<<endl;
            return -1;
        }
    }

    bool isEmpty(){
        if (top==-1)
        {
            return true;
        }else{
            return false;
        }
        
    }

};

int main(){

    Stack st(5);

    st.push(22);
    st.push(23);
    st.push(29);
    st.push(29);
    st.push(79);
    st.push(69);
    st.push(49);
    
    cout<<st.peek()<<endl;
    st.pop();

     cout<<st.peek()<<endl;

    st.pop();
      cout<<st.peek()<<endl;

    st.pop();

    
     cout<<st.peek()<<endl;
 
    if (st.isEmpty())
    {
        cout<<"kuch nahi hai "<<endl;
    }else{
        cout<<"kuch to hai"<<endl;
    }
    






    // stack<int> s;
    // // s.push(29);
    // // s.push(49);
    // // s.push(50);


    // // s.pop();
    // // cout<<"printing element of sack:"<<s.top()<<endl;

    // // if (s.empty())
    // // {
    // //     cout<<"stack is empty"<<endl;
    // // }else{
    // //     cout<<"stack is not emnpty"<<endl;
    // // }
    
    // // cout<<"size of stack:"<<s.size()<<endl;

}
