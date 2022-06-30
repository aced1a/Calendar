#include "Date.h"

bool invalidDate = false;
bool autoSetTime_time = true;
Date currentDate;
Date lastDate;

const string WeekDaysNames[DAYSINWEEK] = { "Понедельник\0","Вторник\0","Среда\0","Четверг\0","Пятница\0", "Суббота\0","Воскресенье\0" };
const string MonthNames[MONTHSAYEAR] = { "Январь\0","Февраль\0","Март\0","Апрель\0","Май\0", "Июнь\0","Июль\0","Август\0","Сентябрь\0","Октябрь\0","Ноябрь\0","Декабрь\0" };
short DaysInMonth[MONTHSAYEAR] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

//проверка, является ли год високосным
bool const leapyear(int year)		
{
	return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

//проверка на корректность даты
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

//Возвращает день недели заданной даты(день,месяц,год), используя формулу Зеллера
Week dayOfWeek(short day,short month,int year)
{
	short day_of_week = NULL;
	month++;							//в представленном в программе формате нумерация месяцев начинается с 0
	if (month == 1 || month == 2)		//в формуле зеллера месяцы начинаются с 3 (3 = март ... 14 = февраль)
	{
		month += 12;
	}

	int K = year % 100;
	int J = year / 100;

	day_of_week = (day + ((13 * (month + 1)) / 5) + K + (K / 4) + (J / 4) - (2 * J)) % 7;

	if (day_of_week < NULL)
		day_of_week += 7;

	for(short i=0;i<2;i++)														//перевод в формат, представленный в программе
		(day_of_week - 1) < NULL ? day_of_week = 6 : day_of_week --;
	
	return { Week(day_of_week) };
}

//Конструктор
Date::Date()
	:year{ 1970 }, month{ Month::jan }, day{ 1 }, day_of_week{ Week::Thursday }
{}

//Конструктор
Date::Date(short d, Month m, int y, Week weekday) 
:year{ y }, month{ m }, day{ d }, day_of_week{ weekday }
{
	if ( !isDate(d, m, y) || dayOfWeek(d, short(m), y) != weekday)
	{
		error(Error::invalidDate,"Error! Invalid date!\n");
	}
}

//Конструктор
Date::Date(short d, Month m, int y) :
	day{ d }, month{ m }, year{ y }
{
	if(!isDate(d,m,y))
	{
		error(Error::invalidDate,"Error! Invalid date!\n");
	}
	day_of_week = dayOfWeek(d, int(m), y);
}

//Возвращает число месяца
short Date::getDay()
{
	return day;
}

//Возвращает месяц
Month Date::getMonth() 
{ 
	return month; 
}

//Возвращает год
int Date::getYear() 
{
	return year;
}


Week Date::getDayOfWeek()
{
	return day_of_week; 
}

//Автоматическое получение текущей даты
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

		weekday - 1 < 0 ? weekday = 6 : weekday--;		//преобразуем под формат, принятый в этой программе

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

//Изменить год
void Date::chgYears(short index)
{
	year += index; 
	day_of_week = dayOfWeek(day, short(month), year);
	
}

//Изменить месяц
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

//Изменить день
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
