#include "Button.h"



short buttonArraysCount[int(ButtonArrays::COUNT)];
bool buttonsState[int(ButtonArrays::COUNT)];

Button dayCellButtons[DAYCELLBUTTONSCOUNT];
Button changeMonthButtons[CHANGEMONTHBUTTONSCOUNT];
Button dateInfoButtons[DATEINFOBUTTONSCOUNT];
Button eventsInfoButtons[EVENTINFOBUTTONSCOUNT];
Button eventCreateButtons[EVENTCREATEBUTTONS];
Button setDateButtons[SETDATEBUTTONSCOUNT];

Button* ptrButtonArrays[int(ButtonArrays::COUNT)] = { dayCellButtons,changeMonthButtons,dateInfoButtons,eventsInfoButtons,eventCreateButtons,setDateButtons };
//Button* ptrButtonArrays[int(ButtonArrays::COUNT)] = { dayCellButtons,changeMonthButtons,dateInfoButtons,eventsInfoButtons,eventCreateButtons};

Button::Button()
	:x{ 0 }, y{ 0 }, index{ 0 }, active{ 0 }, element{ Element::cell }
{
	buttonFunction = nullptr;
}

Button::Button(int xx,int yy, short i, bool a,Element e, void(*f)(short))
:x{xx},y{yy},index{i},active{a},element{e}
{
	buttonFunction = f;
}

bool Button::getActive()
{
	return active;
}

short Button::getIndex()
{
	return index;
}

int Button::getX()
{
	return x;
}

int Button::getY()
{
	return y;
}

Element Button::getElement()
{
	return element;
}

//void Button::chgPath(string str)
//{
//	path = str;
//}

void Button::setActive(bool a)
{
	active = a;
}

void Button::setIndex(short i)
{
	index = i;
}

void offButtons(ButtonArrays index)
{
	Button* button = nullptr;

	for(short i=0;i<buttonArraysCount[int(index)];i++)
	{
		button = &ptrButtonArrays[int(index)][i];
		button->setActive(false);
	}
}

void onButtons(ButtonArrays index)
{
	Button* button = nullptr;

	for (short i = 0; i < buttonArraysCount[short(index)]; i++)
	{
		button = &ptrButtonArrays[short(index)][i];

		if (!(index==ButtonArrays::eventInfoButtons && (i == 0 || i==1 )) && !(index==ButtonArrays::setDateButtons && i==0 ))
			button->setActive(true);
	}
}
