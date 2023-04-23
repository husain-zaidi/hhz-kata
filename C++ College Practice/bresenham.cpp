#include <iostream>

using namespace std;

void bresenham(int x1, int y1, int x2, int y2, int width){
    int m = 2 * (y2 - y1);
    int slopeError = m - (x2 - x1);
    for(int x = x1, y = y1; x <= x2; x++){
        cout << "(" << x << "," << y << ")" << endl;

        for(int i = 1, modify = 0; i <= width-1; i++){
            if(i%2 != 0){
                modify++;
                
            }
            if(i%2 != 0)
                cout << "(" << x+modify << "," << y << ")" << endl;
            else
                cout << "(" << x-modify << "," << y << ")" << endl;
        }
        slopeError += m;
        
        if(slopeError >= 0){
            y++;
            slopeError -= 2*(x2 - x1);
        }
    }
}

int main(int argc, char const *argv[])
{
    int x1 = 0, y1 = 0, x2 = 4, y2 = 4;
    bresenham(x1, y1, x2, y2,3);
    return 0;
}
