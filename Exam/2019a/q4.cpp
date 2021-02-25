#include <iostream>
#include <fstream>
#include "date.h"
using namespace std;
int main(int argc, char const *argv[])
{
    Date d1, d2;
    if ((d1.dateCreate(1, 1, 1) == Fail) || (d2.dateCreate(1, 1, 1) == Fail))
        return 1;
    if (d1.dateRead(cin) == Fail || d2.dateRead(cin) == Fail)
        return 1;
    cout << "The month of ";
    d1.datePrint(cout);
    cout << " is %d\n" << d1.dateMonth();
    printf("The difference between ");
    d1.datePrint(cout);
    cout << " and ";
    d2.datePrint(cout);
    cout << " is %d\n"<< d1.dateDiff(&d2);
    d1.dateDestroy();
    d2.dateDestroy();
    return 0;
}
