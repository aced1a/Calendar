#include "Button.h"

//����� ��������� ������� ��� ������������� ���� �� �� �� ����

//������������� SDL
void init_SDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		error(Error::initSDL,"SDL initialization failed. SDL Error: " + string(SDL_GetError()));
	}
	if (TTF_Init() < 0)
	{
		error(Error::initTTF,"SDL_TTF initialization failed: " + string(TTF_GetError()));
	}
	
	gWindow = SDL_CreateWindow("Calendar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow==nullptr)
	{
		error(Error::windowCreate,"SDL_CreateWindow failed: " + string(SDL_GetError()));
	}
	/*gSurface = SDL_GetWindowSurface(gWindow);
	if (gSurface == nullptr)
		error("error");*/
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);	// | SDL_RENDERER_PRESENTVSYNC
	if(gRenderer==nullptr)
	{
		error(Error::renderCreate,"SDL_CreateRenderer failed: " + string(SDL_GetError()));
	}
	
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
}

//������� SDL
void close_SDL()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	SDL_Quit();
	TTF_Quit();
}

//������������� ������� �������� �������
void init_FontSizeArray()
{
	fontSizeArray[short(Fonts::digitFont)] = 25;
	fontSizeArray[short(Fonts::digitFont_small)] = 16;
	fontSizeArray[short(Fonts::wordFont)] = 22;
	fontSizeArray[short(Fonts::wordFont_small)] = 16;
}

//������������� ������� �������
void init_Fonts()
{
	bool fail = false;
	init_FontSizeArray();
	
	fontArray[short(Fonts::digitFont)]		= TTF_OpenFont(fontPath.c_str(), fontSizeArray[short(Fonts::digitFont)]);
	if (fontArray[short(Fonts::digitFont)] == nullptr)
	{
		fail = true;
	}
	fontArray[short(Fonts::digitFont_small)]  = TTF_OpenFont(fontPath.c_str(), fontSizeArray[short(Fonts::digitFont_small)]);
	if (fontArray[short(Fonts::digitFont_small)] == nullptr)
	{
		fail = true;
	}
	fontArray[short(Fonts::wordFont)]			= TTF_OpenFont(fontPath.c_str(), fontSizeArray[short(Fonts::wordFont)]);
	if (fontArray[short(Fonts::wordFont)] == nullptr)
	{
		fail = true;
	}
	fontArray[short(Fonts::wordFont_small)]	= TTF_OpenFont(fontPath.c_str(), fontSizeArray[short(Fonts::wordFont_small)]);
	if (fontArray[short(Fonts::wordFont_small)] == nullptr)
	{
		fail = true;
	}
	if (fail)
	{
		error(Error::initFont,"TTF_OpenFont failed: " + string(TTF_GetError()));
	}
}

//�������� �������
void close_Fonts()
{
	TTF_CloseFont(fontArray[short(Fonts::digitFont)]);
	TTF_CloseFont(fontArray[short(Fonts::digitFont_small)]);
	TTF_CloseFont(fontArray[short(Fonts::wordFont)]);
	TTF_CloseFont(fontArray[short(Fonts::wordFont_small)]);
}

//������������ ������� ��������� ������ 
void init_buttonsState()
{
	for (short i = 0; i<short(ButtonArrays::eventInfoButtons); i++)
		buttonsState[i] = true;
	buttonsState[short(ButtonArrays::eventInfoButtons)] = false;
	buttonsState[short(ButtonArrays::eventCreateButtons)] = false;
}

//������������� ������� ����� � ����������� ������������
void init_ImagePathArray()
{
	//������������� �����������
	imagePathsArray[0] = "C:/SDL/Calendar_v0.3.1/Calendar_v0.3.1/Images/spring.bmp";
	imagePathsArray[1] = "C:/SDL/Calendar_v0.3.1/Calendar_v0.3.1/Images/summer.bmp";
	imagePathsArray[2] = "C:/SDL/Calendar_v0.3.1/Calendar_v0.3.1/Images/autumn.bmp";
	imagePathsArray[3] = "C:/SDL/Calendar_v0.3.1/Calendar_v0.3.1/Images/winter.bmp";

	imagePathsArray[short(Element::createEventButton)]	   = "C:/SDL/Calendar_v0.3.1/Calendar_v0.3.1/Images/createEvent.bmp";
	imagePathsArray[short(Element::deleteButton)]		   = "C:/SDL/Calendar_v0.3.1/Calendar_v0.3.1/Images/delete.bmp";
	imagePathsArray[short(Element::swipeUp)]			   = "C:/SDL/Calendar_v0.3.1/Calendar_v0.3.1/Images/swipeUp.bmp";
	imagePathsArray[short(Element::swipeDown)]			   = "C:/SDL/Calendar_v0.3.1/Calendar_v0.3.1/Images/swipeDown.bmp";
	imagePathsArray[short(Element::buttonHome)]			   = "C:/SDL/Calendar_v0.3.1/Calendar_v0.3.1/Images/button_home.bmp";
	imagePathsArray[short(Element::buttonRight)]		   = "C:/SDL/Calendar_v0.3.1/Calendar_v0.3.1/Images/button_right.bmp";
	imagePathsArray[short(Element::buttonLeft)]			   = "C:/SDL/Calendar_v0.3.1/Calendar_v0.3.1/Images/button_left.bmp";
	imagePathsArray[short(Element::textInput)]			   = "C:/SDL/Calendar_v0.3.1/Calendar_v0.3.1/Images/textInput.bmp";
	imagePathsArray[short(Element::setNewEvent)]		   = "C:/SDL/Calendar_v0.3.1/Calendar_v0.3.1/Images/setNewEvent.bmp";
	imagePathsArray[short(Element::setDate)]			   = "C:/SDL/Calendar_v0.3.1/Calendar_v0.3.1/Images/options.bmp";

}

