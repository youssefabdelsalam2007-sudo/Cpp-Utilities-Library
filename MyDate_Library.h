#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>
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

    while (Month > 12 || Month < 1)
    {
        cout << "enter a valid Month : ";
        cin >> Month;
    }

    return Month;
}
int ReadDay()
{
    int day;
    cout << "Enter a Day : ";
    cin >> day;
    while (day > 31 || day < 1)
    {
        cout << "enter a valid day :";
        cin >> day;
    }

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
int NumberOfDaysInaMonth_TheLastDayInMonth(int Year, int Month)
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
    return NumberOfDaysInaMonth_TheLastDayInMonth(Year, Month) * 24;
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
    int Days = NumberOfDaysInaMonth_TheLastDayInMonth(Y, M);
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
void PrintYearCalendar(int Year)
{
    for (int month = 0; month < 12; month++)
    {
        PrintMonthCalendar(Year, month + 1);
    }
}
int TotalDaysFromBeginingTheYear(int Day, int month, int Year)
{
    int TotalDays = 0;
    int ArrNumberOfDaysForEachMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31};

    if (IsLeapYear(Year))
    {
        ArrNumberOfDaysForEachMonth[1] = 29;
    }
    for (int i = 0; i < month - 1; i++)
    {
        TotalDays += ArrNumberOfDaysForEachMonth[i];
    }
    TotalDays += Day;
    return TotalDays;
}
void DateForADay(int day, int month, int year)
{
    int TotalDays = TotalDaysFromBeginingTheYear(day, month, year);
    cout << "Number of Days From the begining of the year is " << TotalDays << endl;
    cout << "Date for [ " << TotalDays << " ] is : " << day << '/' << month << '/' << year << endl;
}

bool IsTheEndDayInMonth(int Day, int Month, int Year)
{

    if (Month < 1 || Month > 12)
    {
        return 0;
    }

    if (Month == 2)
    {
        if ((IsLeapYear(Year) && Day == 29) || (IsLeapYear(Year) == 0 && Day == 28))
        {
            return true;
        }
    }
    else if ((Month == 4 || Month == 6 || Month == 9 || Month == 11) && Day == 30)
    {
        return true;
    }
    else if ((Month == 1 || Month == 3 || Month == 5 || Month == 7 || Month == 8 || Month == 10 || Month == 12) && Day == 31)
    {
        return true;
    }
    return false;
}

bool IsTheLastMonthInYear(int Month)
{
    return (Month == 12);
}

// Forward declaration: because the next function calls it before it is defined
void WhatIsTheNewDateIfSubtractedNumberOfDayes(int day, int month, int year, long long subtract);

void WhatIsTheNewDateIfAddedNumberOfDayes(int day, int month, int year, long long add)
{
    if (add < 0)
    {
        WhatIsTheNewDateIfSubtractedNumberOfDayes(day, month, year, -1 * add);
        return;
    }

    while (add != 0)
    {

        if (IsTheEndDayInMonth(day, month, year))
        {
            if (month == 12)
            {
                day = 1;
                month = 1;
                year++;
                add -= 1;
            }
            else
            {
                day = 1;
                month += 1;
                add -= 1;
            }
        }
        else
        {
            day++;
            add -= 1;
        }
    }
    cout << "NewDate is : " << day << '/' << month << '/' << year << endl;
}

void WhichDateIsHeighsitFirstApproach(int DayDate1, int MonthDate1, int YearDate1, int DayDate2, int MonthDate2, int YearDate2)
{
    if (YearDate1 > YearDate2)
    {
        cout << "The Date 1 is the Heighist : ";
    }
    else if (YearDate1 < YearDate2)
    {

        cout << "The Date 2 is the Heighist : ";
    }
    else
    {
        if (MonthDate1 > MonthDate2)
        {
            cout << "The Date 1 is the Heighist : ";
        }
        else if (MonthDate1 < MonthDate2)
        {
            cout << "The Date 2 is the Heighist : ";
        }
        else
        {
            if (DayDate1 > DayDate2)
            {
                cout << "The Date 1 is the Heighist : ";
            }
            else if (DayDate1 < DayDate2)
            {
                cout << "The Date 2 is the Heighist : ";
            }
            else
            {
                cout << "The two Dates is The same ";
            }
        }
    }
}

