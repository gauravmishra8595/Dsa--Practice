#include<iostream>
using namespace std;

class hero
{
private:
    int health;
public:
    char level;
    void print(){
        cout<<level<<endl;
    }
    int gethealth(){
        return health;
    }
    char getLevel(){
        return level;   
    }
    void SetHealth(int h){
        health= h;
    }
    void SetLevel(char ch){
        level= ch;
    }
};

int main(){
    hero Dubey;
    cout<<"size of Dubey is:"<<sizeof(Dubey)<<endl;
    cout<<"Dubey health is"<<Dubey.gethealth()<<endl;
    Dubey.SetHealth(100);
    Dubey.level='A';

    cout<<"health is:"<<Dubey.gethealth()<<endl;
    cout<<"Level is:"<<Dubey.level<<endl;
    
}

//static allocation
// hero a;
// a.setHeath();
// a.setlevel();
//  cout<<"size of a is:"<<sizeof(a)<<endl;
//     cout<<"a health is"<<a.gethealth()<<endl;

// dynamic allocation
//  hero *b=new hero;
//b->setlevel('A);
//b->sethealth(70);
//  cout<<"size of a is:"<<sizeof(*b)<<endl;
//cout<<"a health is"<<(*b).gethealth()<<endl;
