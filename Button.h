#include "Texture.h"

//������� �������� ���� Button
#define DAYCELLBUTTONSCOUNT 49
#define CHANGEMONTHBUTTONSCOUNT 4
#define DATEINFOBUTTONSCOUNT 2
#define EVENTINFOBUTTONSCOUNT 5
#define SETDATEBUTTONSCOUNT 3
#define EVENTCREATEBUTTONS 6

enum class ButtonArrays{dayCellButtons=0,changeMonthButtons,dateInfoButtons,eventInfoButtons,eventCreateButtons,setDateButtons,COUNT};

class Button
{
	int x, y;		//������ �������������� ( ����� ������� �����)
	short index;	//������ ��� �������, ���������� ��� �������
	bool active;	//������ �������� �����-���� �������
	Element element;	//������ ��� ��������� ���� � �����������, ���� �������� ����� �����������
public:
	Button();
	Button(int xx, int yy, short i, bool a, Element e, void(*f)(short));
	bool getActive();
	void setActive(bool a);
	short getIndex();
	void setIndex(short i);
	int getX();
	int getY();
	void(*buttonFunction)(short);	//��������� �� ���������� ��� ������� �������
	Element getElement();				//���������� ���� ��� �������� �����������

	Texture mTexture;
};

extern int x, y;						//����������, �� ������� ���� ��������� ������� ������ ����	
extern bool textInputActive;			//���� ������ �������
extern string inputText;				//�������� �����
extern ButtonArrays textInputButtons;

extern short buttonArraysCount[int(ButtonArrays::COUNT)];		//������ �������� �������� ������
extern bool buttonsState[int(ButtonArrays::COUNT)];				//������ ��������� �������� ������ (�������/���������)

//������� ������
extern Button dayCellButtons[DAYCELLBUTTONSCOUNT];
extern Button changeMonthButtons[CHANGEMONTHBUTTONSCOUNT];
extern Button dateInfoButtons[DATEINFOBUTTONSCOUNT];
extern Button eventsInfoButtons[EVENTINFOBUTTONSCOUNT];
extern Button eventCreateButtons[EVENTCREATEBUTTONS];
extern Button setDateButtons[SETDATEBUTTONSCOUNT];
//������ ���������� �� ������� ������
extern Button* ptrButtonArrays[int(ButtonArrays::COUNT)];


void eventControll();

void drawButtons();
void ViewWindow();

//----------
void init_SDL();
void close_SDL();

void init_Fonts();
void close_Fonts();

void init_Buttons();
//------------

void loadMedia_DayCellButtons(short month_beg, Month month, int year);
void loadMedia_DateInfoButtons(short index);
void loadMedia_EventsInfoButtons(short day, short month, short year,short direction);
void loadMedia_EventCreateButtons(short day,short direct);
void loadMedia_SetDateButtons();
void loadMedia();
//void inputTextRender(Button* textInputButton, short w, short h);
void inputTextRender(short w, short h);

//���������� ������
void offButtons(ButtonArrays index);
//��������� ������
void onButtons(ButtonArrays index);

//������� ���������� �������� ��� ��� ���� ������
void changeMonth(short index);
void start_textInput(short index);
void viewEvent(short day);
void eventCreateMenuBack(short index);
void viewEventCreateMenu(short day);
void addNewEvent(short day);
void deleteElement(short day);
void swipUp(short index);
void swipDown(short index);
void startSetDate(short index);
void endSetDate(short index);
void acceptInputDate(short index);

extern short offset_list;
extern short offset_delList;