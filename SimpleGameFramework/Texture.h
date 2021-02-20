#pragma once
#include<SDL.h>
#include"Vector.h"
/**翻转*/
enum FLIP{FLIP_NONE = 0,FLIP_HORIZONTAL = 1, FLIP_VERTICAL = 2, FLIP_BOTH = 3};
/**坐标系*/
enum CROOD{WORLD_CROOD, SCREEN_CROOD};
/**
* @brief Texture
* 封装的纹理，仅仅是SDL_Texture的外壳
* 共享统一的SDL_Texture，由TextureManager对象创建
* 派生出 动画类
*/
class Texture
{
	friend class TextureManager;
	friend class AnimationManager;
public:
	Texture(SDL_Texture* texture = nullptr, SDL_Renderer* renderer = nullptr);

	//绘制
	virtual void draw(Point position, int w, int h, double angle, Vector center = Vector(0, 0), int flip = FLIP_NONE, CROOD crood = WORLD_CROOD);
	virtual void draw(Point position, double angle ,Vector center = Vector(0, 0), int flip = FLIP_NONE, CROOD crood = WORLD_CROOD);
	virtual void draw(Point position, int w, int h, CROOD crood = WORLD_CROOD);
	virtual void draw(Point position, CROOD crood = WORLD_CROOD);

	//为Animation定义的播放控制函数
	virtual void pause() {/*缺省的操作*/ }
	virtual void play() {/*缺省的操作*/}
	virtual int getCurrentFrame() { return 0; /*缺省的操作*/ }
	virtual void setCurrentFrame(int frame) {/*缺省的操作*/ }
	virtual int getIntervalTime() { return 0;/*缺省的操作*/ }
	virtual void setIntervalTime(int interval) {/*缺省的操作*/ }

	//get
	int getHeight() { return _height; }
	virtual int getWidth() { return _width; }
protected:
	SDL_Texture* _texture;
	SDL_Renderer* _renderer;
	int _height = 0;
	int _width = 0;
};