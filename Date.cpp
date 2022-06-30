#include "Date.h"

bool invalidDate = false;
bool autoSetTime_time = true;
Date currentDate;
Date lastDate;

const string WeekDaysNames[DAYSINWEEK] = { "�����������\0","�������\0","�����\0","�������\0","�������\0", "�������\0","�����������\0" };
const string MonthNames[MONTHSAYEAR] = { "������\0","�������\0","����\0","������\0","���\0", "����\0","����\0","������\0","��������\0","�������\0","������\0","�������\0" };
short DaysInMonth[MONTHSAYEAR] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

//��������, �������� �� ��� ����������
bool const leapyear(int year)		
{
	return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

//�������� �� ������������ ����
bool isDate(short day,Month month,int year)
{
	int max_day_in_month = DaysInMonth[short(month)];
	if (month == Month::feb && leapyear(year))
		max_day_in_month++;
	if (month > Month::dec || month < Month::jan) return false;
	if (day < 0) return false;
	if (day > max_day_in_month) return false;
	return true;
}

//���������� ���� ������ �������� ����(����,�����,���), ��������� ������� �������
Week dayOfWeek(short day,short month,int year)
{
	short day_of_week = NULL;
	month++;							//� �������������� � ��������� ������� ��������� ������� ���������� � 0
	if (month == 1 || month == 2)		//� ������� ������� ������ ���������� � 3 (3 = ���� ... 14 = �������)
	{
		month += 12;
	}

	int K = year % 100;
	int J = year / 100;

	day_of_week = (day + ((13 * (month + 1)) / 5) + K + (K / 4) + (J / 4) - (2 * J)) % 7;

	if (day_of_week < NULL)
		day_of_week += 7;

	for(short i=0;i<2;i++)														//������� � ������, �������������� � ���������
		(day_of_week - 1) < NULL ? day_of_week = 6 : day_of_week --;
	
	return { Week(day_of_week) };
}

//�����������
Date::Date()
	:year{ 1970 }, month{ Month::jan }, day{ 1 }, day_of_week{ Week::Thursday }
{}

//�����������
Date::Date(short d, Month m, int y, Week weekday) 
:year{ y }, month{ m }, day{ d }, day_of_week{ weekday }
{
	if ( !isDate(d, m, y) || dayOfWeek(d, short(m), y) != weekday)
	{
		error(Error::invalidDate,"Error! Invalid date!\n");
	}
}

//�����������
Date::Date(short d, Month m, int y) :
	day{ d }, month{ m }, year{ y }
{
	if(!isDate(d,m,y))
	{
		error(Error::invalidDate,"Error! Invalid date!\n");
	}
	day_of_week = dayOfWeek(d, int(m), y);
}

//���������� ����� ������
short Date::getDay()
{
	return day;
}

//���������� �����
Month Date::getMonth() 
{ 
	return month; 
}

//���������� ���
int Date::getYear() 
{
	return year;
}


Week Date::getDayOfWeek()
{
	return day_of_week; 
}

//�������������� ��������� ������� ����
void autoSetTime()
{
	short day = 0, month = 0,weekday = 0;
	int year = 1900;
	time_t rawtime;
	struct tm* ptm;
	time(&rawtime);
	if (rawtime)
	{
		ptm = localtime(&rawtime);
		day = ptm->tm_mday;
		month = ptm->tm_mon;		
		year += ptm->tm_year;
		weekday = ptm->tm_wday;

		weekday - 1 < 0 ? weekday = 6 : weekday--;		//����������� ��� ������, �������� � ���� ���������

		if (invalidDate)
			invalidDate = false;

		currentDate = Date{ day, Month(month), year, Week(weekday) };
		lastDate = currentDate;
	}
	else
	{
		error(Error::invalidDate, "Error. Auto time initialization failed.");
	}
}

bool updateTime()
{
	time_t rawtime;
	time(&rawtime);
	if (rawtime)
	{
		
		struct tm* ptm = localtime(&rawtime);
		if (ptm->tm_mday != currentDate.getDay())
		{
			currentDate.chgDay(1);
			return true;
		}
		return false;
	}
	else
		error(Error::invalidDate, "Error.Update time failes");

	return false;
}

//�������� ���
void Date::chgYears(short index)
{
	year += index; 
	day_of_week = dayOfWeek(day, short(month), year);
	
}

//�������� �����
void Date::chgMonth(short index)
{
	if (index == 1)
	{
		if (month == Month::dec)
		{
			month = Month::jan;
			year++;
		}
		else
			month = Month(int(month) + 1);
	}
	else
	{
		if (month == Month::jan)
		{
			month = Month::dec;
			year--;
		}
		else
			month = Month(int(month) - 1);
	}
	day_of_week = dayOfWeek(day, short(month), year);
}

//�������� ����
void Date::chgDay(short index)
{
	short daysinmonth = DaysInMonth[int(month)];
	if (month == Month::feb && leapyear(year))
		daysinmonth++;

	if (index == 1) {
		if (day == daysinmonth)
		{
			day = 1;
			chgMonth(1);
		}
		else
			day++;
	}
	else {
		if (day == 1)
		{
			chgMonth(-1);
			day = DaysInMonth[int(month)];
		}
		else
			day--;
	}
	day_of_week = dayOfWeek(day, short(month), year);
}

void setCurrentDate(short day,short month,short year)
{
	currentDate = Date{ day, Month(month), year};
	lastDate = currentDate;
	cout << currentDate.getDay() << endl;
}
