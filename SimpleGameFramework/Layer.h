#pragma once
#include"GameObject.h"
/**
* @brief 层，各种游戏对象的容器\n
* 默认跟随窗口大小\n
* 具有背景纹理属性\n
*/
class Layer : public GameObject
{
public:
	Layer();
	
	void draw();

	void setSize(int w, int h) { _w = w; _h = h; }
	int getHeight() { return _h; }
	int getWidth() { return _w; }
	
	void setBackground(string name_texture);
private:
	int _w;
	int _h;
	Texture* _background = nullptr;		//背景
};

