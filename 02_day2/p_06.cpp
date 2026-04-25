#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N = 5;
    vector<int> stages = {2, 1, 2, 6, 2, 4, 3, 3};

    vector<pair<float, int>> res;
    for (int i = 0 ; i < N ; i++){
        int low = 0;
        int cur = 0;
        int ovr = 0;
        for (int j : stages){
            if (j == i+1) cur++;
            if (j < i+1) low++;
            if (j > i+1) ovr++;
        }
        res.push_back({static_cast<float>(cur) / (cur + ovr), i+1});
    }
    sort(res.rbegin(), res.rend());
    for (pair<float, int> a : res){
        cout << a.second << ", ";
    }
    cout << endl;

    return 0;
}



//누적합으로 계산하는 것이 O(NlogN)으로 조금 더 깔끔한 시간복잡도가 나오게 됨
//지금의 경우, O(N*M)으로 높은 시간복잡도를 가짐.
