#include "Date.h"

class EventList
{
	vector<string> list;
	short day, month;
public:
	EventList();
	void setDate(short d, short m);
	void loadEventList();		//�������� ������ ������� ��� ������� ���� (����,�����)
	vector<string> getEventList();	//���������� ������ list
	string getShownEvent();			//���������� ������� ������� ������� list (list[0]),���� ""
	void rewriteEventList();		//������ � ����, �� � ������ ����������
	void addNewEvent(string str);	//������ � ���� ������ str � ������ ���������� + ���������� ������ str � ������ list
	void deleteEvent(unsigned int index);	//�������� �� ������� list �������� � �������� index-1 (list[index-1])
	void cleareEventList();					//������� ������� list
};

extern EventList eventArray[31];	
extern bool invalidFile;

void checkFiles();	//�������� ������, ���� ��� ������-�� �� ������, �� ����� ������

