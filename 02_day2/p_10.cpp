#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool valdiator(string input) {
    stack<char> st;
    for (int i = 0 ; i < input.length() ; i++){
        if(input[i] == '['|| input[i] == '{' || input[i] == '('){
            st.push(input[i]);
        }else{
            if(st.empty()) return false;
            char top = st.top();
            st.pop();
            if(top + 1 == input[i] || top + 2 == input[i]){
                continue;
            }else {
                return false;
            }
        }
        
    }
    return true;
}

int main(){
    string input = "}]()[{";
    stack<char> st;
    int i = 0;
    int count = 0;
    for (i = 0 ; i < input.length() ; i++){
        if(valdiator(input)){
            count++;
        }
        rotate(input.begin(), input.begin() + 1, input.end());

    }
    cout << count << endl;
    return 0;
}