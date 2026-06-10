#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

int main(){
    vector<string> cards1 = {"i", "water", "drink"};
    vector<string> cards2 = {"want", "to"};
    vector<string> goal = {"i", "want", "to", "drink", "water"};

    bool res = true;
    queue<string> q1;
    queue<string> q2;
    queue<string> g;
    for(int i = 0 ; i < cards1.size() ; i++){
        q1.push(cards1[i]);
    }
    for(int i = 0 ; i < cards2.size() ; i++){
        q2.push(cards2[i]);
    }
    for(int i = 0 ; i < goal.size() ; i++){
        g.push(goal[i]);
    }
    for(int i = 0 ; i < goal.size() ; i++){
        auto tmp = g.front();
        if(tmp != q1.front() && tmp != q2.front()){
            res = false;
            break;
        }else{
            g.pop();
            if(tmp == q1.front())   q1.pop();
            else                    q2.pop();
        }
    }
    cout << (res ? string("true") : string("false"));


}