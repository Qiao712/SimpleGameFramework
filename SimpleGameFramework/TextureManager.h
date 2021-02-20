#pragma once
#include "Vector.h"
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<map>
using std::string;
using std::map;
class Texture;
class Window;
class Animation;
/*
* @brief TextureManger��
* Ϊһ�� Singleton\n
* ���沢�������е�����/������Դ
* ��������/���������롢Ϊ���������ṩ����
* ���䴴������/��������
*/
class TextureManager
{
	friend class AnimationManager;
public:
	static void init();			//��ʼ��,����һ��ʵ��
	static Texture* create(string name);			//��������/����
	static SDL_Renderer* getSDL_Renderer();		//��ȡ��Ⱦ��

	static void drawLine(Point p1, Point p2, Uint8 r = 255, Uint8 g = 0, Uint8 b = 0, Uint8 a = 0);	//����
private:
	static TextureManager* _instance;

	TextureManager(SDL_Renderer* _renderer);
	~TextureManager();

	void    _loadTextures();						//����������Դ
	void    _loadAnimations();					/**��ȡ�����������ļ����������ж�����ԭ��*/
	Texture _loadTexture(string path);		    //���ļ���������
	bool    _checkExtension(string extension);	//�����չ��

	/**����ԭ��*/
	map<string, Texture> _textures;			//���Ƶ���������ӳ��
	map<string, Animation> animations;		//���Ƶ����������ӳ��	

	SDL_Renderer* _renderer;					//ȫ�ֵ���Ⱦ��
};