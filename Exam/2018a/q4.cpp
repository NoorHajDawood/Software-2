#include <iostream>
using namespace std;
void swap(float &x, float &y){
    float t = x;
    x = y;
    y = t;
}
int main(int argc, char const *argv[])
{
    float x = 7.5, y = 12.5;
    swap(x,y);
    cout << x << " " << y;
    return 0;
}
