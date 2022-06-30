#include "FileWork.h"
#include <fstream>

bool invalidFile = false;
EventList eventArray[31];

//Конструктор
EventList::EventList()
	:day{ 0 }, month{ 0 }
{}

//Возвращает путь для открытия файлы, для заданной даты (день,месяц)
string getFilePath(short day, short month)
{
	char char_str[65];
	sprintf(char_str, "C://SDL//Calendar_v0.3.1//Calendar_v0.3.1//EventsData//%d.%d.bin", day + 1, month + 1);
	return string{ char_str };
}

//Проверка файлов, если нет какого-то из файлов, он будет создан
void checkFiles()
{
	string currentFilePath = "";
	short daysInMonth = 0;
	for (short i = 0; i < MONTHSAYEAR; i++)
	{
		daysInMonth = DaysInMonth[i];
		if (i == 1)
			daysInMonth++;

		for (short j = 0; j < daysInMonth; j++)
		{
			currentFilePath = getFilePath(j, i);
			ofstream file(currentFilePath.c_str(), ios::binary | ios::app);
			if (!file.is_open())
			{
				error(Error::fileOpen,"Open file error");
			}
			file.close();
		}
	}
	invalidFile = false;
}

void EventList::setDate(short d,short m)
{
	day = d;
	month = m;
}

vector<string> EventList::getEventList()
{
	return list;
}

void EventList::rewriteEventList()
{
	ofstream file;
	char newStr = '\n';
	string currentFilePath = getFilePath(day, month);
	file.open(currentFilePath.c_str(), ios::binary);
	if(!file)
	{
		error(Error::fileOpen, "File open error!");
	}

	for(int i=0;i<list.size();i++)
	{
		for (int j = 0; j < list[i].size(); j++)
			file.write((char*)&list[i][j], sizeof(list[i][j]));

		file.write((char*)&newStr, sizeof(newStr));
	}
	file.close();
}

void EventList::addNewEvent(string str)
{
	list.push_back(str);
	str += '\n';
	string currentFilePath = getFilePath(day, month);
	ofstream file(currentFilePath.c_str(),ios::binary | ios::app );
	if(!file)
	{
		error(Error::fileOpen, "Open file error");
	}
	for (int i = 0; i < str.size(); i++)
	{
		file.write((char*)&str[i], sizeof(str[i]));
	}
	file.close();
}

void EventList::deleteEvent(unsigned int index)
{
	if (!(index > list.size()))
	{
		//	error("deleteEvent invalid index");
		list.erase(list.begin() + (index - 1));
		rewriteEventList();
	}
}

void EventList::loadEventList()
{
	ifstream file;
	string currentFilePath = getFilePath(day, month);
	file.open(currentFilePath.c_str(),ios::binary);

	if (!file)
	{
		cout << currentFilePath << endl;
		error(Error::fileOpen, "Open file error");
	}
	while(!file.eof())
	{
		string str = "";
		getline(file, str);
		if (str != "" && str!=" ") 
		{
			list.push_back(str);
		}

	}
	file.close();
}

string EventList::getShownEvent()
{
	if (list.size() != 0)
		return list[0];
	return " ";
}

void EventList::cleareEventList()
{
	while(list.size()!=0)
	{
		list.erase(list.end()-1);
	}
	day = 0;
	month = 0;
}