//������������� ������� �������� ����������� �����������
void init_elementSizes()
{
	elementSizes[short(Element::cell)] = { 140,70 };
	elementSizes[short(Element::cell_big)] = { 210,70 };
	elementSizes[short(Element::eventInfoList)] = { 210,350 };
	elementSizes[short(Element::createEventButton)] = { 210,70 };
	elementSizes[short(Element::setNewEvent)] = { 100,40 };
	elementSizes[short(Element::textInput)] = { 980,210 };
	elementSizes[short(Element::eventDeleteList)] = { 980,280 };
	elementSizes[short(Element::deleteButton)] = { 20,20 };
	elementSizes[short(Element::swipeUp)] = { 20,20 };
	elementSizes[short(Element::swipeDown)] = { 20,20 };
	elementSizes[short(Element::buttonHome)] = { 70,70 };
	elementSizes[short(Element::buttonRight)] = { 70,70 };
	elementSizes[short(Element::buttonLeft)] = { 70,70 };
	//elementSizes[short(Element::background)] = { 1200,600 };
}

//������������� ������� �������� �������� ������
void init_buttonArraysCount()
{
	buttonArraysCount[short(ButtonArrays::dayCellButtons)]		= DAYCELLBUTTONSCOUNT;
	buttonArraysCount[short(ButtonArrays::changeMonthButtons)]  = CHANGEMONTHBUTTONSCOUNT;
	buttonArraysCount[short(ButtonArrays::dateInfoButtons)]		= DATEINFOBUTTONSCOUNT;
	buttonArraysCount[short(ButtonArrays::eventInfoButtons)]	= EVENTINFOBUTTONSCOUNT;
	buttonArraysCount[short(ButtonArrays::eventCreateButtons)]  = EVENTCREATEBUTTONS;
	buttonArraysCount[short(ButtonArrays::setDateButtons)]		= SETDATEBUTTONSCOUNT;
}


//������������� ������� ������ dayCellButtons, ������ �������� ������ � �������� ����� ���������
void init_DayCellButtons()
{
	int w = elementSizes[short(Element::cell)].first;
	int h = elementSizes[short(Element::cell)].second;
	int dx = 1;

	for (short i = 0; i < buttonArraysCount[short(ButtonArrays::dayCellButtons)]; i++)
	{
		if (i < 7)
		{
			dayCellButtons[i] = Button{ INDENTX + (w * (i % 7) + dx * (i % 7 +1)),INDENTY + (h*short(i/7) + dx*(i/7)+1),0,false,Element::cell,nullptr };
		}
		else
		{
			dayCellButtons[i] = Button{ INDENTX + (w * (i % 7) + dx * (i % 7 +1)), INDENTY + (h*short(i/7) + dx*(i/7)+1),0, true, Element::cell, viewEvent };
		}
	}
}

//������������� ������� ������ changeMonthButtons, ������� �������� ������:
//[0]������������ �������� ��������� �� ���� ����� �����
//[1]����������� � ��������, ���������� ������� ����
//[2]������������ �������� ��������� �� ���� ����� ������
void init_ChangeButtons()
{
	int w = elementSizes[int(Element::buttonLeft)].first;

	changeMonthButtons[0] = Button{ MAINWINDOW_WIDTH - (w * 4),0,0,true,Element::setDate ,startSetDate };
	//changeMonthButtons[0] = Button{ MAINWINDOW_WIDTH - (w * 4),0,0,true,Element::setDate ,nullptr};
	changeMonthButtons[1] = Button{ MAINWINDOW_WIDTH - (w*3),0,-1,true,Element::buttonLeft,changeMonth };
	changeMonthButtons[2] = Button{ MAINWINDOW_WIDTH - (w*2),0,0,true,Element::buttonHome,changeMonth };
	changeMonthButtons[3] = Button{ MAINWINDOW_WIDTH - (w),0,1,true,Element::buttonRight,changeMonth };
}