void WhichDateIsHeighsitSecondApproachUsingString(
    int DayDate1, int MonthDate1, int YearDate1,
    int DayDate2, int MonthDate2, int YearDate2)
{
    stringstream ss1, ss2;

    ss1 << YearDate1
        << setw(2) << setfill('0') << MonthDate1
        << setw(2) << setfill('0') << DayDate1;

    ss2 << YearDate2
        << setw(2) << setfill('0') << MonthDate2
        << setw(2) << setfill('0') << DayDate2;

    string Date1 = ss1.str();
    string Date2 = ss2.str();

    int IntDate1 = stoi(Date1);
    int IntDate2 = stoi(Date2);

    if (IntDate1 > IntDate2)
        cout << "The Date 1 is the Highest";

    else if (IntDate1 < IntDate2)
        cout << "The Date 2 is the Highest";

    else
        cout << "The two Dates are the same";
}
bool IsDate1BeforeDate2(int DayDate1, int MonthDate1, int YearDate1, int DayDate2, int MonthDate2, int YearDate2)
{
    if (YearDate1 != YearDate2)
    {
        return YearDate1 < YearDate2;
    }

    if (MonthDate1 != MonthDate2)
    {
        return MonthDate1 < MonthDate2;
    }

    return DayDate1 < DayDate2;
}
int TheDifferenceBetweenTwoDates(int DayDate1, int MonthDate1, int YearDate1, int DayDate2, int MonthDate2, int YearDate2)
{
    if (!IsDate1BeforeDate2(DayDate1, MonthDate1, YearDate1, DayDate2, MonthDate2, YearDate2))
    {
        return 0;
    }
    int Differnce = 0;
    while ((DayDate1 != DayDate2) || (MonthDate1 != MonthDate2) || (YearDate1 != YearDate2))
    {
        if (IsTheEndDayInMonth(DayDate1, MonthDate1, YearDate1))
        {
            if (IsTheLastMonthInYear(MonthDate1))
            {
                DayDate1 = 1;
                MonthDate1 = 1;
                YearDate1++;
                Differnce++;
            }

            else
            {
                DayDate1 = 1;
                MonthDate1++;
                Differnce++;
            }
        }
        else
        {
            DayDate1++;
            Differnce++;
        }
    }
    return Differnce;
}
int CalculateAgeInDays(int BirthDay, int BirthMonth, int BirthYear)
{
    time_t t = time(0);
    tm *CurrentDate = localtime(&t);

    int CurrentDay = CurrentDate->tm_mday;
    int CurrentMonth = CurrentDate->tm_mon + 1;
    int CurrentYear = CurrentDate->tm_year + 1900;

    return TheDifferenceBetweenTwoDates(
        BirthDay, BirthMonth, BirthYear,
        CurrentDay, CurrentMonth, CurrentYear);
}
int TheDifferenceBetweenTwoDatesSigned(
    int DayDate1, int MonthDate1, int YearDate1,
    int DayDate2, int MonthDate2, int YearDate2)
{
    if (IsDate1BeforeDate2(
            DayDate1, MonthDate1, YearDate1,
            DayDate2, MonthDate2, YearDate2))
    {
        return TheDifferenceBetweenTwoDates(
            DayDate1, MonthDate1, YearDate1,
            DayDate2, MonthDate2, YearDate2);
    }

    if (IsDate1BeforeDate2(
            DayDate2, MonthDate2, YearDate2,
            DayDate1, MonthDate1, YearDate1))
    {
        return -TheDifferenceBetweenTwoDates(
            DayDate2, MonthDate2, YearDate2,
            DayDate1, MonthDate1, YearDate1);
    }

    return 0;
}
void IncreaseDateByOneDay(int day, int month, int year)
{
    WhatIsTheNewDateIfAddedNumberOfDayes(day, month, year, 1);
}
void IncreaseDateDateByOneWeaks(int day, int month, int year)
{
    WhatIsTheNewDateIfAddedNumberOfDayes(day, month, year, 7);
}
void IncreaseDateDateByXweaks(int day, int month, int year, int weak)
{
    WhatIsTheNewDateIfAddedNumberOfDayes(day, month, year, 7 * weak);
}
void IncreaseDateDateByOneMonth(int day, int month, int year)
{
    WhatIsTheNewDateIfAddedNumberOfDayes(day, month, year, 30);
}
void IncreaseDateDateByXMonth(int day, int month, int year, int Month)
{
    WhatIsTheNewDateIfAddedNumberOfDayes(day, month, year, 30 * Month);
}
void IncreaseDateDateByOneYear(int day, int month, int year)
{
    WhatIsTheNewDateIfAddedNumberOfDayes(day, month, year, 365);
}

