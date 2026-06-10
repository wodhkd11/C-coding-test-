#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main(){
    vector<int> prices = {1,2,3,2,3};
    vector<int> res(prices.size(), 0);
    stack<int> st;
    for (int i = 0 ; i < prices.size(); i ++) {
        while(!st.empty() && prices[st.top()] > prices[i]){
            int tmp = st.top();
            st.pop();
            res[tmp] = i - tmp;
        }
        st.push(i);
    }
    while(!st.empty()){
        res[st.top()] = prices.size() - st.top() - 1;
        st.pop();
    }
    for (int i = 0 ; i < res.size() ; i++){
        cout << res[i];
    }
    return 0;
}