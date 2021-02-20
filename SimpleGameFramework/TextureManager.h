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
* @brief TextureManger：
* 为一个 Singleton\n
* 储存并管理所有的纹理/动画资源
* 负责纹理/动画的载入、为其他对象提供纹理
* 由其创建纹理/动画对象
*/
class TextureManager
{
	friend class AnimationManager;
public:
	static void init();			//初始化,创建一个实例
	static Texture* create(string name);			//创建纹理/动画
	static SDL_Renderer* getSDL_Renderer();		//获取渲染器

	static void drawLine(Point p1, Point p2, Uint8 r = 255, Uint8 g = 0, Uint8 b = 0, Uint8 a = 0);	//画线
private:
	static TextureManager* _instance;

	TextureManager(SDL_Renderer* _renderer);
	~TextureManager();

	void    _loadTextures();						//加载纹理资源
	void    _loadAnimations();					/**读取描述动画的文件，加载所有动画的原型*/
	Texture _loadTexture(string path);		    //从文件加载纹理
	bool    _checkExtension(string extension);	//检测扩展名

	/**储存原型*/
	map<string, Texture> _textures;			//名称到纹理对象的映射
	map<string, Animation> animations;		//名称到动画对象的映射	

	SDL_Renderer* _renderer;					//全局的渲染器
};