#include "TextManipulation.h"

Symbols ruSym[SYMBOLINALPHABET];

//Перевод строки в юникод
wstring transform_str(string str)
{
	wchar_t* new_str = new wchar_t[str.size() + 1];
	mbstowcs(new_str, str.c_str(), str.size() + 1);
	wstring str2 = new_str;

	delete[]new_str;
	return str2;
}

//Перевод строки юникода в массив типа Uint16
void text_transform(wstring str, Uint16* new_str)
{
	int size = str.size();
	for (short i = 0; i < size + 1; i++)
	{
		new_str[i] = str[i];
	}
}

bool parsStrtoDate(string str)
{
	const short size = 3;
	string date[size];
	short day = 0, month = 0, year = 0;
	for (short j = 0, i = 0; j < size; j++)
	{
		while (str.size() > i && str[i] != '.')
		{

			if(!(str[i]>47 && str[i]<58))
				return false;

			date[j] += str[i];
			i++;
		}
		
		if (date[j].size() == 0)
			return false;
		i++;
	}
	day = atoi(date[0].c_str());
	month = atoi(date[1].c_str()) - 1;
	year = atoi(date[2].c_str());

	if (isDate(day, Month(month), year))
		setCurrentDate(day, month, year);
	else
		return false;

	return true;
}

//Возвращает количество символов в числе
short digitNumber(short val)
{
	short count = 0;
	while(val>0)
	{
		count++;
		val /= 10;
	}
	return count;
}

//Перевод числа в строку
string digit_transform(short val)
{
	char* str = new char[digitNumber(val)+1];
	string str2;

	sprintf(str, "%d", val);
	str2 = str;
	delete[] str;

	return str2;
}

//Получение строки в формате day.month.year
string getDate_str(short day, short month, short year)
{
	string str;
	char* char_str = new char[digitNumber(day) + digitNumber(month + 1) + digitNumber(year) + 3];
	sprintf(char_str, "%d.%d.%d", day, month, year);
	str = char_str;
	delete[]char_str;

	return str;
}

//Функция нужна, для реализации ввода русского текста через графический интерфейс
//Функция сравнивает полученный сканкод с сканкодами из массива ruSym (ruSym.scancode) и при совпадении
//сравнивает полученные символы с символами из массива ruSym (ruSym.engChar) и при несовпадении возвращает
//русский символ из массива ruSym (ruSym.ruChar)
char whatSym(string str, short scancode, bool isCapital)
{
		for (short i = 0; i < SYMBOLINALPHABET; i++)
		{
			if (ruSym[i].scancode == scancode && (str[0] != ruSym[i].engChar && str[0] != toupper(ruSym[i].engChar)))
			{
				if (isCapital)
					return toupper(ruSym[i].ruChar);

				return ruSym[i].ruChar;
			}
		}
	return str[0];
}
