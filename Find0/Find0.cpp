#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <windows.h>
#include <conio.h>
using namespace std;
//
bool Win();
void exit();
//
#define win Win()
#define w 20
#define h 20
#define maxBarries 50 
//
std::string matrix[h][w];
int x=1;
int y=1;
int winX = 5;
int winY = 8;

template <typename T>
void print(T s){
    std::cout << s;
}

template <typename T>
void print(T s,int n){
    for(int i=0;i<n;i++)
        std::cout << s;
}

void display(){
    print("\n",30);
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            print(matrix[i][j]);
            if(j==w-1) std::cout<<std::endl;
        }
    }
}

void wall(){
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            matrix[i][j] = "  ";
            matrix[0][j] = "# ";
            matrix[i][0] = "# ";
            matrix[h-1][j] = "# ";
            matrix[i][w-1] = "# ";
        }
    }
}

void barriers(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution rh(1,h-2);
    std::uniform_int_distribution rw(1,w-2);
    for(int i=0;i<maxBarries;i++){
        matrix[rh(gen)][rw(gen)] = "# ";
    }

    int randX = rw(gen);
    int randY = rh(gen);
    if(randX == x && randY == y){

    }else{
        winX = randX;
        winY = randY;
    }
}

void startAndEnd(){
    matrix[1][1] = "1 ";
    matrix[winY][winX] = "0 ";
}

void init(){
    wall();
    barriers();
    startAndEnd();
}

void left(){
    if(x > 1 && matrix[y][x-1] != "# "){
        swap(matrix[y][x-1],matrix[y][x]);
        x--;
        if(win) {
            matrix[y][x+1] = "1 ";
            display();
            exit();
        }
        display();
    }
}
void right(){
    if(x < w-2 && matrix[y][x+1] != "# "){
        swap(matrix[y][x+1],matrix[y][x]);
        x++;
        if(win) {
            matrix[y][x-1] = "1 ";
            display();
            exit();
        }
        display();
    }
}
void up(){
    if(y > 1 && matrix[y-1][x] != "# "){
        swap(matrix[y-1][x],matrix[y][x]);
        y--;
        if(win) {
            matrix[y+1][x] = "1 ";
            display();
            exit();
        }
        display();
    }
}
void down(){
    if(y < h-2 && matrix[y+1][x] != "# "){
        swap(matrix[y+1][x],matrix[y][x]);
        y++;
        if(win) {
            matrix[y-1][x] = "1 ";
            display();
            exit();
        }
        display();
    }
}

void keyboardThread(){
    while (1){
        if (_kbhit()){
            char ch = _getch();
            if (ch == 27){ break; }
            switch(ch){
                case 'A' :case  'a': left();break; 
                case 'D' :case  'd': right();break; 
                case 'W' :case  'w': up();break; 
                case 'S' :case  's': down();break; 
            }
        }
    }
}

bool Win(){
    if(x == winX && y == winY) return true;
    return false;
}

void exit(){
    print("\n",3);
    print(
"   *     *     *   * * *   *     *\n"
"    *   * *   *      *     * *   *\n"
"     * *   * *       *     *   * *\n"
"      *     *      * * *   *     *\n\n");
    print("Thanks, no balls man has been straightened!");
    print("\n",3);
    exit(0);
}


int main(){
    init();
    display();
    std::thread t(std::bind(keyboardThread));
    t.join();
    return 0;
}
