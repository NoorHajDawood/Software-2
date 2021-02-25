#include <cstddef>
#include <string>
#include "date.h"
static const string months[]={"JAN","FEB","MAR","APR","MAY","JUN", "JUL","AUG", "SEP", "OCT", "NOV", "DEC"}; 
Result Date::dateCreate(int day, int month, int year)
{
    if (day < 1 || day > 31 || month < 1 || month > 12)
        return Fail;
    this->day = day;
    this->month=months[month - 1];
    this->year = year;
    return Success;
}

void Date::dateDestroy()
{
}
Result Date::dateRead(istream &ifd)
{
    ifd >> day >> month >> year;
    if (day < 1 || 31 < day || dateMonth() == -1)
        return Fail;
    return Success;
}
Result Date::datePrint(ostream &ofd)
{
    ofd << day << " " << month << " " << year;
    return Success;
}
int Date::dateMonth()
{
    int j = 0;
    for (j = 0; j < 12; j++)
        if (month.compare(months[j]) == 0)
            return j + 1;
    return -1;
}
int Date::dateDiff(Date *date)
{
    int da, db, diff;
    da = dateMonth();
    db = date->dateMonth();
    if (da == -1 || db == -1)
        return -1;
    da = day + 30 * da + 365 * year;
    db = date->day + 30 * db + 365 * date->year;
    diff = da - db;
    return ((diff < 0) ? -diff : diff);
}