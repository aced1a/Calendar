#include "Button.h"

extern int x=0, y=0;			//Координаты, по которым было совершено нажатие кнопки мыши	
bool textInputActive = false;	//Ввод текста активен
string inputText="";			//Вводимый текст
ButtonArrays textInputButtons=ButtonArrays::eventCreateButtons;

//Рендер вводимого текста

//Проверка,была ли нажата клавиша button
bool inSquare(Button* button,int& x,int& y)
{
	if (x > button->getX() && y > button->getY() && x < (button->getX() + button->mTexture.getWidth()) && y < (button->getY() + button->mTexture.getHeight()))
		return true;
	return false;
}

//Проверка,была ли нажата какая-либо клавиша, если да и она активна, то вызывается ее функция buttonFunction 
void whichButtonDown(int& x,int& y)
{
	Button* button = nullptr;

	for(short i=0;i<short(ButtonArrays::COUNT);i++)
	{
		for (short j = 0; j < buttonArraysCount[i]; j++)
		{
			button = &ptrButtonArrays[i][j];
			if (button->getActive() && inSquare(button, x, y))
			{
				button->buttonFunction(button->getIndex());
			}
		}
	}
}

//Проверка было ли провернуто колесико мыши в зоне одного из списка событий
void whereScrolled(int x, int y, short direction)
{
	if (buttonsState[short(ButtonArrays::eventInfoButtons)] && inSquare(&eventsInfoButtons[1], x, y))
	{
		loadMedia_EventsInfoButtons(eventsInfoButtons[2].getIndex(), short(lastDate.getMonth()), lastDate.getYear(), -direction);
		drawButtons();
		ViewWindow();
	}
	else if (buttonsState[short(ButtonArrays::eventCreateButtons)] && inSquare(&eventCreateButtons[3], x, y))
	{
		loadMedia_EventCreateButtons(eventCreateButtons[2].getIndex(), -direction);
		drawButtons();
		ViewWindow();
	}
}

//Обработка событий
void eventControll()
{
	SDL_Event e;
	bool running = true;
	bool renderText = false;
	short scancode = 0;
	bool isCapitalLetter = false;
	//int x=0, y = 0;
	short direct = 0;

	while (running)
	{
		if(SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&x, &y);
				whichButtonDown(x, y);
				break;
			case SDL_KEYDOWN:
				scancode = e.key.keysym.scancode;
				if (SDL_GetModState() & KMOD_SHIFT || SDL_GetModState() & KMOD_CAPS)
				{
					isCapitalLetter = true;
				}
				if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
				{
					inputText.pop_back();
					renderText = true;
				}
				else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
				{
					SDL_SetClipboardText(inputText.c_str());
				}
				else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
				{
					inputText = SDL_GetClipboardText(); renderText = true;
				}
				break; 
			case SDL_TEXTINPUT:
				inputText += whatSym(e.text.text, scancode,isCapitalLetter);
				isCapitalLetter = false;
				renderText = true;
				break;
			case SDL_MOUSEWHEEL:
				SDL_GetMouseState(&x, &y);
				if (e.wheel.y > 0)
					direct = 1;
				else if (e.wheel.y < 0)
					direct = -1;
				whereScrolled(x,y,direct);
				break;			
			default:
				break;
			}
			if (renderText)
			{
				inputTextRender(100,100);
				renderText = false;
			}
		}
		if (autoSetTime_time && updateTime())
		{
			
			loadMedia_DateInfoButtons(0);
			drawButtons();
			ViewWindow();
		}
	}
}
