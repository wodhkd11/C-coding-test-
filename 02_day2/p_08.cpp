#include <iostream>

using namespace std;

int main(){
    string input = "((())(()";
    stack<char> st;
    bool result = true;
    
    for (int i = 0 ; i < input.length() ; i++){
        if(input[i] == '('){
            st.push(input[i]);
        }else if(input[i] == ')'){
            if(st.empty() == true)  result = false;
            else    st.pop();
        }
    }
    if(st.empty() == false) result = false;
    cout << result << endl;
    return 0;
}