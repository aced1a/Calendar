#include "FileWork.h"
#define SYMBOLINALPHABET 34

//��� ��������� �����, ��� ���������� ����� �������� ������ 
struct Symbols
{
	short scancode=0;
	char engChar=0;
	char ruChar=0;
};

extern Symbols ruSym[SYMBOLINALPHABET];


void text_transform(wstring str, Uint16* new_str);	//������� �� wstring  � ������  Uint16
wstring transform_str(string str);					//������� � ������ unicode
string digit_transform(short val);					//������� �� ����� � ������

char whatSym(string str, short scancode,bool isCapital);

string getDate_str(short day, short month, short year);

short digitNumber(short val);
bool parsStrtoDate(string str);
