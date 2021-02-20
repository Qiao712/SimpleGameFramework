#pragma once
#include "Texture.h"
/**
* @brief 动画类
* Texture的子类，即随时间改变的纹理。
*/
class Animation :
    public Texture
{
public:
    Animation(int width_frame = 0, int interval = 0, SDL_Texture* texture = nullptr, SDL_Renderer* renderer = nullptr);

    virtual void draw(Point position, int w, int h, double angle, Vector center = Vector(0, 0), int flip = FLIP_NONE, CROOD crood = WORLD_CROOD);
    virtual void draw(Point position, double angle, Vector center = Vector(0, 0), int flip = FLIP_NONE, CROOD crood = WORLD_CROOD);
    virtual void draw(Point position, int w, int h, CROOD crood = WORLD_CROOD);
    virtual void draw(Point position, CROOD crood = WORLD_CROOD);

    /**
    * @brief 播放控制
    * @{
    */
    virtual void pause() { _play = false; }
    virtual void play() { _play = true; }
    virtual int getCurrentFrame() { return _current_frame;}
    virtual void setCurrentFrame(int frame) { _current_frame = frame % _num_frame; }
    virtual int getIntervalTime() { return _interval; }
    virtual void setIntervalTime(int interval) { _interval = interval; }
    /**
    * @}
    */

    int getWidth() { return _width_frame; }
private:
    /**获取当前帧在纹理图片中的矩形区域*/
    SDL_Rect _getSrcRect();
    /**在draw时调用，刷新动画的当前帧*/
    void _refresh();

    int _width_frame;    //! 动画的宽度
    int _interval;       //! 帧之间间隔时间，ms
    int _num_frame;      //! 总帧数
    int _current_frame = 0;  //! 当前帧
    bool _play = true;       //播放状态
    unsigned int _time_last; //上次绘制时的时间，ms
};

