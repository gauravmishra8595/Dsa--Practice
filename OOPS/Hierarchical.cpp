#include <iostream>
using namespace std;
class A{
    public:
    void function1(){
        cout<<"Dubey"<<endl;
    }
};

class B: public A{
    public:
    void function2(){
        cout<<"Gaurav"<<endl;
    }
};
class C:public A{
    public:
    void function3(){
        cout<<"Gaurav Mishra and Ayushi Dubey"<<endl;
    }
};

 int main() {
    A object1;
    object1.function1();

    B object2;
    object2.function2();
    object2.function2();

    C object3;
    object3.function3();
    object3.function1();


    return 0;
}