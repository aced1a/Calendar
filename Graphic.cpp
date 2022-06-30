#include "Button.h"
//short currentDay_index = -1;
short offset_list = 0;
short offset_delList = 0;


void loadMedia_backgrounds()
{
	for (short i = 0; i < 4; i++)
	{
		backgrounds[i].loadImage(imagePathsArray[i]);
		backgrounds[i].loadTexture();
	}
}

void inputTextRender(short w,short h)
{
	Button* textInputButton = nullptr;
	textInputButton= &ptrButtonArrays[short(textInputButtons)][0];

	string renderText = "";
	if (inputText.size() > 60)
	{
		for (unsigned short i = 0; i < inputText.size(); i++)
		{
			if (i > inputText.size() - 60)
			{
				renderText += inputText[i];
			}
		}
	}
	else
	{
		renderText = inputText;
	}

	textInputButton->mTexture.createSurface(textInputButton->getElement());
	textInputButton->mTexture.addImage(imagePathsArray[short(textInputButton->getElement())], w, h);
	if (textInputButtons==ButtonArrays::setDateButtons)
	{
		if (invalidDate)
			textInputButton->mTexture.loadFromText("Не удалось получить дату", fontArray[short(Fonts::wordFont)], gTextColor, 150, 20);
		textInputButton->mTexture.loadFromText("Задайте дату в формате: день.месяц.год ", fontArray[short(Fonts::wordFont)], gTextColor, 150, 50);
	}
	textInputButton->mTexture.loadFromText(renderText, fontArray[short(Fonts::wordFont_small)],blackColor, w + 2, h + 2);
	textInputButton->mTexture.loadTexture();
	drawButtons();
	ViewWindow();
}

//Отобразить список событий
void showEventList(Button* button,EventList* eventList,short direction,Element element)
{
	vector<string> list = eventList->getEventList();
	short dh = 20,dw=10;
	short* offset = nullptr;

	if (element == Element::COUNT)
		offset = &offset_list;
	else
		offset = &offset_delList;

	*offset += direction;

	if (*offset < 0)
		*offset = 0;
	else if (*offset > list.size() - 1)
		*offset = list.size() - 1;

	if (element != Element::COUNT)
		dw += 15;
	for(unsigned short i=0;i<list.size()-*offset;i++)
	{
		if (10 + dh * i > elementSizes[short(Element::eventInfoList)].second - 30)
			break;

		if (element != Element::COUNT)
			button->mTexture.addImage(imagePathsArray[short(element)],5, dh*i + 10,true,transpatentColor);

		button->mTexture.loadFromText(list[i+*offset], fontArray[int(Fonts::wordFont_small)], gTextColor, dw,10 + dh * i );
	}
}

//Задать параметры для загрузки списка событий для текущей даты
void loadEventForDay(short day,short month)
{
	eventArray[day].cleareEventList();
	eventArray[day].setDate(day, short(month));
	eventArray[day].loadEventList();
}

//Загрузка всех требуемых данных для кнопок массива dayCellButtons
void loadMedia_DayCellButtons(short month_beg, Month month, int year)
{
	int daysInMonth = DaysInMonth[int(month)];
	if (month == Month::feb && leapyear(year))
		daysInMonth++;

	/*if (currentDay_index != -1)
	{
		dayCellButtons[currentDay_index].chgPath(imagePathsArray[int(ImagePath::cellPath)]);
		currentDay_index = -1;
	}*/

	for (short i = 0; i < buttonArraysCount[int(ButtonArrays::dayCellButtons)]; i++)
	{
		
		/*if (currentDay_index==-1 && currentDate.getMonth() == month && (i - month_beg - 6) == currentDate.getDay() && currentDate.getYear() == year)
			dayCellButtons[i].chgPath(imagePathsArray[int(ImagePath::cellPath_currentDay)]);*/

		dayCellButtons[i].mTexture.createSurface(Element::cell);
		
		if (i < 7)
		{
			dayCellButtons[i].mTexture.loadFromText(WeekDaysNames[i % 7], fontArray[int(Fonts::wordFont)], gTextColor, 10,10 );
			dayCellButtons[i].setActive(false);
		}
		else if (i > month_beg + 6 && i <= daysInMonth + 6+month_beg)
		{
			loadEventForDay(i - month_beg - 7, short(month));
			dayCellButtons[i].setActive(true);
			dayCellButtons[i].setIndex(i - month_beg - 6);
			dayCellButtons[i].mTexture.loadFromText(digit_transform(i - month_beg - 6), fontArray[int(Fonts::digitFont)], gTextColor, 10,10 );
			dayCellButtons[i].mTexture.loadFromText(eventArray[(i - month_beg - 7)].getShownEvent(), fontArray[int(Fonts::wordFont_small)], gTextColor, 20,40 );
		}
		else
			dayCellButtons[i].setActive(false);

		dayCellButtons[i].mTexture.loadTexture();

	}
	
}

