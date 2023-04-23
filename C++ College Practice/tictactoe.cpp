#include <iostream>

using namespace std;

char map[3][3] = {{' ',' ','x'},
                  {' ',' ','x'},
                  {' ',' ','x'}};

void check(int i, int j, int c){
    c++;
    if(map[i][j] != 'x'){
        c = 0;
        return;
    }
    if(c == 2){
        cout << "x wins" << endl;
        return;
    }
    check(i,j+1,c);
    check(i+1,j,c);
    check(i+1,j+1,c);
}

int main(int argc, char const *argv[])
{
    for(int i = 0; i < 3; i++){
        if(i == 0){
            for(int j = 0; j < 3; j++)
                check(i,j,0);
        }else {
            check(i,0,0);
        }

    }
    return 0;
}
