
#include <iostream>
#include <queue>

using namespace std;

int main(){
    int N = 5;
    int K = 3;
    queue<int> q;
    for (int i = 1 ; i <= N ; i++){
        q.push(i);
    }
    while(q.size() != 1){
        for(int i = 0 ; i < K ; i++){
            if (i == K-1){
                q.pop();
            } else{
                q.push(q.front());
                q.pop();
            }
        }
    }
    cout << q.front() << endl;
    return 0;
}