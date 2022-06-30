#include "Texture.h"

//Размеры массивов типа Button
#define DAYCELLBUTTONSCOUNT 49
#define CHANGEMONTHBUTTONSCOUNT 4
#define DATEINFOBUTTONSCOUNT 2
#define EVENTINFOBUTTONSCOUNT 5
#define SETDATEBUTTONSCOUNT 3
#define EVENTCREATEBUTTONS 6

enum class ButtonArrays{dayCellButtons=0,changeMonthButtons,dateInfoButtons,eventInfoButtons,eventCreateButtons,setDateButtons,COUNT};

class Button
{
	int x, y;		//Задают местоположение ( левую верхнюю точку)
	short index;	//Индекс для функций, вызываемых при нажатии
	bool active;	//Кнопка вызывает какую-либо функцию
	Element element;	//индекс для получения пути к изображению, либо размеров этого изображения
public:
	Button();
	Button(int xx, int yy, short i, bool a, Element e, void(*f)(short));
	bool getActive();
	void setActive(bool a);
	short getIndex();
	void setIndex(short i);
	int getX();
	int getY();
	void(*buttonFunction)(short);	//указатель на вызываемую при нажатии функцию
	Element getElement();				//Возвращает путь для загрузки изображения

	Texture mTexture;
};

extern int x, y;						//Координаты, по которым было совершено нажатие кнопки мыши	
extern bool textInputActive;			//Ввод текста активен
extern string inputText;				//Вводимый текст
extern ButtonArrays textInputButtons;

extern short buttonArraysCount[int(ButtonArrays::COUNT)];		//Массив размеров массивов кнопок
extern bool buttonsState[int(ButtonArrays::COUNT)];				//Массив состояний массивов кнопок (видимый/невидимый)

//Массивы кнопок
extern Button dayCellButtons[DAYCELLBUTTONSCOUNT];
extern Button changeMonthButtons[CHANGEMONTHBUTTONSCOUNT];
extern Button dateInfoButtons[DATEINFOBUTTONSCOUNT];
extern Button eventsInfoButtons[EVENTINFOBUTTONSCOUNT];
extern Button eventCreateButtons[EVENTCREATEBUTTONS];
extern Button setDateButtons[SETDATEBUTTONSCOUNT];
//Массив указателей на массивы кнопок
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

//Отключение кнопок
void offButtons(ButtonArrays index);
//Включение кнопок
void onButtons(ButtonArrays index);

//Функции вызываемые нажатием той или иной кнопки
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