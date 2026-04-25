#include <iostream>
#include <string>

using namespace std;
bool map[21][21] {false, };
int cur_x = 10; //11번째 칸
int cur_y = 10;

void move_position(char mv) {
    if (mv == 'U' && cur_y != 20){
        map[cur_x][cur_y+1]= true;
        cur_y += 2;
    }else if (mv == 'D' && cur_y != 0){
        map[cur_x][cur_y-1]= true;
        cur_y -= 2;
    }else if (mv == 'L' && cur_x != 0){
        map[cur_x-1][cur_y]= true;
        cur_x -= 2;
    }else if (mv == 'R' && cur_x != 20){
        map[cur_x+1][cur_y]= true;
        cur_x += 2;
    }
}

int main(){
    string str = "LULLLLLU";
    int count = 0;
    for(int i = 0 ; i < str.length() ; i++){
        move_position(str[i]);
    }
    for(int i = 1 ; i < 40 ; i+= 2){
        for(int j = 0 ; j <= i && j < 21 && i-j < 21 ; j++){
            if(map[j][i-j] == true)     count++;
        }
    }
    cout << count << endl;
    return 0;
}