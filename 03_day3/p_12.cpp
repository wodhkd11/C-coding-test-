#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main(){
    vector<int> prices = {1,2,3,2,3};
    vector<int> res(prices.size(), 0);
    stack<pair<int, int>> st;
    for (int i = 0 ; i < prices.size() ; i++){
        if(i == 0 || st.top().second <= prices[i]){
            st.push({i, prices[i]});
        }else{
            int count = 1;
            while(!st.empty()){
                auto temp = st.top();
                res[temp.first] = count;
                st.pop();
                count++;
            }
        }
    }
    for (int i = 0 ; i < res.size(); i++){
        cout << res[i] << " " << endl;
    }
    return 0;
}