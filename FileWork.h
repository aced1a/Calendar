#include "Date.h"

class EventList
{
	vector<string> list;
	short day, month;
public:
	EventList();
	void setDate(short d, short m);
	void loadEventList();		//Загрузка списка событий для текущей даты (день,месяц)
	vector<string> getEventList();	//Возвращает вектор list
	string getShownEvent();			//Возвращает нулевой элемент вектора list (list[0]),либо ""
	void rewriteEventList();		//Запись в файл, не в режиме дополнения
	void addNewEvent(string str);	//Запись в файл строки str в режиме дополнения + добавление строки str в вектор list
	void deleteEvent(unsigned int index);	//Удаление из вектора list элемента с индексом index-1 (list[index-1])
	void cleareEventList();					//Очистка вектора list
};

extern EventList eventArray[31];	
extern bool invalidFile;

void checkFiles();	//Проверка файлов, если нет какого-то из файлов, он будет создан

