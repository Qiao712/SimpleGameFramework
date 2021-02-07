#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<map>
using std::string;
using std::map;
class Texture;
class Window;
/*
* @brief TextureManger��
* Ϊһ�� Singleton\n
* ���沢�������е�������Դ
* ������������롢Ϊ���������ṩ����
* ���䴴���������
*/
class TextureManager
{
public:
	static void init(const Window& win);			//��ʼ��,����һ��ʵ��
	static Texture create(string name);			//��������
	static SDL_Renderer* getSDL_Renderer();		//��ȡ��Ⱦ��

	static void drawLine(int x1, int y1, int x2, int y2, char r = 255, char g = 0, char b = 0, char a = 0);	//����
private:
	static TextureManager* _instance;

	TextureManager(SDL_Renderer* _renderer);
	~TextureManager();

	void loadTextures();						//����������Դ
	Texture loadTexture(string path);		//���ļ���������

	map<string, Texture> _textures;			//��������Ƶ���������ӳ��	
	SDL_Renderer* _renderer;					//ȫ�ֵ���Ⱦ��
};