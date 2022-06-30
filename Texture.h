#include "TextManipulation.h"


enum class Element { cell = 0, cell_big, eventInfoList, eventDeleteList, createEventButton, deleteButton, swipeUp, swipeDown, buttonHome, buttonRight, buttonLeft, textInput, setNewEvent,setDate, COUNT };
enum class Fonts { digitFont = 0, digitFont_small, wordFont, wordFont_small, COUNT };

class Texture
{
public:
	Texture();
	~Texture();
	
	void free();																						//������� ��������	  mTexture
	void surfaceFree();																					//������� ����������� mSurface
	void createSurface(Element element);
	void loadImage(string path, bool transparent = false, SDL_Color color = { 0,0,0 });					//�������� ����������� �� ����������� mSurface
	void addImage(string path, int x, int y, bool transparent = false, SDL_Color color = { 0,0,0 });	//�������� ��������������� ����������� �� ����������� mSurface
	void loadFromText(string text, TTF_Font* font, SDL_Color color, int x, int y);						//�������� ������ �� ����������� mSurface
	void loadTexture();																					//��������� �������� mTexture �� ����������� mSurface
	void render(int x, int y);																			//������ �������� mTexture

	int getWidth();																						//���������� mWidth
	int getHeight();																					//���������� mHeight

private:
	SDL_Texture* mTexture;
	SDL_Surface* mSurface;

	int mWidth;																			
	int mHeight;																		
};



extern Texture backgrounds[4];
extern SDL_Window* gWindow;										//������������ ����
extern SDL_Renderer* gRenderer;									//������ ������������� ����

extern string imagePathsArray[short(Element::COUNT)];			//������ ����� � ����������� ������������
extern pair<short, short> elementSizes[short(Element::COUNT)];	//������ �������� ����������� �����������

extern TTF_Font* fontArray[short(Fonts::COUNT)];				//������ ������� (����������� �� ��������)
extern short fontSizeArray[short(Fonts::COUNT)];				//������ �������� �������


extern const string fontPath;									//���� � ������������ ������
extern SDL_Color gTextColor;									//���� ������	
extern SDL_Color blackColor;
extern SDL_Color transpatentColor;