void IncreaseDateDateByXYear(int day, int month, int year, int Year)
{
    WhatIsTheNewDateIfAddedNumberOfDayes(day, month, year, 365 * Year);
}
void IncreaseDateByOneDecade(int day, int month, int year)
{
    WhatIsTheNewDateIfAddedNumberOfDayes(day, month, year, 10 * 365);
}
void IncreaseDateDateByXDecade(int day, int month, int year, int Deacde)
{
    WhatIsTheNewDateIfAddedNumberOfDayes(day, month, year, 10 * 365 * Deacde);
}
void IncreaseDateByOneCentury(int day, int month, int year)
{
    WhatIsTheNewDateIfAddedNumberOfDayes(day, month, year, 100 * 365);
}

void IncreaseDateByXCentury(int day, int month, int year, int Century)
{
    WhatIsTheNewDateIfAddedNumberOfDayes(day, month, year, 100 * 365 * Century);
}

void WhatIsTheNewDateIfSubtractedNumberOfDayes(int day, int month, int year, long long subtract)
{
    if (subtract < 0)
    {
        WhatIsTheNewDateIfAddedNumberOfDayes(day, month, year, -1 * subtract);
        return;
    }

    while (subtract != 0)
    {
        if (day == 1)
        {
            if (month == 1)
            {
                day = NumberOfDaysInaMonth_TheLastDayInMonth(year - 1, 12);
                month = 12;
                year -= 1;
                subtract -= 1;
            }
            else
            {
                day = NumberOfDaysInaMonth_TheLastDayInMonth(year, month - 1);
                month = month - 1;
                subtract -= 1;
            }
        }
        else
        {
            day -= 1;
            subtract -= 1;
        }
    }
    cout << "NewDate is : " << day << '/' << month << '/' << year << endl;
}

void DecreaseDateByOneDay(int day, int month, int year)
{
    WhatIsTheNewDateIfSubtractedNumberOfDayes(day, month, year, 1);
}

void DecreaseDateByOneWeek(int day, int month, int year)
{
    WhatIsTheNewDateIfSubtractedNumberOfDayes(day, month, year, 7);
}

void DecreaseDateByXWeeks(int day, int month, int year, int weeks)
{
    WhatIsTheNewDateIfSubtractedNumberOfDayes(day, month, year, 7 * weeks);
}

void DecreaseDateByOneMonth(int day, int month, int year)
{
    WhatIsTheNewDateIfSubtractedNumberOfDayes(day, month, year, 30);
}

void DecreaseDateByXMonths(int day, int month, int year, int months)
{
    WhatIsTheNewDateIfSubtractedNumberOfDayes(day, month, year, 30 * months);
}

void DecreaseDateByOneYear(int day, int month, int year)
{
    WhatIsTheNewDateIfSubtractedNumberOfDayes(day, month, year, 365);
}

void DecreaseDateByXYears(int day, int month, int year, int years)
{
    WhatIsTheNewDateIfSubtractedNumberOfDayes(day, month, year, 365 * years);
}

void DecreaseDateByOneDecade(int day, int month, int year)
{
    WhatIsTheNewDateIfSubtractedNumberOfDayes(day, month, year, 10 * 365);
}