//������������� ������� ������ changeMonhButtons,������� �������� ������:
//[0]����������� ������� ����
//[1]����������� ������ � ���� ������� �������� ���������
void init_DateInfoButtons()
{
	dateInfoButtons[0] = Button{ 0,0,0,false,Element::cell_big,nullptr };
	dateInfoButtons[1] = Button{ elementSizes[short(Element::cell_big)].first+1,0,0,false,Element::cell_big,nullptr };
}

//������������� ������� ������ eventsInfoButtons, ������� ������� ������:
//[0]����������� ���� ������� ������ �� ������� dayCellButtons
//[1]����������� ������ ������� ��� ���� ����
//[2]������ ������ ���� ��������/������� �������
//[3][4] - ��������� ������ �������
void init_EventsInfoButtons()
{
	int w = elementSizes[short(Element::cell_big)].first;
	int h = elementSizes[short(Element::cell_big)].second;
	int h2 = elementSizes[short(Element::eventInfoList)].second;

	eventsInfoButtons[0] = Button{ 0,h,0,false,Element::cell_big,nullptr };
	eventsInfoButtons[1] = Button{ 0,h *2+1,0,false,Element::eventInfoList,nullptr };
	eventsInfoButtons[2] = Button{ 0,h*2 + h2+1,0,false,Element::createEventButton,viewEventCreateMenu };
	eventsInfoButtons[3] = Button{ w - 20,h*2,short(ButtonArrays::eventInfoButtons),false,Element::swipeUp,swipUp };
	eventsInfoButtons[4] = Button{ w - 20,h*2 +h2-20,short(ButtonArrays::eventInfoButtons),false,Element::swipeDown,swipDown };
}

//������������� ������� ������ eventsCreateButtons, ������� �������� ������:
//[0]������ �� ���� ��������/�������� �������; 
//[1]����� ������
//[2]����������� ������ ������� � �� ��������
//[3][4] - ��������� ������ �������
void init_EventCreateButtons()
{
	int w = elementSizes[short(Element::cell_big)].first;
	int h = elementSizes[short(Element::cell_big)].second;
	//w + 100,100+h
	eventCreateButtons[0] = Button{ w+1,h,0,false,Element::textInput,start_textInput};
	eventCreateButtons[1] = Button{ w + 610 ,h + 140,0,false,Element::setNewEvent,addNewEvent };
	eventCreateButtons[2] = Button{ w+1,h * 4,0,false,Element::eventDeleteList,deleteElement };
	eventCreateButtons[3] = Button{ w,h,0,false,Element::buttonLeft,eventCreateMenuBack };
	eventCreateButtons[4] = Button{ w + elementSizes[short(Element::eventDeleteList)].first - 20,h * 4,short(ButtonArrays::eventCreateButtons),false,Element::swipeUp,swipUp };
	eventCreateButtons[5] = Button{ w + elementSizes[short(Element::eventDeleteList)].first - 20,h * 4 + elementSizes[short(Element::eventDeleteList)].second-20,short(ButtonArrays::eventCreateButtons),false,Element::swipeDown,swipDown };
}

void init_SetDateButtons()
{
	setDateButtons[0] = Button{ 100,200,0,false,Element::textInput, nullptr};
	setDateButtons[1] = Button{ 0,0,0,false,Element::buttonLeft,endSetDate };
	setDateButtons[2] = Button{ 250,350,0,false,Element::setNewEvent,acceptInputDate };
	//setDateButtons[3] = Button{ 0,0,0,false,Element::COUNT,nullptr };
}

//������������� ������� ruSym
void init_ruSym()
{
	char eng[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','[',']',';','\'','`',',','.','/' };
	char ru[] = { '�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','.' };
	short scan[] = { 4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,47,48,51,52,53,54,55,56 };
	for (short i = 0; i < 32; i++)
	{
		ruSym[i].engChar = eng[i];
		ruSym[i].ruChar = ru[i];
		ruSym[i].scancode = scan[i];
	}
}

void init_Buttons()
{
	init_elementSizes();
	init_ImagePathArray();
	init_buttonArraysCount();
	init_buttonsState();
	init_ruSym();

	init_SetDateButtons();
	init_DayCellButtons();
	init_ChangeButtons();
	init_DateInfoButtons();
	init_EventsInfoButtons();
	init_EventCreateButtons();
}