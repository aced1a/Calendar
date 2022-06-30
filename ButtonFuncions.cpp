#include "Button.h"

//Здесь находятся функции, вызываемые при нажатии на ту или иную кнопку


void acceptInputDate(short index)
{
	if (parsStrtoDate(inputText))
	{
		endSetDate(0);
		autoSetTime_time = false;
		invalidDate = false;
	}
	else
	{
		inputText = "Invalid date";
		inputTextRender(100,100);
		drawButtons();
		ViewWindow();
	}
}

void startSetDate(short index)
{
	for(short i=0;i<short(ButtonArrays::setDateButtons);i++)
	{
		offButtons(ButtonArrays(i));
		buttonsState[i] = false;
	}
	buttonsState[short(ButtonArrays::setDateButtons)] = true;
	onButtons(ButtonArrays::setDateButtons);
	SDL_StartTextInput();
	textInputButtons = ButtonArrays::setDateButtons;
	loadMedia_SetDateButtons();
	drawButtons();
	ViewWindow();
}

void endSetDate(short index)
{
	for (short i = 0; i<short(ButtonArrays::setDateButtons); i++)
	{
		onButtons(ButtonArrays(i));
		buttonsState[i] = true;
	}
	inputText = "";
	buttonsState[short(ButtonArrays::setDateButtons)] = false;
	offButtons(ButtonArrays::setDateButtons);
	SDL_StartTextInput();
	textInputButtons = ButtonArrays::eventCreateButtons;
	if (buttonsState[short(ButtonArrays::eventCreateButtons)] = true)
	{
		eventCreateMenuBack(NULL);
	}
	loadMedia();
	drawButtons();
	ViewWindow();
}

//Изменение месяца
void changeMonth(short index)
{
	if (index == 0)
		lastDate = currentDate;
	else
		lastDate.chgMonth(index);

	offButtons(ButtonArrays::eventInfoButtons);
	loadMedia_DayCellButtons(short(dayOfWeek(1, int(lastDate.getMonth()), lastDate.getYear())), lastDate.getMonth(), lastDate.getYear());
	loadMedia_DateInfoButtons(1);
	if (buttonsState[short(ButtonArrays::eventCreateButtons)] = true)
	{
		eventCreateMenuBack(NULL);
	}
	else {
		buttonsState[short(ButtonArrays::eventInfoButtons)] = false;
		offButtons(ButtonArrays::eventInfoButtons);
		drawButtons();
		ViewWindow();
	}
}

//Отобразить список событий для даты
void viewEvent(short day)
{
	offset_list = 0;
	loadMedia_EventsInfoButtons(day, short(lastDate.getMonth()), lastDate.getYear(),NULL);
	eventsInfoButtons[2].setIndex(day);
	buttonsState[short(ButtonArrays::eventInfoButtons)] = true;
	onButtons(ButtonArrays::eventInfoButtons);
	drawButtons();;
	ViewWindow();
}

//Отобразить меню создания/удаления событий
void viewEventCreateMenu(short day)
{
	loadMedia_EventCreateButtons(day, NULL);
	buttonsState[short(ButtonArrays::dayCellButtons)] = false;
	buttonsState[short(ButtonArrays::eventCreateButtons)] = true;
	buttonsState[short(ButtonArrays::eventInfoButtons)] = true;
	offButtons(ButtonArrays::dayCellButtons);
	onButtons(ButtonArrays::eventCreateButtons);
	eventCreateButtons[1].setIndex(day);
	drawButtons();
	//buttonsState[short(ButtonArrays::eventCreateButtons)] = false;
	ViewWindow();
}

//Выход из меню создания/удаления событий
void eventCreateMenuBack(short index)
{
	if (textInputActive)
	{
		SDL_StopTextInput();
		textInputActive = false;
		inputText = "";
	}
	
	offset_delList = 0;
	offset_list = 0;
	buttonsState[short(ButtonArrays::eventCreateButtons)]	= false;
	buttonsState[short(ButtonArrays::dayCellButtons)]	    = true;
	buttonsState[short(ButtonArrays::eventInfoButtons)]		= false;
	offButtons(ButtonArrays::eventInfoButtons);
	offButtons(ButtonArrays::eventCreateButtons);
	loadMedia_DayCellButtons(short(dayOfWeek(1,short(lastDate.getMonth()),lastDate.getYear())),lastDate.getMonth(),lastDate.getYear());

	drawButtons();
	ViewWindow();
}

//Разрешить ввод текста
void start_textInput(short index)
{
	SDL_StartTextInput();
	textInputActive = true;
}

//Добавить новое событие
void addNewEvent(short day)
{
	if (inputText != "")
	{
		eventArray[day - 1].addNewEvent(inputText);
		inputText = "";
		loadMedia_EventsInfoButtons(day, short(lastDate.getMonth()), lastDate.getYear(),NULL);
		loadMedia_EventCreateButtons(day,NULL);
		drawButtons();
		ViewWindow();
	}
}

//Удалить событие
void deleteElement(short day)
{
	short h = 20, index = -1;
	short xx = elementSizes[short(Element::cell_big)].first;
	short yy = elementSizes[short(Element::cell_big)].second * 4+10;
	vector<string> list = eventArray[day - 1].getEventList();
	if (x < 20+xx)
	{
		for (short i = 0; i < list.size(); i++)
		{
			if (y < h*(i+1)+yy && y > h*i+yy)
			{
				index = i;
			}
		}
	}
	if (index != -1)
	{
		eventArray[day - 1].deleteEvent(index+1);
		loadMedia_EventCreateButtons(day,NULL);
		loadMedia_EventsInfoButtons(day, short(lastDate.getMonth()), lastDate.getYear(), NULL);
		drawButtons();
		ViewWindow();
	}
}

//Сдвиг списка событий вверх (кнопкой)
void swipUp(short index)
{
	if (index == short(ButtonArrays::eventCreateButtons))
	{
		loadMedia_EventCreateButtons(eventCreateButtons[2].getIndex(),-1);
	}
	else if (index == short(ButtonArrays::eventInfoButtons))
	{
		loadMedia_EventsInfoButtons(eventsInfoButtons[2].getIndex(),short(lastDate.getMonth()),lastDate.getYear(),-1);
	}
	drawButtons();
	ViewWindow();
}

//Сдвиг списка событий вниз (кнопкой)
void swipDown(short index)
{
	if (index == short(ButtonArrays::eventCreateButtons))
	{
		loadMedia_EventCreateButtons(eventCreateButtons[2].getIndex(), 1);
	}
	else if (index == short(ButtonArrays::eventInfoButtons))
	{
		loadMedia_EventsInfoButtons(eventsInfoButtons[2].getIndex(), short(lastDate.getMonth()), lastDate.getYear(), 1);
	}
	drawButtons();
	ViewWindow();
}