//Загрузка всех требуемых данных для кнопок массива eventsInfoButtons
void loadMedia_EventsInfoButtons(short day,short month,short year,short direciton)
{
	for (short i = 0; i < buttonArraysCount[short(ButtonArrays::eventInfoButtons)]; i++)
	{	
		eventsInfoButtons[i].mTexture.createSurface(eventsInfoButtons[i].getElement());

		if (i == 0)
		{
			eventsInfoButtons[i].mTexture.loadFromText(getDate_str(day, month + 1, year), fontArray[short(Fonts::digitFont)], gTextColor, 10,10 );
			eventsInfoButtons[i].mTexture.loadFromText(WeekDaysNames[short(dayOfWeek(day, month, year))], fontArray[short(Fonts::wordFont)], gTextColor, 10,30 );
		}
		else if (i == 1)
		{
			showEventList(&eventsInfoButtons[i], &eventArray[day - 1], direciton, Element::COUNT);
		}
		else if (i == 2)
		{
			eventsInfoButtons[i].mTexture.loadFromText("Создать/удалить", fontArray[short(Fonts::wordFont_small)], gTextColor, 20,10 );
			eventsInfoButtons[i].mTexture.loadFromText("событие", fontArray[short(Fonts::wordFont_small)], gTextColor, 20,30 );
		}
		else
			eventsInfoButtons[i].mTexture.loadImage(imagePathsArray[short(eventsInfoButtons[i].getElement())],true,transpatentColor);

		eventsInfoButtons[i].mTexture.loadTexture();
	}
}

//Загрузка всех требуемых данных для кнопок массива changeMonthButtons
void loadMedia_ChangeMonthButtons()
{
	Button* button = nullptr;
	for (short i = 0; i < buttonArraysCount[int(ButtonArrays::changeMonthButtons)];i++) 
	{
		button = &changeMonthButtons[i];
		if (button != nullptr) 
		{
			button->mTexture.loadImage(imagePathsArray[short(button->getElement())], true, transpatentColor);
			button->mTexture.loadTexture();
		}
	}
}

//Загрузка всех требуемых данных для кнопок массива dateInfoButtons
void loadMedia_DateInfoButtons(short index)
{
	Button* button = nullptr;
	if (index >= buttonArraysCount[int(ButtonArrays::dateInfoButtons)])
		index = 0;

	for(short i = index;i<buttonArraysCount[int(ButtonArrays::dateInfoButtons)];i++)
	{
		button = &dateInfoButtons[i];

		button->mTexture.createSurface(button->getElement());
		if (i == 0)
		{
			button->mTexture.loadFromText(getDate_str(currentDate.getDay(),short(currentDate.getMonth())+1,currentDate.getYear()), fontArray[int(Fonts::wordFont)], gTextColor,30,10 );
			button->mTexture.loadFromText(WeekDaysNames[int(currentDate.getDayOfWeek())], fontArray[int(Fonts::wordFont)], gTextColor,30,30 );
		}
		else
		{
			button->mTexture.loadFromText(MonthNames[int(lastDate.getMonth())], fontArray[int(Fonts::wordFont)], gTextColor,30,5 );
			button->mTexture.loadFromText(digit_transform(lastDate.getYear()) + " год", fontArray[int(Fonts::wordFont)], gTextColor,30,30);
		}

		button->mTexture.loadTexture();
	}
}

