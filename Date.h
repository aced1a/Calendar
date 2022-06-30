#pragma once
#define SDL_MAIN_HANDLED
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
using namespace std;

#define MONTHSAYEAR 12								//������� ������� � ����
#define DAYSINWEEK 7								//������� ���� � ������

#define MAINWINDOW_HEIGHT 600						//������ �������� ����
#define MAINWINDOW_WIDTH 1200						//����� �������� ����

#define INDENTX 210									//������ ������
#define INDENTY	70									//������ ������


enum class Error { invalidDate, initSDL, initTTF, initFont, windowCreate, surfaceCreate, renderCreate, textureCreate, textRender, imageLoad, fileOpen };
enum class Week  { Monday = 0, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
enum class Month { jan = 0, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

class Date
{
	int year;
	Month month;
	short day;
	Week day_of_week;

public:
	Date();
	Date(short d, Month m, int y);
	Date(short d, Month m, int y, Week weekday);
	short getDay();
	Month getMonth();
	int getYear();
	Week getDayOfWeek();
	void chgMonth(short index);
	void chgDay(short index);
	void chgYears(short index);
};


extern bool invalidDate;
extern bool autoSetTime_time;
extern Date currentDate;		//������� ����
extern Date lastDate;			//����(�����,���) ������� ��������

extern short DaysInMonth[MONTHSAYEAR];		//������� ���� � ������ ������
extern const string WeekDaysNames[DAYSINWEEK];	//�������� ���� ������
extern const string MonthNames[MONTHSAYEAR];	//�������� �������

bool const leapyear(int year);		//��������, �������� �� ��� ����������

void autoSetTime();					//������������� ������� ����

Week dayOfWeek(short day, short month, int year);				//���������� ���� ������ �������� ����(����,�����,���), ��������� ������� �������

void setCurrentDate(short day, short month, short year);	//DELETE THIS

void error(Error error,string str);		//������� ����������

bool updateTime();

bool isDate(short day, Month month, int year);