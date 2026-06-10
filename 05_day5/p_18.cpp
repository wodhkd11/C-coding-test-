#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main(){
    unordered_map<string, int> mp ;
    vector<string> participant = {"leo", "kiki", "eden"};
    vector<string> completion = {"eden", "kiki"};
    for(int i = 0 ; i < participant.size() ; i++){
        mp[participant[i]] ++;
    }
    for(int i = 0 ; i < completion.size() ; i++){
        mp[completion[i]] --;
    }
    for(int i = 0 ; i < participant.size() ; i++){
        if(mp[participant[i]]!= 0)  cout << participant[i] << endl;
    }
    return 0;
}