#pragma once
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int ReadYear()
{
    int year;
    cout << "Enter a year : ";
    cin >> year;
    return year;
}
int ReadMonth()
{
    int Month;
    cout << "Enter a Month : ";
    cin >> Month;
    return Month;
}
int ReadDay()
{
    int day;
    cout << "Enter a Day : ";
    cin >> day;
    return day;
}
bool IsLeapYear(int Year)
{

    if (Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0))
    {
        return true;
    }
    return false;
}

int NumberOfDaysInaYear(int Year)
{
    return IsLeapYear(Year) ? 366 : 365;
}

int NumberOfHoursInaYear(int Year)
{
    return NumberOfDaysInaYear(Year) * 24;
}
int NumberOfMinutsInaYear(int Year)
{

    return NumberOfHoursInaYear(Year) * 60;
}
long long NumberOfSecondsInaYear(int Year)
{

    return NumberOfMinutsInaYear(Year) * 60LL;
}
int NumberOfDaysInaMonth(int Year, int Month)
{
    if (Month < 1 || Month > 12)
    {
        return 0;
    }
    if (Month == 2)
    {
        return IsLeapYear(Year) ? 29 : 28;
    }
    else if (Month == 4 || Month == 6 || Month == 9 || Month == 11)
    {
        return 30;
    }
    else
    {
        return 31;
    }
}
int NumberOfHoursInaMonth(int Year, int Month)
{
    return NumberOfDaysInaMonth(Year, Month) * 24;
}
int NumberOfMinutesInaMonth(int Year, int Month)
{
    return NumberOfHoursInaMonth(Year, Month) * 60;
}
int NumberOfSecondsInaMonth(int Year, int Month)
{
    return NumberOfMinutesInaMonth(Year, Month) * 60;
}

int GetDayFromWeak(int Day, int Month, int Year)
{
    int a = ((14 - Month) / 12);
    int y = Year - a;
    int m = Month + (12 * a) - 2;
    int indexDay = (Day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;

    return indexDay;
}
string GetDayName(int GetDayFromWeak)
{
    string DayName[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return DayName[GetDayFromWeak];
}

void PrintMonthCalendar(int Y, int M)
{

    int FirstDay = GetDayFromWeak(1, M, Y); // 0 = Sunday
    int Days = NumberOfDaysInaMonth(Y, M);
    int counter = 1;

    string ArrMonth[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    cout << "________________" << ArrMonth[M - 1] << "_________________" << endl;
    cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if ((i == 0 && j < FirstDay) || counter > Days)
            {
                cout << setw(5) << " ";
            }
            else
            {
                cout << setw(5) << counter;
                counter++;
            }
        }
        cout << endl;
    }
}
void PrintMonthCalendarFromUser()
{
    int Y = ReadYear();
    int M = ReadMonth();
    PrintMonthCalendar(Y, M);
}
void PrintYearCalendar(int Year){
    for(int month=0;month<12;month++){
        PrintMonthCalendar(Year,month+1);
        
    }
}
int TotalDaysFromBeginingTheYear(int Day,int month,int Year){
    int TotalDays=0;
    int ArrNumberOfDaysForEachMonth[] = {
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31
};

if(IsLeapYear(Year)){
    ArrNumberOfDaysForEachMonth[1]=29;
}
for(int i=0;i<month-1;i++){
    TotalDays +=ArrNumberOfDaysForEachMonth[i];
}
TotalDays+=Day;
return TotalDays;
}
