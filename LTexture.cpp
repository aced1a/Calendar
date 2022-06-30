#include "Texture.h"

Texture backgrounds[4];
SDL_Window* gWindow=nullptr;			//������������ ����
SDL_Renderer* gRenderer = nullptr;		//������ ������������� ����

const string fontPath = "C:/SDL/Calendar_v0.3.1/Calendar_v0.3.1/Fonts/16271.ttf";			//���� � ������������ ������
SDL_Color gTextColor = { 0xFF,0xFF,0xFF };
SDL_Color blackColor = { 0x00,0x00,0x00 };
SDL_Color transpatentColor = {0x00,0x00,0x00};

string imagePathsArray[short(Element::COUNT)];										//������ ����� � ����������� ������������
pair<short, short> elementSizes[int(Element::COUNT)];									//������ �������� ����������� �����������

TTF_Font* fontArray[short(Fonts::COUNT)];												//������ ������� (����������� �� ��������)
short fontSizeArray[short(Fonts::COUNT)];												//������ �������� �������
	

Texture::Texture()
{
	mTexture = nullptr;
	mSurface = nullptr;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture()
{
	free();
	surfaceFree();
	mWidth = 0;
	mHeight = 0;
}

//������� ��������	  mTexture
void Texture::free()
{
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}
}

//������� ����������� mSurface
void Texture::surfaceFree()
{
	if(mSurface != nullptr)
	{
		SDL_FreeSurface(mSurface);
		mSurface = nullptr;
	}
}

int Texture::getHeight()
{
	return mHeight;
}

int Texture::getWidth()
{
	return mWidth;
}


void Texture::createSurface(Element element)
{
	if (element == Element::COUNT)
	{
		mWidth = MAINWINDOW_WIDTH;
		mHeight = MAINWINDOW_HEIGHT;
	}
	else
	{
		mWidth = elementSizes[short(element)].first;
		mHeight = elementSizes[short(element)].second;
	}

	surfaceFree();
	SDL_Surface* blitSurface = nullptr;
	mSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, mWidth, mHeight, 32, 0xff000000, 0x00ff0000, 0x00000ff00, 0x00000000ff);
	if (mSurface == nullptr)
	{
		error(Error::surfaceCreate,"SDL_CreateRGBSurface error: " + string(SDL_GetError()));
	}
	blitSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, mWidth, mHeight, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff00000000);
	if(blitSurface==nullptr)
	{
		error(Error::surfaceCreate,"SDL_CreateRGBSurface" + string(SDL_GetError()));
	}

	SDL_Rect rect = { 0,0,mSurface->w,mSurface->h };
	SDL_FillRect(blitSurface, &rect, SDL_MapRGB(mSurface->format, 255, 255, 255));
	SDL_SetSurfaceBlendMode(blitSurface, SDL_BLENDMODE_BLEND);
	SDL_SetSurfaceAlphaMod(blitSurface, 128);
	
	SDL_BlitSurface(blitSurface, NULL,mSurface,NULL);
	SDL_FreeSurface(blitSurface);
}


//�������� ����������� �� ����������� mSurface
void Texture::loadImage(string path,bool transparent, SDL_Color color)
{
	surfaceFree();

	mSurface = SDL_LoadBMP(path.c_str());
	if (mSurface == nullptr)
	{
		error(Error::imageLoad,"loadImage: LoadBMP error: " + string(SDL_GetError()));
	}

	if(transparent)
	{
		SDL_SetColorKey(mSurface, SDL_TRUE, SDL_MapRGB(mSurface->format,color.r,color.g,color.b));
	}
	mWidth = mSurface->w;
	mHeight = mSurface->h;
}

//�������� ��������������� ����������� �� ����������� mSurface
void Texture::addImage(string path, int x,int y, bool transparent, SDL_Color color)
{
	SDL_Surface* loadedImage = SDL_LoadBMP(path.c_str());
	if (loadedImage == nullptr)
	{
		error(Error::imageLoad,"loadImage: LoadBMP error: " + string(SDL_GetError()));
	}
	if (transparent)
	{
		SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(loadedImage->format, color.r, color.g, color.b));
	}
	SDL_Rect rect = { NULL,NULL,loadedImage->w,loadedImage->h };
	SDL_Rect desc = { x,y,NULL,NULL};
	SDL_BlitSurface(loadedImage, &rect, mSurface, &desc);
	SDL_FreeSurface(loadedImage);
}

//�������� ������ �� ����������� mSurface
void Texture::loadFromText(string text, TTF_Font* font, SDL_Color color, int x,int y)
{
	if (text.size() == 0)
	{
		return;
	}

	SDL_Surface* textSurface = nullptr;
	Uint16* unicode_text = new Uint16[text.size() + 1];

	text_transform(transform_str(text), unicode_text);
	textSurface = TTF_RenderUNICODE_Solid(font, unicode_text, color);
	if (textSurface == nullptr)
	{
		error(Error::textRender,"loadFromText failed: " + string(TTF_GetError()));
	}

	SDL_Rect rect = { NULL,NULL,mSurface->w - x,mSurface->h - y };
	SDL_Rect desc = { x,y,NULL,NULL };
	SDL_BlitSurface(textSurface, &rect, mSurface, &desc);

	SDL_FreeSurface(textSurface);
}

//��������� �������� mTexture �� ����������� mSurface
void Texture::loadTexture()
{
	free();
	mTexture = SDL_CreateTextureFromSurface(gRenderer, mSurface);
	if (mTexture == nullptr)
	{
		error(Error::textureCreate,"loadTexute failed: " + string(SDL_GetError()));
	}
	surfaceFree();
}

//������ �������� mTexture
void Texture::render(int x, int y)
{
	SDL_Rect renderQuad = { x,y,mWidth,mHeight };	
	SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}
