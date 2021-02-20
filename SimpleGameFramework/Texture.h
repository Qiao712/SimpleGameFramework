#pragma once
#include<SDL.h>
#include"Vector.h"
/**��ת*/
enum FLIP{FLIP_NONE = 0,FLIP_HORIZONTAL = 1, FLIP_VERTICAL = 2, FLIP_BOTH = 3};
/**����ϵ*/
enum CROOD{WORLD_CROOD, SCREEN_CROOD};
/**
* @brief Texture
* ��װ������������SDL_Texture�����
* ����ͳһ��SDL_Texture����TextureManager���󴴽�
* ������ ������
*/
class Texture
{
	friend class TextureManager;
	friend class AnimationManager;
public:
	Texture(SDL_Texture* texture = nullptr, SDL_Renderer* renderer = nullptr);

	//����
	virtual void draw(Point position, int w, int h, double angle, Vector center = Vector(0, 0), int flip = FLIP_NONE, CROOD crood = WORLD_CROOD);
	virtual void draw(Point position, double angle ,Vector center = Vector(0, 0), int flip = FLIP_NONE, CROOD crood = WORLD_CROOD);
	virtual void draw(Point position, int w, int h, CROOD crood = WORLD_CROOD);
	virtual void draw(Point position, CROOD crood = WORLD_CROOD);

	//ΪAnimation����Ĳ��ſ��ƺ���
	virtual void pause() {/*ȱʡ�Ĳ���*/ }
	virtual void play() {/*ȱʡ�Ĳ���*/}
	virtual int getCurrentFrame() { return 0; /*ȱʡ�Ĳ���*/ }
	virtual void setCurrentFrame(int frame) {/*ȱʡ�Ĳ���*/ }
	virtual int getIntervalTime() { return 0;/*ȱʡ�Ĳ���*/ }
	virtual void setIntervalTime(int interval) {/*ȱʡ�Ĳ���*/ }

	//get
	int getHeight() { return _height; }
	virtual int getWidth() { return _width; }
protected:
	SDL_Texture* _texture;
	SDL_Renderer* _renderer;
	int _height = 0;
	int _width = 0;
};