#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main(){
    vector<int> progresses = {95, 90, 99 , 99, 80, 99};
    vector<int> speeds = {1, 1, 1, 1, 1};
    vector<int> time(progresses.size(), 0);
    vector<int> res;

    for(int i = 0 ; i < time.size() ; i++){
        time[i] = (100 - progresses[i]) / speeds[i] + ((100 - progresses[i]) % speeds[i] != 0);
    }
    queue<int> q;
    q.push(1);
    for(int i = 1 ; i < time.size() ; i++){
        if(time[i-1] < time[i]){
            res.push_back(q.size());
            while(!q.empty()){q.pop();}
            q.push(1);
            // 다음 프로그램이 완성되는데 오래걸리므로 큐 초기화해야됨
        }else{
            q.push(1);
        }
    }
    if(!q.empty()){
        res.push_back(q.size());
    }
    for(int i = 0 ; i < res.size() ; i++){
        cout << res[i] << " ";
    }
    return 0;
}