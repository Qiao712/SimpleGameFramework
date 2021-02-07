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
* @brief TextureManger：
* 为一个 Singleton\n
* 储存并管理所有的纹理资源
* 负责纹理的载入、为其他对象提供纹理
* 由其创建纹理对象
*/
class TextureManager
{
public:
	static void init(const Window& win);			//初始化,创建一个实例
	static Texture create(string name);			//创建纹理
	static SDL_Renderer* getSDL_Renderer();		//获取渲染器

	static void drawLine(int x1, int y1, int x2, int y2, char r = 255, char g = 0, char b = 0, char a = 0);	//画线
private:
	static TextureManager* _instance;

	TextureManager(SDL_Renderer* _renderer);
	~TextureManager();

	void loadTextures();						//加载纹理资源
	Texture loadTexture(string path);		//从文件加载纹理

	map<string, Texture> _textures;			//纹理的名称到纹理对象的映射	
	SDL_Renderer* _renderer;					//全局的渲染器
};