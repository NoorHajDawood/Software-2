#ifndef _date_h
#define _date_h
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
enum Result {Success, Fail};

class Date
{
private:
    int day;
    string month;
    int year;
public:
    Result dateCreate(int day, int month, int year);
    void dateDestroy();
    Result dateRead(istream &ifd);
    Result datePrint(ostream &ofd);
    int dateMonth();
    int dateDiff(Date *date);
};
#endif