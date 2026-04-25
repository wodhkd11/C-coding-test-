#include <iostream>
#include <stdlib.h>
#include <stack>

using namespace std;

int main(){
    stack<char> bin;
    int value = 27;
    if (value == 0) bin.push('0');
    while(value > 0){
        bin.push(static_cast<char>('0' + value % 2));
        value = value >> 1;
    }

    do{
        cout << bin.top();
        bin.pop();
    }while(!bin.empty());
    return 0;
}