void DecreaseDateByXDecades(int day, int month, int year, int decades)
{
    WhatIsTheNewDateIfSubtractedNumberOfDayes(day, month, year, 10 * 365 * decades);
}

void DecreaseDateByOneCentury(int day, int month, int year)
{
    WhatIsTheNewDateIfSubtractedNumberOfDayes(day, month, year, 100 * 365);
}

void DecreaseDateByXCenturies(int day, int month, int year, int centuries)
{
    WhatIsTheNewDateIfSubtractedNumberOfDayes(day, month, year, 100 * 365 * centuries);
}

int DayOfWeekOrder(int Day, int Month, int Year)
{
    return GetDayFromWeak(Day, Month, Year);
}

bool IsEndOfWeek(int Day, int Month, int Year)
{
    return DayOfWeekOrder(Day, Month, Year) == 6;
}

bool IsWeekEnd(int Day, int Month, int Year)
{
    int Order = DayOfWeekOrder(Day, Month, Year);
    return (Order == 5 || Order == 6);
}

bool IsBusinessDay(int Day, int Month, int Year)
{
    return !IsWeekEnd(Day, Month, Year);
}

int DaysUntilTheEndOfWeek(int Day, int Month, int Year)
{
    return 6 - DayOfWeekOrder(Day, Month, Year);
}

int DaysUntilTheEndOfMonth(int Day, int Month, int Year)
{
    return NumberOfDaysInaMonth_TheLastDayInMonth(Year, Month) - Day + 1;
}

int DaysUntilTheEndOfYear(int Day, int Month, int Year)
{
    return NumberOfDaysInaYear(Year) - TotalDaysFromBeginingTheYear(Day, Month, Year) + 1;
}

int ActualVacationPeriod(int DayDate1, int MonthDate1, int YearDate1, int DayDate2, int MonthDate2, int YearDate2)
{
    if (!IsDate1BeforeDate2(DayDate1, MonthDate1, YearDate1, DayDate2, MonthDate2, YearDate2))
    {
        return 0;
    }
    int Differnce = 0;
    while (IsDate1BeforeDate2(DayDate1, MonthDate1, YearDate1, DayDate2, MonthDate2, YearDate2))
    {
        if (IsTheEndDayInMonth(DayDate1, MonthDate1, YearDate1))
        {
            if (IsTheLastMonthInYear(MonthDate1))
            {
                if (IsWeekEnd(DayDate1, MonthDate1, YearDate1))
                {
                    DayDate1 = 1;
                    MonthDate1 = 1;
                    YearDate1++;
                }
                else
                {
                    DayDate1 = 1;
                    MonthDate1 = 1;
                    YearDate1++;
                    Differnce++;
                }
            }

            else
            {
                if (IsWeekEnd(DayDate1, MonthDate1, YearDate1))
                {
                    DayDate1 = 1;
                    MonthDate1++;
                }
                else
                {
                    DayDate1 = 1;
                    MonthDate1++;
                    Differnce++;
                }
            }
        }
        else
        {
            if (IsWeekEnd(DayDate1, MonthDate1, YearDate1))
            {
                DayDate1++;
            }

            else
            {
                DayDate1++;
                Differnce++;
            }
        }
    }

    return Differnce;
}
void VacationStarEnd(int day, int month, int year, int vacation)
{
    if (vacation <= 0)
    {
        return;
    }
    while (vacation != 0)
    {

        if (IsWeekEnd(day, month, year))
        {

            if (IsTheEndDayInMonth(day, month, year))
            {
                if (month == 12)
                {
                    day = 1;
                    month = 1;
                    year++;
                }
                else
                {
                    day = 1;
                    month += 1;
                }
            }
            else
            {
                day++;
            }
        }

        else
        {

            if (IsTheEndDayInMonth(day, month, year))
            {
                if (month == 12)
                {
                    day = 1;
                    month = 1;
                    year++;
                }
                else
                {
                    day = 1;
                    month += 1;
                }
            }
            else
            {
                day++;
            }

            vacation -= 1;
        }
    }

    cout << "return Date : " << GetDayName(GetDayFromWeak(day, month, year)) << ',' << day << "/" << month << "/" << year << endl;
}