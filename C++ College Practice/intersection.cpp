#include <iostream>

using namespace std;
int width, height;
void print(int x, int y)
{
	if(x <= width && y <= height && x >= 0 && y >= 0)
		cout << "[" << x << " , " << y << "]" << endl;
	else
		cout << "out of bounds" << endl;
}

int main(int argc, char const *argv[])
{
	int m, c;
	
	cout << "Enter the lines of rectangle (width,height)" << endl;
	cin >> width >> height;
	cout << "Enter the slope & constant of the line" << endl;
	cin >> m >> c;
	int intersect1 = (m*0)+c;
	cout << "Intersection with left side "<< endl;
	print(0,intersect1);
	int intersect2 = (m*width)+c;
	cout << "Intersection with right side " << endl;
	print(width,intersect2);
	int intersect3 = (m == 0) ? c:(0-c)/m;
	cout << "Intersection with bottom side " << endl;
	print(intersect3,0);
	int intersect4 = (m == 0) ? c:(height-c)/m;
	cout << "Intersection with top side " << endl;
	print(intersect4,height);
	return 0;
}