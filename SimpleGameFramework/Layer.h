#pragma once
#include"GameObject.h"
/**
* @brief �㣬������Ϸ���������
* Ĭ�ϸ��洰�ڴ�С
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
	Texture* _background = nullptr;		//����
};