//Загрузка всех требуемых данных для кнопок массива eventCreateButtons
void loadMedia_EventCreateButtons(short day,short direct)
{
	for(short i=0;i<buttonArraysCount[short(ButtonArrays::eventCreateButtons)];i++)
	{
		if (i < 3)
			eventCreateButtons[i].mTexture.createSurface(eventCreateButtons[i].getElement());
		else
			eventCreateButtons[i].mTexture.loadImage(imagePathsArray[short(eventCreateButtons[i].getElement())],true,transpatentColor);

		if(i==0)
		{
			eventCreateButtons[i].mTexture.addImage(imagePathsArray[short(eventCreateButtons[i].getElement())],100,100);
		}
		else if (i == 1)
		{
			eventCreateButtons[i].mTexture.loadFromText("Сохранить", fontArray[short(Fonts::wordFont_small)], gTextColor, 2,2 );
		}
		else if (i == 2)
		{
			eventCreateButtons[i].setIndex(day);
			showEventList(&eventCreateButtons[i], &eventArray[day - 1], direct, Element::deleteButton);
		}
		eventCreateButtons[i].mTexture.loadTexture();
	}
}

void loadMedia_SetDateButtons()
{
	for (short i = 0; i < buttonArraysCount[short(ButtonArrays::setDateButtons)]; i++)
	{
		if(i!=0)
			setDateButtons[i].mTexture.loadImage(imagePathsArray[short(setDateButtons[i].getElement())], true, transpatentColor);
		else
		{
			setDateButtons[i].mTexture.createSurface(setDateButtons[i].getElement());
			setDateButtons[i].mTexture.addImage(imagePathsArray[short(setDateButtons[i].getElement())], 100, 100);
			if(invalidDate)
				setDateButtons[i].mTexture.loadFromText("Не удалось получить дату", fontArray[short(Fonts::wordFont)], gTextColor, 150, 20);
			setDateButtons[i].mTexture.loadFromText("Задайте дату в формате: день.месяц.год ", fontArray[short(Fonts::wordFont)], gTextColor, 150, 50);
		}

		if (i == 1 && invalidDate)
		{
			setDateButtons[i].setActive(false);		
		}
		else if (i == 2)
		{
			setDateButtons[i].mTexture.loadFromText("Принять", fontArray[short(Fonts::digitFont_small)], blackColor, 2, 2);
		}


		setDateButtons[i].mTexture.loadTexture();

				
	}
	
}

void loadMedia()
{
	loadMedia_backgrounds();
	loadMedia_DayCellButtons(short(dayOfWeek(1, int(currentDate.getMonth()), currentDate.getYear())), currentDate.getMonth(), currentDate.getYear());
	loadMedia_ChangeMonthButtons();
	loadMedia_DateInfoButtons(0);
}

void drawBackground()
{
	short month = short(lastDate.getMonth());
	for(short i=0;i<2;i++)
		month-1 < 0 ? month=11 : month--;
	backgrounds[month / 3].render(0, 0);
}

//Отрисовка кнопок
void drawButtons()
{
	Button* button	  = nullptr;
	short count       = 0;
	short buttonCount = int(ButtonArrays::COUNT);

	drawBackground();
	for (count; count < buttonCount; count++)
	{
		if (buttonsState[count])
		{
			for (short j = 0; j < buttonArraysCount[count]; j++)
			{
				button = &ptrButtonArrays[count][j];
				if (button != nullptr)
				{
					button->mTexture.render(button->getX(), button->getY());
				}
			}
		}
	}
}

//Отобразить рендер
void ViewWindow()
{
	SDL_RenderPresent(gRenderer);
	SDL_RenderClear(gRenderer);
}