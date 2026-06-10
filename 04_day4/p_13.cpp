#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main(){
    vector<vector<int>> board = {{0,0,0,0,0}, {0,0,1,0,3}, {0,2,5,0,1}, {4,2,4,4,2}, {3,5,1,3,1}};
    vector<int> moves = {1,5,3,5,1,2,1,4};
    int res;
    int count = 0;
    stack<int> st;

    vector<int> in;
    for (int i = 0 ; i < moves.size(); i++){
        for(int y = 0 ; y < board.size() ; y++){
            if(board[y][moves[i]-1] != 0){
                in.push_back(board[y][moves[i]-1]);
                break;
            }
        }
    }
    for (int i = 0 ; i < in.size() ; i++){
        if(!st.empty() && st.top() == in[i]){
            count += 2;
            st.pop();
        }else { st.push(in[i]); }
    } 
    cout << count << endl;
    return 0;
}