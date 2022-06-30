#include "Button.h"
  
// Врядли это говно вообще скомпилится, но оно когда-то работало, ага, были времена...


void error(Error error,string str)
{
	switch (error)
	{
	case Error::invalidDate:
		if (!invalidDate)
		{
			invalidDate = true;
			autoSetTime();
		}
		break;
	case Error::initSDL:
		//break;
	case Error::initTTF:
		//break;
	case Error::initFont:
		//break;
	case Error::windowCreate:
		//break;
	case Error::surfaceCreate:
		//break;
	case Error::renderCreate:
		//break;
	case Error::textureCreate:
		//break;
	case Error::textRender:
		//break;
	case Error::imageLoad:
		//break;
		throw runtime_error(str);
		break;
	case Error::fileOpen:
		if(!invalidFile)
		{
			invalidFile = true;
			checkFiles(); 
		}
		if(invalidFile)
			throw runtime_error(str);
		break;
	default:
		break;
	}
}

int main(int argc, char * argv[])
{
	setlocale(LC_ALL, "RUS");
	try 
	{
		checkFiles();

		init_SDL();
		init_Fonts();

		autoSetTime();
	
	    init_Buttons();
		loadMedia();

		if(invalidDate)
		{
			startSetDate(0);
		}
		drawButtons();
		ViewWindow();
		eventControll();

		close_Fonts();
		close_SDL();

		return 0;
	}
	catch(exception c )
	{
		cerr << c.what() << endl;
		close_SDL();
		close_Fonts();
		return 1;
	}
}